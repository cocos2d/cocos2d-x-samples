/****************************************************************************
Copyright (c) 2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/


#include "LFParticleSystemNode.h"



// Custom Shader
static const GLchar* shaderVert = R"(
attribute vec4 a_position;
attribute vec4 a_color;
attribute float a_size;

#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
#else
varying vec4 v_fragmentColor;
#endif
void main()
{
    gl_Position = CC_PMatrix * CC_MVMatrix * a_position;
    gl_PointSize = CC_MVMatrix[0][0] * a_size;
    v_fragmentColor = a_color;
}
)";

static const GLchar* shaderFrag = R"(

#ifdef GL_ES
precision lowp float;
#endif
uniform sampler2D CC_Texture0;

varying vec4 v_fragmentColor;
void main()
{
    gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, gl_PointCoord);
}
)";


using namespace cocos2d;

LFParticleSystemNode* LFParticleSystemNode::create(b2ParticleSystem* particleSystem, float ratio)
{
    auto node = new LFParticleSystemNode;
    node->init(particleSystem, ratio);
    node->autorelease();

    return node;
}

bool LFParticleSystemNode::init(b2ParticleSystem* particleSystem, float ratio)
{
    _particleSystem = particleSystem;
    kmMat4Scaling(&_ratioTransform, ratio, ratio, 1);
    _ratio = ratio;

    // own shader
    GLProgram *p = new GLProgram;
    p->initWithByteArrays(shaderVert, shaderFrag);
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
//    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    p->bindAttribLocation("a_size", 3);

    p->link();
    p->updateUniforms();

    this->setShaderProgram(p);
    p->release();

    setupVBO();

    auto textureCache = Director::getInstance()->getTextureCache();
    _texture = textureCache->addImage("Images/fire.png");

    _blendFunc = BlendFunc::ADDITIVE;

    return true;
}

void LFParticleSystemNode::setupVBO()
{
    glGenBuffers(3, &_buffersVBO[0]);

    // 5000 particles
    _sizeVBO = 5000;

    // positions (point only)
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, _sizeVBO * sizeof(b2Vec2), NULL, GL_DYNAMIC_DRAW);

    // colors
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, _sizeVBO * sizeof(b2ParticleColor), NULL, GL_DYNAMIC_DRAW);

    // point sprite position
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[2]);
    glBufferData(GL_ARRAY_BUFFER, _sizeVBO * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    float *size = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    for(int i=0; i<_sizeVBO; i++) {
        float s = _particleSystem->GetRadius() * 2;
        size[i] = s + CCRANDOM_0_1() * s;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
}

// draw

void LFParticleSystemNode::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(LFParticleSystemNode::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}

void LFParticleSystemNode::onDraw(const kmMat4 &transform, bool transformUpdated)
{
    // transform everything to PTM_RATIO
    kmMat4 newMV;
    kmMat4Multiply(&newMV, &_modelViewTransform, &_ratioTransform);
    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins(newMV);

//    GL::blendFunc(_blendFunc.src, _blendFunc.dst);
    GL::bindTexture2D(_texture->getName());
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);


    int totalParticles = _particleSystem->GetParticleCount();
    CCASSERT(totalParticles<_sizeVBO, "too many particles, increase VBO size");

    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

    // Update Positions
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    b2Vec2 *positions = (b2Vec2*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    b2Vec2* posBuffer = _particleSystem->GetPositionBuffer();
    memcpy(positions, posBuffer, sizeof(positions[0]) * totalParticles);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(b2Vec2), NULL);

    // Colors
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[1]);
    b2ParticleColor *colors = (b2ParticleColor*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    b2ParticleColor* colorsBuffer = _particleSystem->GetColorBuffer();
    memcpy(colors, colorsBuffer, sizeof(colors[0]) * totalParticles);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(b2ParticleColor), NULL);

    // sizes
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[2]);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(float), NULL);

    glDrawArrays(GL_POINTS, 0, totalParticles);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,totalParticles);

    // cleanup
    glDisableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
}

// Blend Interface

/// blendFunc getter
const BlendFunc& LFParticleSystemNode::getBlendFunc() const
{
    return _blendFunc;
}
/// blendFunc setter
void LFParticleSystemNode::setBlendFunc(const BlendFunc &var)
{
    _blendFunc = var;
}

