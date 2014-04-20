//
//  LFParticleSystemNode.h
//  LiquidFun-EyeCandy
//
//  Created by Ricardo Quesada on 4/19/14.
//
//

#ifndef __LiquidFun_EyeCandy__LFParticleSystemNode__
#define __LiquidFun_EyeCandy__LFParticleSystemNode__

#include <Box2D/Box2D.h>
#include "cocos2d.h"
#include "kazmath/kazmath.h"

class LFParticleSystemNode : public cocos2d::Node
{
public:
    static LFParticleSystemNode* create(b2ParticleSystem* particleSystem, float ratio=1);

    virtual void draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;
    void onDraw(const kmMat4 &transform, bool transformUpdated);

protected:
    bool init(b2ParticleSystem* particleSystem, float ratio=1);
    void setupVBO();

    cocos2d::CustomCommand _customCommand;
    b2ParticleSystem* _particleSystem; // weak ref
    kmMat4 _ratioTransform;

    GLuint _buffersVBO[2]; //0: position, 1: color
    ssize_t _sizeVBO;
};

#endif /* defined(__LiquidFun_EyeCandy__LFParticleSystemNode__) */
