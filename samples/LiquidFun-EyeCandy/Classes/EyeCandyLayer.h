/*
* Copyright (c) 2013 Google, Inc.
* Copyright (c) 2014 Chukong Technologies Inc.
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef _EYECANDY_LAYER_H_
#define _EYECANDY_LAYER_H_

#include "cocos2d.h"
#include <Box2D/Box2D.h>

class GLESDebugDraw;
class LFParticleSystemNode;

class EyeCandyLayer : public cocos2d::Layer
{
public:
    static EyeCandyLayer* create();

    EyeCandyLayer();
    ~EyeCandyLayer();

    void initPhysics();

    void addNewSpriteAtPosition(cocos2d::Point p);
    void update(float dt);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

protected:

    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t transformFlags) override;
    void onDraw(const cocos2d::Mat4 &transform, uint32_t transformFlags);

    GLESDebugDraw *_debugDraw;
    cocos2d::CustomCommand _customCmd;

    //
    b2World* _world;
    b2ParticleSystem *_particleSystem;
    b2RevoluteJoint *_joint;
    b2Body *_mover;
};

#endif // _EYECANDY_LAYER_H_
