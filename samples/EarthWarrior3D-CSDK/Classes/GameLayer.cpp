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

#include "GameLayer.h"
#include "Player.h"
#include "Enemies.h"
#include "PublicApi.h"
#include "GameControllers.h"
#include "consts.h"
#include "Bullets.h"
//#include "EnemyManager.h"
#include "Effects.h"
#include "GameEntity.h"
#include "SimpleAudioEngine.h"
#include "Effects.h"
#include "ParticleManager.h"
#include "CCFPlayer.h"
#include "json/document.h"
#include "ConnectionInterface.h"
#include "MainMenuScene.h"

USING_NS_CC;
using namespace std;

bool GameLayer::isDie=false;

bool GameLayer::init()
{    
    //************** animation cache ******************
//    auto animation = Animation::create();
//    animation->setDelayPerUnit(0.1);
//    auto texture = Director::getInstance()->getTextureCache()->addImage("player_bullet_explosion.png");
//    animation->addSpriteFrameWithTexture(texture, Rect(0,0,26,17));
//    animation->addSpriteFrameWithTexture(texture, Rect(0,18,26,22));
//    animation->addSpriteFrameWithTexture(texture, Rect(0,40,26,20));
//    animation->addSpriteFrameWithTexture(texture, Rect(0,61,26,23));
//
//    animation->retain();
//    AnimationCache::getInstance()->addAnimation(animation,"bullet_expl");
    
	xScroll = 0.0f;
    speed = -60.0f;
	_elapsed = 20; //testing purpose, this was set to near boss timer
    _bossOut = false;

    _spr = Sprite::create("groundLevel.jpg");
    addChild(_spr, -5);
    Texture2D::TexParams texRepeat = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_REPEAT};
    _spr->getTexture()->setTexParameters(texRepeat);
    setRotation3D(Vec3(-30.0,0.0f,0.0f));
    _spr->setScale(1.4);
    _spr->setPosition(0.0f,400.0f);
    
    _player = Player::create();
    
    _streak = MotionStreak::create(0.4, 1, 15, Color3B(82,255,253), "streak.png");
    _streak ->setBlendFunc(BlendFunc::ADDITIVE);    
    _player->setTrail(_streak);
    addChild(_streak,3);
    auto emission_frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("engine.jpg");
    ValueMap vm_emission=ParticleManager::getInstance()->GetPlistData("emissionPart");
    _emissionPart = ParticleSystemQuad::create(vm_emission);
    //_emissionPart->setDisplayFrame(emission_frame);
    _emissionPart->setTextureWithRect(emission_frame->getTexture(), emission_frame->getRect());
    _player->setEmissionPart(_emissionPart);
    addChild(_emissionPart,4);
    _emissionPart->setPositionType(tPositionType::FREE);
    addChild(_player,5);
    EffectManager::setLayer(this);

    this->schedule(schedule_selector(GameLayer::gameMaster) , 1.5, -1, 2.0);

    BulletController::init(this);
    EnemyController::init(this);
    scheduleUpdate();
    
    
    _player->setPosition(Vec2(0,-1000));
    _player->runAction(Sequence::create(
                                        DelayTime::create(0.75),
                       Spawn::create(
                                     EaseBackOut::create(MoveTo::create(1.7,Vec2(0,-200))),
                                     EaseSineOut::create(RotateBy::create(1.7,Vec3(0,720,0))),
                                     nullptr
                                     ),
                       CallFunc::create(CC_CALLBACK_0(GameLayer::schedulePlayer,this)),nullptr));
    
    if(ConnectionInterface::IsPlayGame())
    {
        _friendPlayer = CCFPlayer::create();
        MotionStreak *_streak1 = MotionStreak::create(0.4, 1, 15, Color3B(82,255,253), "streak.png");
        _friendPlayer->setTrail(_streak1);
        addChild(_streak1,3);

        auto emission_frame1=SpriteFrameCache::getInstance()->getSpriteFrameByName("engine.jpg");
        ValueMap vm_emission1=ParticleManager::getInstance()->GetPlistData("emissionPart");
        ParticleSystemQuad *_emissionPart1 = ParticleSystemQuad::create(vm_emission1);
    
        _friendPlayer->setEmissionPart(_emissionPart1);
        addChild(_emissionPart1,4);
        _emissionPart1->setPositionType(tPositionType::FREE);
        addChild(_friendPlayer,999);
    
        _friendPlayer->setPosition(Point(0,-1000));
        _friendPlayer->runAction(Sequence::create(
                                              DelayTime::create(0.75),
                                              Spawn::create(
                                                            EaseBackOut::create(MoveTo::create(1.7,Point(0,-200))),
                                                            EaseSineOut::create(RotateBy::create(1.7,Vertex3F(0,720,0))),
                                                            nullptr
                                                            ),
                                              CallFunc::create(CC_CALLBACK_0(GameLayer::scheduleFriendPlayer,this)),nullptr));
        
        auto peerListener1 = EventListenerCustom::create("IntelCCFReceiveMessage", CC_CALLBACK_1(GameLayer::listenToReceiveMessage, this));
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(peerListener1, this);
        
        auto peerListener2 = EventListenerCustom::create("IntelCCFDisconnect", CC_CALLBACK_1(GameLayer::listenToDisconnect, this));
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(peerListener2, this);
    }
    else
    {
        _friendPlayer = NULL;
    }
    
    return true;
}

void GameLayer::schedulePlayer()
{
    _player->scheduleUpdate();
}

void GameLayer::scheduleFriendPlayer()
{
    if(_friendPlayer == NULL) return;
    
    _friendPlayer->scheduleUpdate();
}

void GameLayer::gameMaster(float dt)
{
    if(isDie)
    {
        return;
    }
    _elapsed+=dt;
    int enemyCount =EnemyController::enemies.size();
    //if(_elapsed < 10 && enemyCount < 5)
    if(enemyCount < 5 &&_elapsed < 60)
    {
        Vec2 random = Vec2(100*CCRANDOM_MINUS1_1(), BOUND_RECT.size.height/2+200);
        for(int i=0; i < 4; i++)
        {
            auto enemy1 = EnemyController::spawnEnemy(kEnemyFodder);
            enemy1->setPosition(random + Vec2(60,60)*(i+1));
            static_cast<Fodder*>(enemy1)->setMoveMode(moveMode::kDefault);
            auto enemy2 = EnemyController::spawnEnemy(kEnemyFodder);
            enemy2->setPosition(random + Vec2(-60,60)*(i+1));
            static_cast<Fodder*>(enemy2)->setMoveMode(moveMode::kDefault);
            enemy1->setRotation3D(Vec3::ZERO);
            enemy2->setRotation3D(Vec3::ZERO);
        }
        auto leader = EnemyController::spawnEnemy(kEnemyFodderL);
        leader->setPosition(random);
        leader->setRotation3D(Vec3::ZERO);
        static_cast<FodderLeader*>(leader)->setTarget(_player);
        static_cast<FodderLeader*>(leader)->setMoveMode(moveMode::kDefault);
    }
    //else if(_elapsed < 20 && enemyCount <5)
    if(_elapsed > 4 && enemyCount <4 &&_elapsed < 60)
    {
        Vec2 random = Vec2(-400, BOUND_RECT.size.height/4*CCRANDOM_MINUS1_1()+350);
        for(int i=0; i < 3; i++)
        {
            float randomAngle = CCRANDOM_MINUS1_1()*70;
            auto enemy = EnemyController::spawnEnemy(kEnemyFodder);
            enemy->setPosition(random + Vec2(60,60)*(i+1));
            static_cast<Fodder*>(enemy)->setTurnRate(randomAngle*0.5);
            enemy->setRotation(-randomAngle-90);
            auto enemy2 = EnemyController::spawnEnemy(kEnemyFodder);
            enemy2->setPosition(random + Vec2(-60,60)*(i+1));
            static_cast<Fodder*>(enemy2)->setTurnRate(randomAngle*0.5);
            enemy2->setRotation(-randomAngle-90);
        }
        auto leader = EnemyController::spawnEnemy(kEnemyFodderL);
        leader->setPosition(random);
        static_cast<FodderLeader*>(leader)->setTurnRate(45);
        leader->setRotation(-45);
        //enemy->runAction(EaseBackOut::create(MoveTo::create(2, _player->getPosition())));
        static_cast<FodderLeader*>(leader)->setTarget(_player);
        leader->schedule(schedule_selector(FodderLeader::shoot),CCRANDOM_0_1()*1+1,90,0);
        
    }
    if(_elapsed > 10 && enemyCount < 4 &&_elapsed < 60 )
    {
        for(int q = 0; q< 2; q++)
        {
            //random if its from the top, left, or bottom
            int direction = CCRANDOM_0_1()*4;
            float rX, rY;
            switch(direction)
            {
                case 0://top
                    rY = BOUND_RECT.size.height/2+200;
                    rX = ENEMY_BOUND_RECT.size.width*CCRANDOM_0_1();
                    break;
                case 1://bottom
                    rY = -200;
                    rX = ENEMY_BOUND_RECT.size.width*CCRANDOM_0_1();
                    break;
                case 2://left
                    rY = ENEMY_BOUND_RECT.size.height*CCRANDOM_0_1();
                    rX = ENEMY_BOUND_RECT.origin.x;
                    break;
                case 3://right
                    rY = ENEMY_BOUND_RECT.size.height*CCRANDOM_0_1();
                    rX = ENEMY_BOUND_RECT.size.width;
                    break;
            }
            auto enemy = EnemyController::showCaseEnemy(kEnemyBigDude);
            //enemy->setPosition(Vec2(100*CCRANDOM_MINUS1_1(), BOUND_RECT.size.height/2+200));
            enemy->setPosition(rX,rY);
            Vec2 targetPos =Vec2(BOUND_RECT.size.width/3*CCRANDOM_MINUS1_1(),BOUND_RECT.size.height/3*CCRANDOM_0_1());
            enemy->setScale(2*CCRANDOM_MINUS1_1()+2);
            float randomTime = CCRANDOM_0_1()*1+1;
            enemy->setRotation3D(Vec3(300,0,-CC_RADIANS_TO_DEGREES((enemy->getPosition()-targetPos).getAngle())+90));
            enemy->runAction(
                             Sequence::create(
                                              Spawn::create(
                                                            EaseSineOut::create(MoveTo::create(randomTime, targetPos)),
                                                            EaseSineOut::create(ScaleTo::create(randomTime,1)),//TODO: replace with move 3d when possible
                                                            EaseBackOut::create(RotateBy::create(randomTime+0.2,Vec3(-300,0,0))),
                                                            nullptr
                                                            ),
                                              CallFunc::create(CC_CALLBACK_0(BigDude::showFinished, static_cast<BigDude*>(enemy))),
                                              nullptr
                             ));
        }
    }
    if(_elapsed > 65 && !_bossOut)
    {
        //spawn boss
        _bossOut = true;
        auto boss = EnemyController::spawnEnemy(kEnemyBoss);
        boss->setPosition(0,800);
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        // Music By Matthew Pable (http://www.matthewpablo.com/)
        // Licensed under CC-BY 3.0 (http://creativecommons.org/licenses/by/3.0/)
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Orbital Colossus_0.mp3", true);
    }
}

void GameLayer::update(float dt)
{
    xScroll += speed*dt;
    _spr->setTextureRect(Rect(0,((int)xScroll)%2048,512,1200));
    //_cloud->setTextureRect(Rect(0,((int)xScroll)%1024, 256, 1024));
    if (!isDie) {
        GameController::update(dt, _player);
        GameController::update(dt, _friendPlayer);
    }
    else
    {
        if (_player) {
            _player->stop();
            removeChild(_player);
            _player=NULL;
            removeChild(_streak);
            _streak=NULL;
            removeChild(_emissionPart);
            _emissionPart=NULL;
            //scheduleOnce(schedule_selector(GameLayer::removeBulletAndEnmeys), 1/60);
            stopAllActions();
            unscheduleAllSelectors();
        }
        
        if (_friendPlayer) {
            _friendPlayer->stop();
            
            removeChild(_friendPlayer->getTrail());
            removeChild(_friendPlayer->getEmissionPart());
            removeChild(_friendPlayer);
            _friendPlayer=NULL;
        }
    }
}

void GameLayer::removeBulletAndEnmeys(float dt)
{
    for(int i=EnemyController::enemies.size()-1;i>=0;i--)
    {
        EnemyController::erase(i);
    }
    for(int i=EnemyController::showCaseEnemies.size()-1;i>=0;i--)
    {
        //EnemyController::erase(i);
        EnemyController::showCaseEnemies.at(i)->removeFromParentAndCleanup(false);
        EnemyController::showCaseEnemies.erase(i);
    }
    for(int i=BulletController::bullets.size()-1;i>=0;i--)
    {
        BulletController::erase(i);
    }
}


void GameLayer::listenToReceiveMessage(EventCustom* event)
{
    this->scheduleOnce(schedule_selector(GameLayer::scheduleReceiveMessage), 0);
}

void GameLayer::scheduleReceiveMessage(float dt)
{
    if(_friendPlayer == NULL) return;
    
    std::list<std::string>::iterator iter;
    std::list<std::string> listMessage;
    ConnectionInterface::getMessageList(listMessage);
    
    rapidjson::Document doc;
    
    while (listMessage.size()) {
        std::string msg = listMessage.front();
        listMessage.pop_front();
        
        doc.Parse<rapidjson::kParseDefaultFlags>(msg.c_str());
        if(doc.HasParseError() != 0) continue;
        
        if (doc.HasMember("type") && doc.HasMember("prevX") && doc.HasMember("prevY") && doc.HasMember("deltaX") && doc.HasMember("deltaY")
            && doc["type"].IsInt() && doc["prevX"].IsDouble() && doc["prevY"].IsDouble() && doc["deltaX"].IsDouble() && doc["deltaY"].IsDouble())
        {
            _friendPlayer->touchMoved(Point(doc["prevX"].GetDouble(), doc["prevY"].GetDouble()), Point(doc["deltaX"].GetDouble(), doc["deltaY"].GetDouble()));
        }
    }
}

void GameLayer::listenToDisconnect(EventCustom *event)
{
    this->scheduleOnce(schedule_selector(GameLayer::scheduleDisconnect), 0);
}

void GameLayer::scheduleDisconnect(float dt)
{
    auto helloworld = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(helloworld);
}

