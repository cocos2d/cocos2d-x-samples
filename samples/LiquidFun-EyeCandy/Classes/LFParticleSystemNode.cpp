//
//  LFParticleSystemNode.cpp
//  LiquidFun-EyeCandy
//
//  Created by Ricardo Quesada on 4/19/14.
//
//

#include "LFParticleSystemNode.h"

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
    return true;
}

void LFParticleSystemNode::setupVBO()
{
    glGenBuffers(2, &_buffersVBO[0]);

    // 5000 particles
    _sizeVBO = 5000;

    // positions (point only)
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, _sizeVBO * sizeof(b2Vec2), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // colors
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, _sizeVBO * sizeof(b2ParticleColor), NULL, GL_DYNAMIC_DRAW);
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
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

    int totalParticles = _particleSystem->GetParticleCount();
    CCASSERT(totalParticles<_sizeVBO, "too many particles, increase VBO size");

    // Positions
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    b2Vec2 *positions = (b2Vec2*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    b2Vec2* posBuffer = _particleSystem->GetPositionBuffer();
    memcpy(positions, posBuffer, sizeof(positions[0]) * totalParticles);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    // Colors
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[1]);
    b2ParticleColor *colors = (b2ParticleColor*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    b2ParticleColor* colorsBuffer = _particleSystem->GetColorBuffer();
    memcpy(colors, colorsBuffer, sizeof(colors[0]) * totalParticles);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins(_modelViewTransform);

    // vertices
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2F), NULL);

    // tex coords
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Color4F), NULL);

    glDrawArrays(GL_POINTS, 0, totalParticles);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,totalParticles);

    // cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
