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
class BulletController
{
public:
    static void reset();
    static bool init(Node *bulletLayer);
    static Bullet* spawnBullet(int type, Vec2 pos, Vec2 vec);
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
    static void update(float dt, AirCraft* player);
};

#endif /* defined(__Moon3d__BulletController__) */
