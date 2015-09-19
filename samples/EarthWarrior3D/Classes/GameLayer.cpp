//
//  ScrollingBackground.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/24/14.
//
//

#include "GameLayer.h"
#include "Player.h"
#include "FriendPlayer.h"
#include "Enemies.h"
#include "Reward.h"
#include "PublicApi.h"
#include "GameControllers.h"
#include "consts.h"
#include "Bullets.h"
#include "Effects.h"
#include "GameEntity.h"
#include "SimpleAudioEngine.h"
#include "Effects.h"
#include "ParticleManager.h"
#include "json/document.h"

USING_NS_CC;
using namespace std;

bool GameLayer::isDie=false;

bool GameLayer::init()
{    
    _spr = Sprite::create("groundLevel.jpg");
    addChild(_spr, -5);
    Texture2D::TexParams texRepeat = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_REPEAT};
    _spr->getTexture()->setTexParameters(texRepeat);
    setRotation3D(Vertex3F(-30.0,0.0f,0.0f));
    _spr->setScale(1.4);
    _spr->setPosition(0.0f,400.0f);
    
    _player = Player::create();
    _streak = MotionStreak::create(0.4, 1, 15, Color3B(82,255,253), "streak.png");
    _player->setTrail(_streak);
    addChild(_streak,3);
    auto emission_frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("engine.jpg");
    ValueMap vm_emission=ParticleManager::getInstance()->GetPlistData("emissionPart");
    _emissionPart = ParticleSystemQuad::create(vm_emission,emission_frame);
    _player->setEmissionPart(_emissionPart);
    addChild(_emissionPart,4);
    _emissionPart->setPositionType(tPositionType::FREE);
    addChild(_player,5);
    EffectManager::setLayer(this);
    
    this->schedule(schedule_selector(GameLayer::gameMaster) , 1.5, -1, 2.0);
    
    BulletController::init(this);
    EnemyController::init(this);
    RewardController::init(this);
    scheduleUpdate();
    
    
    _player->setPosition(Point(0,-1000));
    _player->runAction(Sequence::create(
                                        DelayTime::create(0.75),
                                        Spawn::create(
                                                      EaseBackOut::create(MoveTo::create(1.7,Point(0,-200))),
                                                      EaseSineOut::create(RotateBy::create(1.7,Vertex3F(0,720,0))),
                                                      nullptr
                                                      ),
                                        CallFunc::create(CC_CALLBACK_0(GameLayer::schedulePlayer,this)),nullptr));
    
    
    _friendPlayer = FriendPlayer::create();
    MotionStreak *_streak1 = MotionStreak::create(0.4, 1, 15, Color3B(82,255,253), "streak.png");
    _friendPlayer->setTrail(_streak1);
    addChild(_streak1,3);
    auto emission_frame1=SpriteFrameCache::getInstance()->getSpriteFrameByName("engine.jpg");
    ValueMap vm_emission1=ParticleManager::getInstance()->GetPlistData("emissionPart");
    ParticleSystemQuad *_emissionPart1 = ParticleSystemQuad::create(vm_emission1,emission_frame1);
    
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
        Point random = Point(100*CCRANDOM_MINUS1_1(), BOUND_RECT.size.height/2+200);
        for(int i=0; i < 4; i++)
        {
            auto enemy1 = EnemyController::spawnEnemy(kEnemyFodder);
            enemy1->setPosition(random + Point(60,60)*(i+1));
            static_cast<Fodder*>(enemy1)->setMoveMode(moveMode::kDefault);
            auto enemy2 = EnemyController::spawnEnemy(kEnemyFodder);
            enemy2->setPosition(random + Point(-60,60)*(i+1));
            static_cast<Fodder*>(enemy2)->setMoveMode(moveMode::kDefault);
            enemy1->setRotation3D(Vertex3F(0,0,0));
            enemy2->setRotation3D(Vertex3F(0,0,0));
        }
        auto leader = EnemyController::spawnEnemy(kEnemyFodderL);
        leader->setPosition(random);
        leader->setRotation3D(Vertex3F(0,0,0));
        static_cast<FodderLeader*>(leader)->setTarget(_player);
        static_cast<FodderLeader*>(leader)->setMoveMode(moveMode::kDefault);
    }
    //else if(_elapsed < 20 && enemyCount <5)
    if(_elapsed > 4 && enemyCount <4 &&_elapsed < 60)
    {
        Point random = Point(-400, BOUND_RECT.size.height/4*CCRANDOM_MINUS1_1()+350);
        for(int i=0; i < 3; i++)
        {
            float randomAngle = CCRANDOM_MINUS1_1()*70;
            auto enemy = EnemyController::spawnEnemy(kEnemyFodder);
            enemy->setPosition(random + Point(60,60)*(i+1));
            static_cast<Fodder*>(enemy)->setTurnRate(randomAngle*0.5);
            enemy->setRotation(-randomAngle-90);
            auto enemy2 = EnemyController::spawnEnemy(kEnemyFodder);
            enemy2->setPosition(random + Point(-60,60)*(i+1));
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
            //enemy->setPosition(Point(100*CCRANDOM_MINUS1_1(), BOUND_RECT.size.height/2+200));
            enemy->setPosition(rX,rY);
            Point targetPos =Point(BOUND_RECT.size.width/3*CCRANDOM_MINUS1_1(),BOUND_RECT.size.height/3*CCRANDOM_0_1());
            enemy->setScale(2*CCRANDOM_MINUS1_1()+2);
            float randomTime = CCRANDOM_0_1()*1+1;
            enemy->setRotation3D(Vertex3F(300,0,-CC_RADIANS_TO_DEGREES((enemy->getPosition()-targetPos).getAngle())+90));
            enemy->runAction(
                             Sequence::create(
                                              Spawn::create(
                                                            EaseSineOut::create(MoveTo::create(randomTime, targetPos)),
                                                            EaseSineOut::create(ScaleTo::create(randomTime,1)),//TODO: replace with move 3d when possible
                                                            EaseBackOut::create(RotateBy::create(randomTime+0.2,Vertex3F(-300,0,0))),
                                                            nullptr
                                                            ),
                                              CallFunc::create(enemy,callfunc_selector(BigDude::showFinished)),
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
    
    for(int i=RewardController::rewards.size()-1;i>=0;i--)
    {
        EnemyController::erase(i);
    }
}

void GameLayer::addNodeAsync(const char* type)
{
    if(isDie) return;

    log("HelloWorld::addNodeAsync %s", type);
    
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(type);
    
    switch (doc["type"].GetInt()) {
        case 1:
            _player->friendShootLeft();
            break;
        case 2:
            _player->friendShootRight();
            break;
        case 3:
            this->schedule(schedule_selector(GameLayer::addNode),0,0,0);
            break;
        case 4:
            if(_friendPlayer == NULL) return;
            _friendPlayer->touchMoved(Point(doc["prevX"].GetDouble(), doc["prevY"].GetDouble()), Point(doc["deltaX"].GetDouble(), doc["deltaY"].GetDouble()));
            break;
    }
}

void GameLayer::addNode(float dt)
{
    if(isDie) return;

    log("HelloWorld::addNode");
    
    Point random = Point(100*CCRANDOM_MINUS1_1(), BOUND_RECT.size.height/2+200);
    
    auto reward = RewardController::spawnReward(kRewardPotion);
    reward->setPosition(random);
}


