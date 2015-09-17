/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 
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

#ifndef __FantasyWarrior3D__ShadowSprite__
#define __FantasyWarrior3D__ShadowSprite__

#include "2d/CCSprite.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class ShadowSprite : public Sprite {
    
public:
    static ShadowSprite* create(const std::string& filename);
    static ShadowSprite* createWithSpriteFrame(SpriteFrame *spriteFrame);
    static ShadowSprite* createWithSpriteFrameName(const std::string& spriteFrameName);
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
protected:
    void onBeforeDraw();
    void onAfterDraw();
    
    bool _isDepthTestEnabled;
    
    GroupCommand _groupCmd;
    CustomCommand _beforeDrawCmd;
    CustomCommand _afterDrawCmd;
};

NS_CC_END

#endif /* defined(__FantasyWarrior3D__ShadowSprite__) */
