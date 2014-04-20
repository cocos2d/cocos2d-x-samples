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

class LFParticleSystemNode : public cocos2d::Node, public cocos2d::BlendProtocol
{
public:
    static LFParticleSystemNode* create(b2ParticleSystem* particleSystem, float ratio=1);

    virtual void draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;
    void onDraw(const kmMat4 &transform, bool transformUpdated);

    const cocos2d::BlendFunc& getBlendFunc() const override;
    void setBlendFunc(const cocos2d::BlendFunc &var) override;

protected:
    bool init(b2ParticleSystem* particleSystem, float ratio=1);
    void setupVBO();

    cocos2d::CustomCommand _customCommand;
    b2ParticleSystem* _particleSystem; // weak ref
    kmMat4 _ratioTransform;
    float _ratio;

    GLuint _buffersVBO[3]; //0: position, 1: color, 2: pointSprite size
    ssize_t _sizeVBO;

    cocos2d::BlendFunc _blendFunc;
    cocos2d::Texture2D *_texture;
};

#endif /* defined(__LiquidFun_EyeCandy__LFParticleSystemNode__) */
