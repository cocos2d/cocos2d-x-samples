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


#ifndef __LiquidFun_EyeCandy__LFParticleSystemNode__
#define __LiquidFun_EyeCandy__LFParticleSystemNode__

#include <Box2D/Box2D.h>
#include "cocos2d.h"

class LFParticleSystemNode : public cocos2d::Node, public cocos2d::BlendProtocol
{
public:
    static LFParticleSystemNode* create(b2ParticleSystem* particleSystem, float ratio=1);

    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t transformFlags) override;
    void onDraw(const cocos2d::Mat4 &transform, uint32_t transformFlags);

    const cocos2d::BlendFunc& getBlendFunc() const override;
    void setBlendFunc(const cocos2d::BlendFunc &var) override;

protected:
    LFParticleSystemNode();
    ~LFParticleSystemNode();

    bool init(b2ParticleSystem* particleSystem, float ratio=1);
    void setupVBO();

    cocos2d::CustomCommand _customCommand;
    b2ParticleSystem* _particleSystem; // weak ref
    cocos2d::Mat4 _ratioTransform;
    float _ratio;

    GLfloat *_sizes;

    cocos2d::BlendFunc _blendFunc;
    cocos2d::Texture2D *_texture;
};

#endif /* defined(__LiquidFun_EyeCandy__LFParticleSystemNode__) */
