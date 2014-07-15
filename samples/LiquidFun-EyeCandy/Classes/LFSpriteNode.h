/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __LFSPRITENODE_H__
#define __LFSPRITENODE_H__

#include "cocos2d.h"
#include <Box2D/Box2D.h>

/** A Sprite subclass that is bound to a physics body.
 It works with:
 - Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 - Objective-Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 - Box2d: Preprocessor macro CC_ENABLE_BOX2D_INTEGRATION should be defined

 Features and Limitations:
 - Scale and Skew properties are ignored.
 - Position and rotation are going to updated from the physics body
 - If you update the rotation or position manually, the physics body will be updated
 - You can't enble both Chipmunk support and Box2d support at the same time. Only one can be enabled at compile time
 */
class LFSpriteNode : public cocos2d::Sprite
{
public:

    static LFSpriteNode* create();
    /** Creates an sprite with a texture.
     The rect used will be the size of the texture.
     The offset will be (0,0).
     */
    static LFSpriteNode* createWithTexture(cocos2d::Texture2D *pTexture);

    /** Creates an sprite with a texture and a rect.
     The offset will be (0,0).
     */
    static LFSpriteNode* createWithTexture(cocos2d::Texture2D *pTexture, const cocos2d::Rect& rect);

    /** Creates an sprite with an sprite frame. */
    static LFSpriteNode* createWithSpriteFrame(cocos2d::SpriteFrame *pSpriteFrame);

    /** Creates an sprite with an sprite frame name.
     An SpriteFrame will be fetched from the SpriteFrameCache by name.
     If the SpriteFrame doesn't exist it will raise an exception.
     @since v0.9
     */
    static LFSpriteNode* createWithSpriteFrameName(const char *pszSpriteFrameName);

    /** Creates an sprite with an image filename.
     The rect used will be the size of the image.
     The offset will be (0,0).
     */
    static LFSpriteNode* create(const char *pszFileName);

    /** Creates an sprite with an image filename and a rect.
     The offset will be (0,0).
     */
    static LFSpriteNode* create(const char *pszFileName, const cocos2d::Rect& rect);

    LFSpriteNode();

    virtual bool isDirty() const;

    /** Keep the sprite's rotation separate from the body. */
    bool isIgnoreBodyRotation() const;
    void setIgnoreBodyRotation(bool bIgnoreBodyRotation);

    //
    // Box2d specific
    //
    /** Body accessor when using box2d */
    b2Body* getB2Body() const;
    void setB2Body(b2Body *pBody);

    float getPTMRatio() const;
    void setPTMRatio(float fPTMRatio);

    // overrides
    virtual const cocos2d::Point& getPosition() const override;
    virtual void getPosition(float* x, float* y) const override;
    virtual float getPositionX() const override;
    virtual float getPositionY() const override;
    virtual void setPosition(const cocos2d::Point &position) override;
    virtual float getRotation() const override;
    virtual void setRotation(float fRotation) override;
    virtual const cocos2d::Mat4& getNodeToParentTransform() const override;
    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentTransformFlags) override;

protected:
    const cocos2d::Point& getPosFromPhysics() const;

    bool    _ignoreBodyRotation;

    // box2d specific
    b2Body  *_pB2Body;
    float   _PTMRatio;
};


#endif // __LFSPRITENODE_H__
