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

#include "ShadowSprite.h"
#include "renderer/CCRenderer.h"
#include "2d/CCSpriteFrameCache.h"

NS_CC_BEGIN

ShadowSprite* ShadowSprite::create(const std::string &filename)
{
    ShadowSprite *sprite = new (std::nothrow) ShadowSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

ShadowSprite* ShadowSprite::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
    ShadowSprite *sprite = new (std::nothrow) ShadowSprite();
    if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

ShadowSprite* ShadowSprite::createWithSpriteFrameName(const std::string& spriteFrameName)
{
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    
    return createWithSpriteFrame(frame);
}

void ShadowSprite::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    // Don't do calculate the culling if the transform was not updated
#if CC_USE_CULLING
    _insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
    
    if(_insideBounds)
#endif
    {
        _groupCmd.init(_globalZOrder);
        renderer->addCommand(&_groupCmd);
        renderer->pushGroup(_groupCmd.getRenderQueueID());
        
        _beforeDrawCmd.init(_globalZOrder, transform, flags);
        _beforeDrawCmd.func = CC_CALLBACK_0(ShadowSprite::onBeforeDraw, this);
        renderer->addCommand(&_beforeDrawCmd);

        _trianglesCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, _polyInfo.triangles, transform, flags);
        _trianglesCommand.setSkipBatching(true);
        renderer->addCommand(&_trianglesCommand);
        
        _afterDrawCmd.init(_globalZOrder, transform, flags);
        _afterDrawCmd.func = CC_CALLBACK_0(ShadowSprite::onAfterDraw, this);
        renderer->addCommand(&_afterDrawCmd);
        
        renderer->popGroup();
    }
}

void ShadowSprite::onBeforeDraw()
{
    _isDepthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
    if (!_isDepthTestEnabled)
    {
        glEnable(GL_DEPTH_TEST);
    }
}

void ShadowSprite::onAfterDraw()
{
    if (!_isDepthTestEnabled) {
        glDisable(GL_DEPTH_TEST);
    }
}

NS_CC_END