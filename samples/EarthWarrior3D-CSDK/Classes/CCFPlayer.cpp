/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://github.com/chukong/EarthWarrior3D
 
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

#include "CCFPlayer.h"
#include "Bullets.h"
#include "GameControllers.h"
#include "consts.h"
#include "HelloWorldScene.h"
#include "PublicApi.h"
#include "GameLayer.h"
#include "ParticleManager.h"
#include "Sprite3DEffect.h"
#include "ConnectionInterface.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif

#define visible_size_macro Director::getInstance()->getVisibleSize()
#define origin_point Director::getInstance()->getVisibleOrigin();

const float CCFPlayer::rollSpeed = 1.5;// recommended 1.5
const float CCFPlayer::returnSpeed = 10;// recommended 4
const float CCFPlayer::maxRoll = 75;
const float CCFPlayer::rollReturnThreshold = 1.02;

bool CCFPlayer::init()
{
    _Model = EffectSprite3D::createFromObjFileAndTexture("playerv002.c3b", "playerv002_256.png");
    if(_Model)
    {
		targetAngle = 0;
		targetPos = Vec2(0,0);
		_trailOffset = Vec2(0,-40);

        _Model->setScale(8);
        addChild(_Model);
       // _Model->setRotation3D(Vec3(90,0,0));
        _radius = 40;
        _HP = 100;
        _alive = true;
        
        GameEntity::UseOutlineEffect(static_cast<Sprite3D*>(_Model), 0.02, Color3B(0,0,0));
        
        if(ConnectionInterface::IsPlayGame())
        {
            schedule(schedule_selector(CCFPlayer::shootMissile), 1.5, -1, 0);
            schedule(schedule_selector(CCFPlayer::shoot), 0.075, -1, 0);
            
            // engine trail
            auto part_frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("engine2.jpg");
            ValueMap vm=ParticleManager::getInstance()->GetPlistData("engine");
            auto part = ParticleSystemQuad::create(vm);
            part->setTextureWithRect(part_frame->getTexture(), part_frame->getRect());
            addChild(part);
            part->setPosition(0,-30);
            part->setScale(0.6);
            //part->setRotation(90);
        }
        
        return true;
    }
    return false;
}
void CCFPlayer::update(float dt)
{
    float smoothedAngle =std::min(std::max(targetAngle*(1-dt*returnSpeed*(rollReturnThreshold-fabsf(targetAngle)/maxRoll)),-maxRoll),maxRoll);
    setRotation3D(Vec3(fabsf(smoothedAngle)*0.15,smoothedAngle, 0));
    targetAngle = getRotation3D().y;
}

void CCFPlayer::touchMoved(Point prev, Point delta)
{
    if(!ConnectionInterface::IsPlayGame()) return;
    
    Point _prev = getPosition();
    
    Point shiftPosition = delta+_prev;
    
    setTargetAngle(targetAngle+delta.x*rollSpeed*(rollReturnThreshold-fabsf(targetAngle)/maxRoll));
    
    setPosition(shiftPosition.getClampPoint(Point(PLAYER_LIMIT_LEFT,PLAYER_LIMIT_BOT),Point(PLAYER_LIMIT_RIGHT,PLAYER_LIMIT_TOP)));
}

void CCFPlayer::shoot(float dt)
{
    BulletController::spawnBullet(kPlayerBullet, getPosition()+Vec2(-20,20), Vec2(-200,1600));
    BulletController::spawnBullet(kPlayerBullet, getPosition()+Vec2(20,20), Vec2(200,1600));
        BulletController::spawnBullet(kPlayerBullet, getPosition()+Vec2(0,20), Vec2(0,1600));
}
void CCFPlayer::setPosition(Vec2 pos)
{
    if (_position.equals(pos))
        return;
    
    _position = pos;
    _transformUpdated = _transformDirty = _inverseDirty = true;
    if(_streak)
    {
        _streak->setPosition(pos+_trailOffset);
    }
    if(_emissionPart)
    {
        _emissionPart->setPosition(pos);
    }
}
void CCFPlayer::shootMissile(float dt)
{
    auto left = BulletController::spawnBullet(kPlayerMissiles, getPosition()+Vec2(-50,-20), Vec2(-200,-200));
    left->setRotation(-45);
    auto right = BulletController::spawnBullet(kPlayerMissiles, getPosition()+Vec2(50,-20), Vec2(200,-200));
    right->setRotation(45);
}

void CCFPlayer::stop()
{
    unschedule(schedule_selector(CCFPlayer::shoot));
    unschedule(schedule_selector(CCFPlayer::shootMissile));
}
void CCFPlayer::hideWarningLayer(Node* node)
{
    if(node)
        node->setVisible(false);
}
bool CCFPlayer::hurt(float damage){
    float fromHP = _HP;
    float toHP = _HP-=damage;
    
    auto fade = FadeTo::create(0.2, 40);
    auto fadeBack = FadeTo::create(0.2, 0);
    auto warningLayer = Director::getInstance()->getRunningScene()->getChildByTag(456);
    warningLayer->setVisible(true);
    warningLayer->runAction(Sequence::create(fade,fadeBack,
                                             CallFunc::create(
                                                              CC_CALLBACK_0(CCFPlayer::hideWarningLayer, this, warningLayer)
                                                              ),NULL));
    
//    auto hpView = ((HelloWorld*)Director::getInstance()->getRunningScene()->getChildByTag(100))->getHPView();
//    
//    auto to = ProgressFromTo::create(0.5, PublicApi::hp2percent(fromHP), PublicApi::hp2percent(toHP));
//    hpView->runAction(to);
//    
    if(_HP <= 0  && _alive)
    {
        die();
        return true;
    }

    return false;
}

void CCFPlayer::die()
{
    _alive = false;
    GameLayer::isDie=true;
    NotificationCenter::getInstance()->postNotification("ShowGameOver",NULL);
}