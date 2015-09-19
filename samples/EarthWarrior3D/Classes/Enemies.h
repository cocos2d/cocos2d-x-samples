//
//  Fodder.h
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#ifndef __Moon3d__Fodder__
#define __Moon3d__Fodder__

#include "cocos2d.h"
#include "AirCraft.h"
enum moveMode{
    kDefault,
    kTurn
};
class Sprite3D;

class Fodder : public AirCraft
{
public:
    CREATE_FUNC(Fodder);
    bool init();
    virtual void reset();
    virtual void move(float y, float dt);
    CC_SYNTHESIZE(int, _moveMode, MoveMode);
    CC_PROPERTY(float, _turn, TurnRate);
    virtual void shoot(float dt);
    CC_SYNTHESIZE(AirCraft*, _target, Target);
};

class FodderLeader : public Fodder
{
public:
    CREATE_FUNC(FodderLeader);
    bool init();
    virtual void reset();
};

class BigDude : public AirCraft
{
public:
    CREATE_FUNC(BigDude);
    bool init();
    virtual void reset();
    virtual void die();
    void update(float dt, Node* player);
    void showFinished();
    void showMuzzle();
    void dismissMuzzle(float dt);
    virtual void shoot(float dt);
    void fall();
protected:
    Sprite* muzzle1;
    Sprite* muzzle2;
    Point _targetPos;
    float _turnRate = 50;
};

class Boss : public Fodder
{
public:
    CREATE_FUNC(Boss);
    bool init();
    virtual void die();
    virtual void shoot(float dt);
    void update(float dt, Node* player);
protected:
    void createRandomExplosion();
    void dying();
    void dead();
    void enterTheBattle();
    void startShooting(float dt);
    void startShooting();
    void showMuzzle();
    void dismissMuzzle(float dt);
    void _turns();
    void _endGame(float dt);
    Point _getCannon1Position();
    Point _getCannon2Position();
    Point _getCannon1Vector();
    Point _getCannon2Vector();
    Node* _Cannon1;
    Node* _Cannon2;
    Sprite* muzzle1;
    Sprite* muzzle2;
    void _dash();
    cocos2d::SEL_CallFunc _next();
};


#endif /* defined(__Moon3d__Fodder__) */
