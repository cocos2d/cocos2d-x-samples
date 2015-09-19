//
//  Reward.h
//  Moon3d
//
//  Created by Jun Li on 5/20/14.
//
//

#ifndef __Moon3d__Reward__
#define __Moon3d__Reward__

#include "cocos2d.h"
#include "GameEntity.h"
USING_NS_CC;

class Reward : public GameEntity
{
public:
    virtual void gain(long count);
    virtual bool alive();
    virtual void move(float y, float dt);
    virtual void reset();
protected:
    bool _alive = true;
    long _count;
};

class Potion : public Reward
{
public:
    CREATE_FUNC(Potion);
    bool init();
    void gain(long count);
    virtual void reset();
    virtual void move(float y, float dt);
    CC_SYNTHESIZE(int, _moveMode, MoveMode);
    CC_PROPERTY(float, _turn, TurnRate);
    CC_SYNTHESIZE(Reward*, _target, Target);
};

#endif /* defined(__Moon3d__Reward__) */
