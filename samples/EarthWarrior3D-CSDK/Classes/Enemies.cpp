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

#include "Enemies.h"
#include "GameControllers.h"
#include "Bullets.h"
#include "consts.h"
#include "SimpleAudioEngine.h"
#include "Effects.h"
#include "HelloWorldScene.h"
#include "GameLayer.h"
#include "Sprite3DEffect.h"

bool Fodder::init()
{
    _score = 10;
	_alive = true;
    _Model = EffectSprite3D::createFromObjFileAndTexture("dijiyuanv001.c3b", "dijiyuanv001.png");
    if(_Model)
    {
        _Model->setScale(6);
        addChild(_Model);
        _Model->setRotation3D(Vec3(90,0,0));
        GameEntity::UseOutlineEffect(static_cast<Sprite3D*>(_Model), 0.02, Color3B(0,0,0));
        _type = kEnemyFodder;
        _HP = 10;
        _radius = 30;
        return true;
    }
    return false;
}
void Fodder::reset()
{
    AirCraft::reset();
    _target = nullptr;
    _HP = 10;
}
void Fodder::setTurnRate(float turn)
{
    setMoveMode(moveMode::kTurn);
    setRotation3D(Vec3(fabsf(turn)*0.15, turn, 0));
    _turn = turn;
}
float Fodder::getTurnRate()
{
    return _turn;
}
void Fodder::move(float y, float dt)
{
switch(_moveMode)
    {
        case moveMode::kTurn:
            forward(y, getTurnRate()*dt);
            break;
        default:
            //setPosition(getPosition()+pos);
            forward(y);
    }

}
void Fodder::shoot(float dt)
{
    if(!GameLayer::isDie && _target->alive())
    {
        //get angle to player;
        float angle = (getPosition()-_target->getPosition()).getAngle();
        auto bullet =BulletController::spawnBullet(kEnemyBullet, getPosition(), Vec2(cosf(angle)*-500, sinf(angle)*-500));
        //auto bullet =BulletController::spawnBullet(kEnemyBullet, getPosition(), Vec2(0,-500));
        bullet->setRotation(-CC_RADIANS_TO_DEGREES(angle)-90);
        //log("aaaaaaa");
    }
    else{
        //log("player is dead,hahahaha");
    }
}


bool FodderLeader::init()
{
    _score = 20;
	_alive = true;
    _Model = EffectSprite3D::createFromObjFileAndTexture("dijiyuanv001.c3b", "dijiyuanv001.png");
    if(_Model)
    {
        _Model->setScale(8);
        addChild(_Model);
        _Model->setRotation3D(Vec3(90,0,0));
        GameEntity::UseOutlineEffect(static_cast<Sprite3D*>(_Model), 0.02, Color3B(255,0,0));
        _type = kEnemyFodderL;
        _HP = 20;
        _radius = 35;
        return true;
    }
    return false;
}
void FodderLeader::reset()
{
    AirCraft::reset();
    _HP = 25;
}


bool BigDude::init()
{
    _score = 20;
	_alive = true;
	_turnRate = 50;
    _Model = EffectSprite3D::createFromObjFileAndTexture("diji1_v002.c3b", "diji02_v002_128.png");
    if(_Model)
    {
        _Model->setScale(8);
        addChild(_Model);
       // _Model->setRotation3D(Vec3(90,0,0));
        //static_cast<Sprite3D*>(_Model)->setOutline(0.2, Color3B::BLACK);
        GameEntity::UseOutlineEffect(static_cast<Sprite3D*>(_Model), 0.02, Color3B::BLACK);
        _type = kEnemyBigDude;
        _HP = 30;
        _radius = 40;
        
        
        return true;
    }
    return false;
}

void BigDude::reset()
{
    AirCraft::reset();
    _HP = 30;
    //_targetPos = nullptr;
}

void BigDude::showFinished()
{
    //remove from show Vector, add to the enemy Vector
    EnemyController::enemies.pushBack(this);
    EnemyController::showCaseEnemies.eraseObject(this);
    schedule(schedule_selector(BigDude::shoot),CCRANDOM_0_1()*2+1, 90, 0);
}
void BigDude::shoot(float dt)
{
    if(GameLayer::isDie)
    {
        unschedule(schedule_selector(BigDude::shoot));
        return;
    }
    //Point bulletVec = Vec2(getRotation())
    
    Vec2 offset1 = getPosition();
    Vec2 offset2 = offset1;
    float angle = CC_DEGREES_TO_RADIANS(-getRotation()+90);
    float offsetRad = CC_DEGREES_TO_RADIANS(45);
    offset1.x += cosf(angle+offsetRad)*-50;
    offset1.y += sinf(angle+offsetRad)*-50;
    offset2.x += cosf(angle-offsetRad)*-50;
    offset2.y += sinf(angle-offsetRad)*-50;
    //this->showMuzzle();
    auto bullet =BulletController::spawnBullet(kEnemyBullet, offset1, Vec2(cosf(angle)*-500, sinf(angle)*-500));
    bullet->setRotation(-CC_RADIANS_TO_DEGREES(angle)-90);
    bullet =BulletController::spawnBullet(kEnemyBullet, offset2, Vec2(cosf(angle)*-500, sinf(angle)*-500));
    bullet->setRotation(-CC_RADIANS_TO_DEGREES(angle)-90);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("boom.mp3");
}

void BigDude::update(float dt, Node* player)
{
    //find angle difference
    float angleRad = (getPosition()-player->getPosition()).getAngle();
    float angleDeg = -CC_RADIANS_TO_DEGREES(angleRad)+180;
    float curRot = getRotation();
    float angleDif = std::min(std::max((angleDeg-90) - curRot, -_turnRate*dt), _turnRate*dt);
    
    float f = curRot + angleDif;
    setRotation(f);
}

void BigDude::showMuzzle()
{
    muzzle1 = Sprite::create("muzzle.png");
    muzzle2 = Sprite::create("muzzle.png");
    muzzle1->setScale(0.4);
    muzzle2->setScale(0.4);
    
    Vec2 offset1 = Vec2::ZERO;
    Vec2 offset2 = offset1;
    float angle = 90;
    float offsetRad = CC_DEGREES_TO_RADIANS(45);
    offset1.x += cosf(offsetRad+angle)*-50;
    offset1.y += sinf(offsetRad+angle)*-50;
    offset2.x += cosf(-offsetRad+angle)*-50;
    offset2.y += sinf(-offsetRad+angle)*-50;
    
    muzzle1->setPosition(offset1);
    muzzle2->setPosition(offset2);
    muzzle1->setRotation(-35.0f);
    muzzle2->setRotation(-35.0f);
    this->addChild(muzzle1);
    this->addChild(muzzle2);
    this->scheduleOnce(schedule_selector(BigDude::dismissMuzzle), 0.1);
}

void BigDude::dismissMuzzle(float dt)
{
    muzzle1->removeFromParent();
    muzzle2->removeFromParent();
}

void BigDude::die()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("boom2.mp3");
    this->_alive = false;
    EnemyController::enemies.eraseObject(this);
    EnemyController::showCaseEnemies.pushBack(this);
    EffectManager::createExplosion(getPosition());
    Vec2 nowPoint = this->getPosition();
    log("now X: %f Y:%f \n",nowPoint.x,nowPoint.y);
    Vec2 targetPos = Vec2(nowPoint.x,nowPoint.y-200);
    log("now X: %f Y:%f \n",targetPos.x,targetPos.y);
    unscheduleAllSelectors();
    this->runAction(
                     Sequence::create(
                                      Spawn::create(
                                                    EaseSineOut::create(MoveTo::create(2, targetPos)),
                                                    EaseSineOut::create(ScaleTo::create(2,0.3)),//TODO: replace with move 3d when possible
                                                    //EaseBackOut::create(RotateBy::create(2,Vec3(CC_RADIANS_TO_DEGREES((nowPoint-targetPos).getAngle()),CC_RADIANS_TO_DEGREES((nowPoint-targetPos).getAngle())+45,-CC_RADIANS_TO_DEGREES((nowPoint-targetPos).getAngle())+90))),
                                                    RotateBy::create(2, Vec3(360+CCRANDOM_0_1()*600, 360+CCRANDOM_0_1()*600, 360+CCRANDOM_0_1()*600)),
                                                    nullptr
                                                    ),
                                      CallFunc::create(CC_CALLBACK_0(BigDude::fall, this)),
                                      nullptr
                                      ));


}

void BigDude::fall()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explodeEffect.mp3");
    EffectManager::createBigExplosion(getPosition());
    auto helloworld = (HelloWorld*)Director::getInstance()->getRunningScene()->getChildByTag(100);
    int score = helloworld->getScore();
    helloworld->setScore(score+=_score);
    std::stringstream ss;
    std::string str;
    ss<<score;
    ss>>str;
    const char *p = str.c_str();
    helloworld->getScoreLabel()->setString(p);
    _alive = false;
    auto scale = ScaleTo::create(0.1, 1.2);
    auto scaleBack = ScaleTo::create(0.1, 1);
    auto label = helloworld->getScoreLabel();
    label->runAction(Sequence::create(scale, scaleBack,NULL));
    this->removeFromParentAndCleanup(false);
    EnemyController::_bigDudePool.pushBack(this);
    EnemyController::showCaseEnemies.eraseObject(this);
    reset();
}

bool Boss::init()
{
    _score = 666;
	_alive = true;
    _Model = EffectSprite3D::createFromObjFileAndTexture("boss.c3b", "boss.png");
    //auto cannon2 = Sprite3D::create("bossCannon.obj", "boos.png");
    if(_Model)
    {
        _Model->setScale(28);
        addChild(_Model);
       // _Model->setRotation3D(Vec3(90,0,0));
        GameEntity::UseOutlineEffect(static_cast<Sprite3D*>(_Model), 0.02, Color3B::BLACK);
        _type = kEnemyBoss;
        _HP = 5000;
        _radius = 150;
        auto cannon1 = EffectSprite3D::createFromObjFileAndTexture("bossCannon.c3b", "boss.png");
        _Cannon1 = Node::create();
        addChild(_Cannon1);
        _Cannon1->addChild(cannon1);
        cannon1->setScale(28);
        //cannon1->setRotation3D(Vec3(90,0,0));
        _Cannon1->setPosition3D(Vec3(40,-100, 10));
        GameEntity::UseOutlineEffect(static_cast<Sprite3D*>(cannon1), 0.02, Color3B(0,0,0));
        auto cannon2 = EffectSprite3D::createFromObjFileAndTexture("bossCannon.c3b", "boss.png");
        _Cannon2 = Node::create();
        addChild(_Cannon2);
        _Cannon2->addChild(cannon2);
        cannon2->setScale(28);
        //cannon2->setRotation3D(Vec3(90,0,0));
        _Cannon2->setPosition3D(Vec3(-40,-100, 10));
        GameEntity::UseOutlineEffect(static_cast<Sprite3D*>(cannon2), 0.02, Color3B(0,0,0));
        //addChild(_Cannon2);
        //_Cannon2->setPosition(-20,-200);
        
        _Cannon1->setRotation(-45);
        _Cannon2->setRotation(45);
        
                enterTheBattle();
        return true;
    }
    return false;
}

void Boss::enterTheBattle()
{
    setRotation3D(Vec3(100,0,0));
    setScale(0.2);
    runAction(
              Sequence::create(
                               Spawn::create(
                                             EaseSineOut::create(MoveTo::create(4, Vec2(0,300))),
                                             EaseSineOut::create(ScaleTo::create(4,1)),//TODO: replace with move 3d when possible
                                             EaseBackOut::create(RotateBy::create(4+0.5,Vec3(-100,0,0))),
                                             nullptr
                                             ),                                             CallFunc::create(std::bind(static_cast<void(Boss::*)(void)>(&Boss::startShooting), this)),
                               CallFunc::create(CC_CALLBACK_0(Boss::_turns,this)),
                               nullptr
                               ));
}

void Boss::_turns()
{
    runAction
    (
                    Sequence::create
                    (
                        EaseSineInOut::create(MoveBy::create(2, Vec2(200,0))),
                        EaseSineInOut::create(MoveBy::create(4, Vec2(-400,0))),
                        EaseSineInOut::create(MoveBy::create(2, Vec2(200,0))),
                    nullptr)
     );
    
    runAction(
              Sequence::create(
                               EaseQuadraticActionInOut::create(RotateBy::create(1,-20)),
                               EaseQuadraticActionInOut::create(RotateBy::create(2,40)),
                               DelayTime::create(2),
                               EaseQuadraticActionInOut::create(RotateBy::create(2,-40)),
                               EaseQuadraticActionInOut::create(RotateBy::create(1,20)),
                               DelayTime::create(2),
                               CallFunc::create(CC_CALLBACK_0(Boss::_next, this)),
                               nullptr
              )
    );
}

void Boss::_next()
{
    int random = CCRANDOM_0_1()*2;
    switch(random)
    {
        case 0:
            _turns();
            break;
        case 1:
            _dash();
            break;
        default:
            _dash();
            break;
    }
}

void Boss::_dash()
{
    int neg = (CCRANDOM_0_1()>0.5)? -1: 1;
    
    auto array = PointArray::create(6);
    
    array->addControlPoint(Vec2(0,0));
    array->addControlPoint(Vec2(80*neg,-300));
    array->addControlPoint(Vec2(500*neg,-900));
    array->addControlPoint(Vec2(700*neg,-600));
    array->addControlPoint(Vec2(500*neg,400));
    array->addControlPoint(Vec2(0,0));
    
    auto action = CardinalSplineBy::create(5.5, array,0);
    runAction(Sequence::create(
                               DelayTime::create(0.5),
                               EaseSineOut::create(action)
                               ,nullptr)
              );
    runAction(
              Sequence::create(
                               EaseSineInOut::create(RotateBy::create(0.5, Vec3(0,30*neg,0))),
                               RotateBy::create(2.5, Vec3(-30,45*neg,-90*neg)),
                                RotateBy::create(1, Vec3(0,-35*neg,-200*neg)),
                               EaseSineInOut::create(RotateBy::create(1.5, Vec3(30,-40*neg,-70*neg))),
                               CallFunc::create(CC_CALLBACK_0(Boss::_next, this)),
              nullptr)
              );
}

void Boss::startShooting()
{
    log("startShooting");
     schedule(schedule_selector(Boss::shoot),0.15, 6, 0);

}

void Boss::startShooting(float dt)
{
    if(GameLayer::isDie)
    {
        unschedule(schedule_selector(Boss::startShooting));
        return;
    }
    log("startShooting fd");
    startShooting();

}

void Boss::createRandomExplosion()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explodeEffect.mp3");
    EffectManager::createBigExplosion(getPosition()+Vec2(CCRANDOM_MINUS1_1()*200, CCRANDOM_MINUS1_1()*200));
}

void Boss::dying()
{
    _alive = false;
    EnemyController::showCaseEnemies.pushBack(this);
    EnemyController::enemies.eraseObject(this);
}

void Boss::dead()
{
    auto helloworld = (HelloWorld*)Director::getInstance()->getRunningScene()->getChildByTag(100);
    int score = helloworld->getScore();
    helloworld->setScore(score+=_score);
    std::stringstream ss;
    std::string str;
    ss<<score;
    ss>>str;
    const char *p = str.c_str();
    helloworld->getScoreLabel()->setString(p);
    auto scale = ScaleTo::create(0.1, 1.2);
    auto scaleBack = ScaleTo::create(0.1, 1);
    auto label =helloworld->getScoreLabel();
    label->runAction(Sequence::create(scale, scaleBack,NULL));
    EnemyController::showCaseEnemies.eraseObject(this);
    removeFromParent();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    NotificationCenter::getInstance()->postNotification("ShowGameOver",NULL);
    scheduleOnce(schedule_selector(Boss::_endGame), 1.5);
}

void Boss::_endGame(float dt)
{
    NotificationCenter::getInstance()->postNotification("ShowGameOver",NULL);
}

void Boss::die()
{
    //sequence to 10 random explosion
    stopAllActions();
    Vector<FiniteTimeAction*> explosions;
    for(int i = 0; i < 22; i++)
    {
        auto expl = CallFunc::create(CC_CALLBACK_0(Boss::createRandomExplosion,this));
        auto delay = DelayTime::create(i*0.15);
        auto seq = Sequence::create(delay, expl, nullptr);
        explosions.pushBack(seq);
    }
    auto giantExpl = Spawn::create(explosions);
    Vector<FiniteTimeAction*> explosions2;
    for(int i = 0; i < 15; i++)
    {
        auto expl = CallFunc::create(CC_CALLBACK_0(Boss::createRandomExplosion,this));
        explosions2.pushBack(expl);
    }
    auto giantExpl2 = Spawn::create(explosions2);
    auto callDead = CallFunc::create(CC_CALLBACK_0(Boss::dead,this));
    auto final = Sequence::create(giantExpl, giantExpl2, callDead,nullptr);
    runAction(final);
    dying();
    
}

Vec2 Boss::_getCannon1Position()
{
    Vec2 offset = getPosition();
    float angle = CC_DEGREES_TO_RADIANS(-getRotation()+90);
    float offsetRad = CC_DEGREES_TO_RADIANS(28);
    offset.x += cosf(angle+offsetRad)*-100;
    offset.y += sinf(angle+offsetRad)*-100;
    return offset;
}

Vec2 Boss::_getCannon2Position()
{
    Vec2 offset = getPosition();
    float angle = CC_DEGREES_TO_RADIANS(-getRotation()+90);
    float offsetRad = CC_DEGREES_TO_RADIANS(28);
    offset.x += cosf(angle-offsetRad)*-100;
    offset.y += sinf(angle-offsetRad)*-100;
    return offset;
}

Vec2 Boss::_getCannon1Vector()
{
    float angle = CC_DEGREES_TO_RADIANS(-_Cannon1->getRotation()+90-getRotation());
    return Vec2(cosf(angle)*-500, sinf(angle)*-500);
}

Vec2 Boss::_getCannon2Vector()
{
    float angle = CC_DEGREES_TO_RADIANS(-_Cannon2->getRotation()+90-getRotation());
    return Vec2(cosf(angle)*-500, sinf(angle)*-500);
}

void Boss::showMuzzle()
{
    muzzle1 = Sprite::create("muzzle.png");
    muzzle2 = Sprite::create("muzzle.png");
    muzzle1->setScale(0.4);
    muzzle2->setScale(0.4);
    muzzle1->setPosition(3,-30);
    muzzle2->setPosition(3,-30);
    muzzle1->setRotation(-35.0f);
    muzzle2->setRotation(-35.0f);
    _Cannon1->addChild(muzzle1);
    _Cannon2->addChild(muzzle2);
    this->scheduleOnce(schedule_selector(Boss::dismissMuzzle), 0.1);
}

void Boss::dismissMuzzle(float dt){
    muzzle1->removeFromParent();
    muzzle2->removeFromParent();
}

void Boss::shoot(float dt)
{
    if (GameLayer::isDie) {
        return;
    }
    auto bullet =BulletController::spawnBullet(kEnemyBullet, _getCannon1Position(), _getCannon1Vector());
    
    showMuzzle();
    
    bullet->setRotation(_Cannon1->getRotation()+180);
    bullet =BulletController::spawnBullet(kEnemyBullet, _getCannon2Position(), _getCannon2Vector());
    bullet->setRotation(_Cannon2->getRotation()+180);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("boom.mp3");
    schedule(schedule_selector(Boss::startShooting),1, 0, 3);
}
void Boss::update(float dt, Node* player)
{
    float angleRad = (_getCannon1Position()-player->getPosition()).getAngle();
    float angleDeg = -CC_RADIANS_TO_DEGREES(angleRad)+90;
    _Cannon1->setRotation(angleDeg-getRotation());
    
    
    angleRad = (_getCannon2Position()-player->getPosition()).getAngle();
    angleDeg = -CC_RADIANS_TO_DEGREES(angleRad)+90;
    _Cannon2->setRotation(angleDeg-getRotation());

}