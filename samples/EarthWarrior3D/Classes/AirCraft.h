//
//  AirCraft.h
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#ifndef __Moon3d__AirCraft__
#define __Moon3d__AirCraft__

#include "cocos2d.h"
#include "GameEntity.h"
USING_NS_CC;

class AirCraft : public GameEntity
{
public:
    virtual bool hurt(float damage);
    virtual void die();
    void shoot();
    //CC_SYNTHESIZE(float, _HP, HP);
    bool alive();
    virtual void move(float y, float dt);
    virtual void reset();
protected:
    bool _alive = true;
    float _HP;
    int _score;
};

#endif /* defined(__Moon3d__AirCraft__) */
