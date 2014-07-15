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

#include "LFSpriteNode.h"

using namespace cocos2d;

LFSpriteNode::LFSpriteNode()
: _ignoreBodyRotation(false)
, _pB2Body(nullptr)
, _PTMRatio(0.0f)
{}

LFSpriteNode* LFSpriteNode::create()
{
    LFSpriteNode* pRet = new LFSpriteNode();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

LFSpriteNode* LFSpriteNode::createWithTexture(Texture2D *pTexture)
{
    LFSpriteNode* pRet = new LFSpriteNode();
    if (pRet && pRet->initWithTexture(pTexture))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

LFSpriteNode* LFSpriteNode::createWithTexture(Texture2D *pTexture, const Rect& rect)
{
    LFSpriteNode* pRet = new LFSpriteNode();
    if (pRet && pRet->initWithTexture(pTexture, rect))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

LFSpriteNode* LFSpriteNode::createWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
    LFSpriteNode* pRet = new LFSpriteNode();
    if (pRet && pRet->initWithSpriteFrame(pSpriteFrame))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

LFSpriteNode* LFSpriteNode::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    LFSpriteNode* pRet = new LFSpriteNode();
    if (pRet && pRet->initWithSpriteFrameName(pszSpriteFrameName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

LFSpriteNode* LFSpriteNode::create(const char *pszFileName)
{
    LFSpriteNode* pRet = new LFSpriteNode();
    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

LFSpriteNode* LFSpriteNode::create(const char *pszFileName, const Rect& rect)
{
    LFSpriteNode* pRet = new LFSpriteNode();
    if (pRet && pRet->initWithFile(pszFileName, rect))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

// this method will only get called if the sprite is batched.
// return YES if the physic's values (angles, position ) changed.
// If you return NO, then getNodeToParentTransform won't be called.
bool LFSpriteNode::isDirty() const
{
    return true;
}

bool LFSpriteNode::isIgnoreBodyRotation() const
{
    return _ignoreBodyRotation;
}

void LFSpriteNode::setIgnoreBodyRotation(bool bIgnoreBodyRotation)
{
    _ignoreBodyRotation = bIgnoreBodyRotation;
}

// Override the setters and getters to always reflect the body's properties.
const Point& LFSpriteNode::getPosition() const
{
    return getPosFromPhysics();
}

void LFSpriteNode::getPosition(float* x, float* y) const
{
    if (x == NULL || y == NULL) {
        return;
    }
    const Point& pos = getPosFromPhysics();
    *x = pos.x;
    *y = pos.y;
}

float LFSpriteNode::getPositionX() const
{
    return getPosFromPhysics().x;
}

float LFSpriteNode::getPositionY() const
{
    return getPosFromPhysics().y;
}

//
// Chipmunk only
//



b2Body* LFSpriteNode::getB2Body() const
{
    return _pB2Body;
}

void LFSpriteNode::setB2Body(b2Body *pBody)
{
    _pB2Body = pBody;
}

float LFSpriteNode::getPTMRatio() const
{
    return _PTMRatio;
}

void LFSpriteNode::setPTMRatio(float fRatio)
{
    _PTMRatio = fRatio;
}

//
// Common to Box2d and Chipmunk
//

const Point& LFSpriteNode::getPosFromPhysics() const
{
    static Point s_physicPosion;

    b2Vec2 pos = _pB2Body->GetPosition();
    float x = pos.x * _PTMRatio;
    float y = pos.y * _PTMRatio;
    s_physicPosion = Point(x,y);
    return s_physicPosion;
}

void LFSpriteNode::setPosition(const Point &pos)
{
    float angle = _pB2Body->GetAngle();
    _pB2Body->SetTransform(b2Vec2(pos.x / _PTMRatio, pos.y / _PTMRatio), angle);
}

float LFSpriteNode::getRotation() const
{
    return (_ignoreBodyRotation ? Sprite::getRotation() :
            CC_RADIANS_TO_DEGREES(_pB2Body->GetAngle()));
}

void LFSpriteNode::setRotation(float fRotation)
{
    if (_ignoreBodyRotation)
    {
        Sprite::setRotation(fRotation);
    }
    else
    {
        b2Vec2 p = _pB2Body->GetPosition();
        float radians = CC_DEGREES_TO_RADIANS(fRotation);
        _pB2Body->SetTransform(p, radians);
    }
}

void LFSpriteNode::visit(Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentTransformFlags)
{
    // box2d controls the position, so set the transform as dirty
    _transformUpdated = true;
    Sprite::visit(renderer, parentTransform, parentTransformFlags);
}

// returns the transform matrix according the Chipmunk Body values
const cocos2d::Mat4& LFSpriteNode::getNodeToParentTransform() const
{
    // Although scale is not used by physics engines, it is calculated just in case
	// the sprite is animated (scaled up/down) using actions.
	// For more info see: http://www.cocos2d-iphone.org/forum/topic/68990

    b2Vec2 pos  = _pB2Body->GetPosition();

	float x = pos.x * _PTMRatio;
	float y = pos.y * _PTMRatio;

	if (_ignoreAnchorPointForPosition)
    {
		x += _anchorPointInPoints.x;
		y += _anchorPointInPoints.y;
	}

	// Make matrix
	float radians = _pB2Body->GetAngle();
	float c = cosf(radians);
	float s = sinf(radians);

	if (!_anchorPointInPoints.equals(Point::ZERO))
    {
		x += ((c * -_anchorPointInPoints.x * _scaleX) + (-s * -_anchorPointInPoints.y * _scaleY));
		y += ((s * -_anchorPointInPoints.x * _scaleX) + (c * -_anchorPointInPoints.y * _scaleY));
	}

	// Rot, Translate Matrix

    float mat[] = {  (float)c * _scaleX, (float)s * _scaleX, 0,  0,
        (float)-s * _scaleY, (float)c * _scaleY,  0,  0,
        0,  0,  1,  0,
        x,	y,  0,  1};

    _transform = Mat4(mat);

	return _transform;
}
