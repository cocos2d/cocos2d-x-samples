//
//  BulletController.cpp
//  Moon3d
//
//  Created by Hao Wu on 3/4/14.
//
//

#include "GameControllers.h"
#include "GameEntity.h"
#include "Bullets.h"
#include "consts.h"
#include "AirCraft.h"
#include "Reward.h"
#include "Effects.h"
#include "SimpleAudioEngine.h"
#include "Enemies.h"
#include "Player.h"
#include "HelloWorldScene.h"

//--------------------------------------------------------------------

Node* RewardController::_rewardLayer = nullptr;
bool RewardController::_inited = false;
Vector<Reward*> RewardController::rewards;
Vector<Potion*> RewardController::_potionPool;
const float RewardController::rewardMoveDist = -200;

bool RewardController::init(Node* rewardLayer)
{
    _rewardLayer = rewardLayer;
    _inited = true;
    return true;
}

void RewardController::reset()
{
    _inited = false;
    _rewardLayer = nullptr;
    rewards.clear();
}
Reward* RewardController::createOrGet(int type)
{
    Reward *reward = nullptr;
    switch(type)
    {
        case kRewardPotion:
            if(!_potionPool.empty())
            {
                reward = _potionPool.back();
                _potionPool.popBack();
            }
            else
            {
                reward = Potion::create();
                reward->retain();
            }
            break;
        case kRewardCoin:

            break;
    }
    return reward;
}

Reward* RewardController::spawnReward(int type)
{
    CC_ASSERT(_rewardLayer);
    Reward *reward = createOrGet(type);
    if(reward)
    {
        rewards.pushBack(reward);
        _rewardLayer->addChild(reward, -1);
        return reward;
    }
    return nullptr;
}

void RewardController::erase(int i)
{
    auto e = rewards.at(i);
    int type = e->getType();
    switch(type)
    {
        case kRewardPotion:
            _potionPool.pushBack(static_cast<Potion*>(e));
            break;
        case kRewardCoin:
            break;
    }
    rewards.erase(i);
    e->removeFromParentAndCleanup(false);
    e->reset();
}

//--------------------------------------------------------------------

Node* BulletController::_bulletLayer = nullptr;
bool BulletController::_inited = false;
Vector<Bullet*> BulletController::bullets;
Vector<Missile*> BulletController::_missilePool;


void BulletController::reset(){
    _inited = false;
    _bulletLayer = nullptr;
    bullets.clear();
}
bool BulletController::init(Node *bulletLayer){
    if(bulletLayer)
    {
        reset();
        _bulletLayer = bulletLayer;
        _inited = false;
        return true;
    }
    return false;
}
Bullet* BulletController::spawnBullet(int type, Point pos, Point vec)
{
    Bullet *bullet = nullptr;
    switch(type)
    {
        case kPlayerBullet:
            bullet = PlayerBullet::create();
            //bullet->retain();
            //bullet->setType(kPlayerBullet);
            break;
        case kPlayerMissiles:
            if(!_missilePool.empty())
            {
                // if the pool is not empty, we don't need to create, just return that, and reset its data
                bullet = _missilePool.back();
                //bullet->retain();
                _missilePool.popBack();
                
                //bullet->reset();
            }
            else
            {
                bullet = Missile::create();
                bullet->retain();
            }
            //bullet->setType
            break;
        case kEnemyBullet:
            bullet = Bullet::create();
            bullet->setType(kEnemyBullet);
            break;
    }
    if(bullet)
    {
        bullets.pushBack(bullet);
        _bulletLayer->addChild(bullet,1);
        //bullet->release();
        bullet->setPosition(pos);
        bullet->setVector(vec);
        return bullet;
    }
    return nullptr;
}
void BulletController::erase(Bullet* b)
{
    if(b->getType() == kPlayerMissiles)
    {
        _missilePool.pushBack(static_cast<Missile*>(b));
        bullets.eraseObject(b);
        b->removeFromParentAndCleanup(false);
        b->reset();
    }
    else
    {
        b->removeFromParentAndCleanup(true);
        bullets.eraseObject(b);
    }
}
void BulletController::erase(int i)
{
    auto b = bullets.at(i);
    if(b->getType() == kPlayerMissiles)
    {
        _missilePool.pushBack(static_cast<Missile*>(b));
        bullets.erase(i);
        b->removeFromParentAndCleanup(false);
        b->reset();
    }
    else
    {
        bullets.erase(i);
        b->removeFromParentAndCleanup(true);
    }
}


Node* EnemyController::_enemyLayer = nullptr;
bool EnemyController::_inited = false;
Vector<AirCraft*> EnemyController::enemies;
Vector<AirCraft*> EnemyController::showCaseEnemies;
Vector<Fodder*> EnemyController::_fodderPool;
Vector<FodderLeader*> EnemyController::_fodderLPool;
Vector<BigDude*> EnemyController::_bigDudePool;
Vector<Boss*> EnemyController::_bossPool;

const float EnemyController::EnemyMoveDist = -400;
bool EnemyController::init(Node* enemyLayer)
{
    _enemyLayer = enemyLayer;
    _inited = true;
    return true;
}

void EnemyController::reset()
{
    _inited = false;
    _enemyLayer = nullptr;
    enemies.clear();
}
AirCraft* EnemyController::createOrGet(int type)
{
    AirCraft *enemy = nullptr;
    switch(type)
    {
        case kEnemyFodder:
            if(!_fodderPool.empty())
            {
                enemy = _fodderPool.back();
                _fodderPool.popBack();
            }
            else
            {
                enemy = Fodder::create();
                enemy->retain();
            }
            break;
        case kEnemyFodderL:
            if(!_fodderLPool.empty())
            {
                enemy = _fodderLPool.back();
                _fodderLPool.popBack();
            }
            else
            {
                enemy = FodderLeader::create();
                enemy->retain();
            }
            break;
        case kEnemyBigDude:
            if(!_bigDudePool.empty())
            {
                enemy = _bigDudePool.back();
                _bigDudePool.popBack();
            }
            else
            {
                enemy = BigDude::create();
                enemy->retain();
            }
            break;
        case kEnemyBoss:
            if(!_bossPool.empty())
            {
                enemy = _bossPool.back();
                _bossPool.popBack();
            }
            else
            {
                enemy = Boss::create();
                enemy->retain();
            }
            break;
    }
    return enemy;
}

AirCraft* EnemyController::spawnEnemy(int type)
{
    CC_ASSERT(_enemyLayer);
    AirCraft *enemy = createOrGet(type);
    if(enemy)
    {
        enemies.pushBack(enemy);
        _enemyLayer->addChild(enemy, 0);
        return enemy;
    }
    return nullptr;
}
AirCraft* EnemyController::showCaseEnemy(int type)
{
    CC_ASSERT(_enemyLayer);
    AirCraft *enemy = createOrGet(type);
    if(enemy)
    {
        showCaseEnemies.pushBack(enemy);
        _enemyLayer->addChild(enemy, 0);
        return enemy;
    }
    return nullptr;
}
void EnemyController::erase(int i)
{
    auto e = enemies.at(i);
    int type = e->getType();
    switch(type)
    {
        case kEnemyFodder:
            _fodderPool.pushBack(static_cast<Fodder*>(e));
            break;
        case kEnemyFodderL:
            _fodderLPool.pushBack(static_cast<FodderLeader*>(e));
            break;
        case kEnemyBigDude:
            _bigDudePool.pushBack(static_cast<BigDude*>(e));
            break;
        case kEnemyBoss:
            _bossPool.pushBack(static_cast<Boss*>(e));
            break;
    }
    enemies.erase(i);
    e->removeFromParentAndCleanup(false);
    e->reset();
}


void GameController::update(float dt, Player* player)
{
    Point temp;
    Bullet* b;
    auto list =BulletController::bullets;
    float enemyMoveDist =EnemyController::EnemyMoveDist*dt;
    for(int i = BulletController::bullets.size()-1; i >= 0; i-- )
    {
        b =BulletController::bullets.at(i);
        temp =b->getPosition();
        if(BOUND_RECT.containsPoint(temp))
        {
            if(b->getOwner() == kPlayer)
            {
                //********* Enemy Loop **********
                for(int j = EnemyController::enemies.size()-1; j >= 0; j--)
                {
                    auto e = EnemyController::enemies.at(j);
                    if(b->getPosition().getDistance(e->getPosition()) <(b->getRadius() + e->getRadius()))
                    {
                        //collision happened
                        bool dead =  e->hurt(b->getDamage());
                        if(!dead)
                        {
                            switch(b->getType())
                            {
                                case kPlayerMissiles:
                                    EffectManager::createExplosion(b->getPosition());
                                
                                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("boom2.mp3");
                                    break;
                                default:
                                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit.mp3");
                                    break;
                            }
                        }
                        BulletController::erase(i);
                    }
                    
                }
                //*********** Enemy Loop ***************
                if(b->getType() == kPlayerMissiles)
                {
                    b->update(dt);
                }
                else{
                    b->setPosition(temp+(b->getVector()*dt));
                }
            }
            // loop all enemy bullets against player
            else if(b->getPosition().getDistance(player->getPosition()) < b->getRadius()+player->getRadius())
            {
                player->hurt(b->getDamage());
                BulletController::erase(i);
                EffectManager::createExplosion(player->getPosition());
                break;
            }
            else // nothing happens to the bullet, move along..
            {
                
                b->setPosition(temp+(b->getVector()*dt));
            }
        }
        else
        {
            BulletController::erase(i);
        }
    }
    // Enemies update
    for(int k = EnemyController::enemies.size()-1; k>=0; k--)
    {
        auto enemy =EnemyController::enemies.at(k);
        if(!enemy->alive())
        {
            EnemyController::erase(k);
            //enemy->reset();
            //break;
        }
        switch(enemy->getType())
        {
            case kEnemyBigDude:
                static_cast<BigDude*>(enemy)->update(dt, player);
                break;
            case kEnemyBoss:
                static_cast<Boss*>(enemy)->update(dt, player);
                break;
            default:
                enemy->move(enemyMoveDist, dt);
                break;
        }
        if(!ENEMY_BOUND_RECT.containsPoint(enemy->getPosition()) && enemy->getType() != kEnemyBoss)
        {
            //enemy went out side, kill it
            EnemyController::erase(k);
        }
        //if colliding with player
        else if(enemy->getPosition().getDistance(player->getPosition()) <(enemy->getRadius() + player->getRadius()))
        {
            player->hurt(50);
            enemy->hurt(50);
            if(enemy->getType() != kEnemyBoss && enemy->getType() != kEnemyBigDude)
            EnemyController::erase(k);
        }
        //TODO: if enemy collide with player
        //if(enemy->getPosition().getDistance(<#const cocos2d::Point &other#>))
    }
    
    float rewardMoveDist =RewardController::rewardMoveDist*dt;
    // Reward update
    for(int k = RewardController::rewards.size()-1; k>=0; k--)
    {
        auto reward =RewardController::rewards.at(k);
        if(!reward->alive())
        {
            RewardController::erase(k);
        }
       switch(reward->getType())
        {
            case kRewardPotion:
            case kRewardCoin:
            default:
                reward->move(rewardMoveDist, dt);
                break;
        }

        if(!ENEMY_BOUND_RECT.containsPoint(reward->getPosition()))
        {
            //reward went out side, kill it
            RewardController::erase(k);
        }
        //if colliding with player
        else if(reward->getPosition().getDistance(player->getPosition()) <(reward->getRadius() + player->getRadius()))
        {
            player->heal(50);
            RewardController::erase(k);
        }
    }
    
}




