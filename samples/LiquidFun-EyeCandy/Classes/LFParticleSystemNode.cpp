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


static const int MAX_PARTICLES = 10000;

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

varying vec4 v_fragmentColor;
void main()
{
    gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, gl_PointCoord);
}
)";


using namespace cocos2d;

LFParticleSystemNode::LFParticleSystemNode()
: _ratioTransform(Mat4::IDENTITY)
{
}

LFParticleSystemNode::~LFParticleSystemNode()
{
    free(_sizes);
}

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
    _ratioTransform.scale(ratio, ratio, 1);
    _ratio = ratio;

    // own shader
    GLProgram *p = GLProgram::createWithByteArrays(shaderVert, shaderFrag);
    GLProgramState *state = GLProgramState::getOrCreateWithGLProgram(p);
    setGLProgramState(state);

    setupVBO();

    auto textureCache = Director::getInstance()->getTextureCache();
    _texture = textureCache->addImage("Images/fire.png");

    _blendFunc = BlendFunc::ADDITIVE;

    return true;
}

void LFParticleSystemNode::setupVBO()
{
    _sizes = (GLfloat*)malloc(MAX_PARTICLES * sizeof(_sizes[0]));
    for(int i=0; i<MAX_PARTICLES; i++) {
        float s = _particleSystem->GetRadius() * 2;
        _sizes[i] = s + CCRANDOM_0_1() * s;
    }

    auto glProgramState = getGLProgramState();

    // Update Positions
    glProgramState->setVertexAttribPointer("a_position", 2, GL_FLOAT, GL_FALSE, 0, _particleSystem->GetPositionBuffer());
    glProgramState->setVertexAttribPointer("a_color", 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, _particleSystem->GetColorBuffer());
    glProgramState->setVertexAttribPointer("a_size", 1, GL_FLOAT, GL_FALSE, 0, _sizes);


    CHECK_GL_ERROR_DEBUG();
}

// draw

void LFParticleSystemNode::draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(LFParticleSystemNode::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}

void LFParticleSystemNode::onDraw(const Mat4 &transform, bool transformUpdated)
{
    // transform everything to PTM_RATIO
    Mat4 newMV;
    Mat4::multiply(_modelViewTransform, _ratioTransform, &newMV);

    _glProgramState->apply(newMV);

//    GL::blendFunc(_blendFunc.src, _blendFunc.dst);
    GL::bindTexture2D(_texture->getName());
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);

    int totalParticles = _particleSystem->GetParticleCount();
    CCASSERT(totalParticles<MAX_PARTICLES, "too many particles, increase VBO size");

    // Update Positions
    glDrawArrays(GL_POINTS, 0, totalParticles);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,totalParticles);

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

