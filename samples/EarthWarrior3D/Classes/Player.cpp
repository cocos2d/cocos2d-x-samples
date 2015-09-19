//
//  Player.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "Player.h"
#include "Bullets.h"
#include "3d/Sprite3D.h"
#include "GameControllers.h"
#include "consts.h"
#include "HelloWorldScene.h"
#include "PublicApi.h"
#include "GameLayer.h"
#include "ParticleManager.h"
#define visible_size_macro Director::getInstance()->getVisibleSize()
#define origin_point Director::getInstance()->getVisibleOrigin();

bool Player::init()
{
    _Model = Sprite3D::create("playerv002.obj", "playerv002_256.png");
    if(_Model)
    {
        _Model->setScale(8);
        addChild(_Model);
        _Model->setRotation3D(Vertex3F(90,0,0));
        _radius = 40;
        _HP = 100;
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        //scheduleUpdate();
        static_cast<Sprite3D*>(_Model)->setOutline(0.2, Color3B(0,0,0));
        schedule(schedule_selector(Player::shootMissile), 1.5, -1, 0);
        schedule(schedule_selector(Player::shoot), 0.075, -1, 0);
        
        // engine trail
        auto part_frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("engine2.jpg");
        ValueMap vm=ParticleManager::getInstance()->GetPlistData("engine");
        auto part = ParticleSystemQuad::create(vm,part_frame);
        addChild(part);
        part->setPosition(0,-30);
        part->setScale(0.6);
        //part->setRotation(90);
        return true;
    }
    return false;
}
void Player::update(float dt)
{
    float smoothedAngle =fmin(fmax(targetAngle*(1-dt*returnSpeed*(rollReturnThreshold-fabsf(targetAngle)/maxRoll)),-maxRoll),maxRoll);
    setRotation3D(Vertex3F(fabsf(smoothedAngle)*0.15,smoothedAngle, 0));
    targetAngle = getRotation3D().y;
}
bool Player::onTouchBegan(Touch *touch, Event *event)
{
    
    return true;
}
void Player::onTouchMoved(Touch *touch, Event *event)
{
    Point prev = event->getCurrentTarget()->getPosition();
    Point delta =touch->getDelta();
    
    setTargetAngle(targetAngle+delta.x*rollSpeed*(rollReturnThreshold-fabsf(targetAngle)/maxRoll));
    
    Point shiftPosition = delta+prev;
  
    setPosition(shiftPosition.getClampPoint(Point(PLAYER_LIMIT_LEFT,PLAYER_LIMIT_BOT),Point(PLAYER_LIMIT_RIGHT,PLAYER_LIMIT_TOP)));
    
    CCLOG("%f %f", shiftPosition.x, shiftPosition.y);
}
void Player::onTouchEnded(Touch *touch, Event *event)
{
}

void Player::shoot(float dt)
{

    BulletController::spawnBullet(kPlayerBullet, getPosition()+Point(-20,20), Point(-200+shootDirection,1600));
    BulletController::spawnBullet(kPlayerBullet, getPosition()+Point(20,20), Point(200+shootDirection,1600));
        BulletController::spawnBullet(kPlayerBullet, getPosition()+Point(0,20), Point(shootDirection,1600));
}

void Player::friendShootLeft()
{
    if (shootDirection > -1000) {
        shootDirection -= 100;
    }
}

void Player::friendShootRight()
{
    if (shootDirection < 1000) {
        shootDirection += 100;
    }
}

void Player::setPosition(Point pos)
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
void Player::shootMissile(float dt)
{
    auto left = BulletController::spawnBullet(kPlayerMissiles, getPosition()+Point(-50,-20), Point(-200,-200));
    left->setRotation(-45);
    auto right = BulletController::spawnBullet(kPlayerMissiles, getPosition()+Point(50,-20), Point(200,-200));
    right->setRotation(45);
}

void Player::stop()
{
    unschedule(schedule_selector(Player::shoot));
    unschedule(schedule_selector(Player::shootMissile));
}
void Player::hideWarningLayer()
{
    setVisible(false);
}
bool Player::hurt(float damage){
    float fromHP = _HP;
    
    _HP-=damage;
    if(_HP>100) _HP = 100;
    float toHP =_HP;
    
    auto fade = FadeTo::create(0.2, 40);
    auto fadeBack = FadeTo::create(0.2, 0);
    auto warningLayer = Director::getInstance()->getRunningScene()->getChildByTag(456);
    warningLayer->setVisible(true);
    warningLayer->runAction(Sequence::create(fade,fadeBack,CallFunc::create(warningLayer, callfunc_selector(Player::hideWarningLayer)),NULL));
    
    auto hpView = ((HelloWorld*)Director::getInstance()->getRunningScene()->getChildByTag(100))->getHPView();
    
    auto to = ProgressFromTo::create(0.5, PublicApi::hp2percent(fromHP), PublicApi::hp2percent(toHP));
    hpView->runAction(to);
    
    if(_HP <= 0  && _alive)
    {
        die();
        return true;
    }

    return false;
}

bool Player::heal(float hp)
{
    hurt(-hp);
}

void Player::die()
{
    _alive = false;
    GameLayer::isDie=true;
    NotificationCenter::getInstance()->postNotification("ShowGameOver",NULL);
}