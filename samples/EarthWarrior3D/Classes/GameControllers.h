//
//  BulletController.h
//  Moon3d
//
//  Created by Hao Wu on 3/4/14.
//
//

#ifndef __Moon3d__BulletController__
#define __Moon3d__BulletController__

#include "cocos2d.h"
USING_NS_CC;
class Bullet;
class AirCraft;
class Missile;
class Fodder;
class FodderLeader;
class BigDude;
class Player;
class Boss;
class Reward;
class Potion;

class RewardController
{
public:
    static void reset();
    static bool init(Node *rewardLayer);
    static Reward* spawnReward(int type);
    static Reward* createOrGet(int type);
    static void update(float dt);
    static Vector<Reward*> rewards;
    static void erase(int i);
    
    static const float rewardMoveDist;

    //all kinds of reward container
    static Vector<Potion*> _potionPool;
    
protected:
    static bool _inited;
    static Node *_rewardLayer;
};

class BulletController
{
public:
    static void reset();
    static bool init(Node *bulletLayer);
    static Bullet* spawnBullet(int type, Point pos, Point vec);
    //static void update(float dt);
    static Vector<Bullet*> bullets;
    static void erase(Bullet* b); //returns the bullet to the pool
    static void erase(int i);
    
    static Vector<Missile*> _missilePool;

protected:
        //static BulletController *s_instance;
    static bool _inited;
    static Node *_bulletLayer;
};

class EnemyController
{
public:
    static void reset();
    static bool init(Node *enemyLayer);
    static AirCraft* spawnEnemy(int type);
    static AirCraft* createOrGet(int type);
    static AirCraft* showCaseEnemy(int type);
    static void update(float dt);
    static Vector<AirCraft*> enemies;
    static void erase(int i);
    static Vector<AirCraft*> showCaseEnemies;

    static const float EnemyMoveDist;
    
    
    //all kinds of enemies container
    static Vector<Fodder*> _fodderPool;
    static Vector<FodderLeader*> _fodderLPool;
    static Vector<BigDude*> _bigDudePool;
    static Vector<Boss*> _bossPool;
    
protected:
    static bool _inited;
    static Node *_enemyLayer;
    
};

class GameController
{
public:
    static void update(float dt, Player* player);
};

#endif /* defined(__Moon3d__BulletController__) */
