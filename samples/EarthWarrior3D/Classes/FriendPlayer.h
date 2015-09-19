//
//  FriendPlayer.h
//  Moon3d
//
//  Created by John Li on 7/16/14.
//
//

#ifndef __Moon3d__Friend_Player__
#define __Moon3d__Friend_Player__

#include "cocos2d.h"
#include "AirCraft.h"

USING_NS_CC;

class FriendPlayer : public AirCraft
{
public:
    CREATE_FUNC(FriendPlayer);
    bool init();

    void update(float dt);
    
    const float rollSpeed = 1.5;// recommended 1.5
    const float returnSpeed = 10;// recommended 4
    const float maxRoll = 75;
    const float rollReturnThreshold = 1.02;
    void setTargetAngle(float angle){targetAngle = angle;};
    void setTargetPos(Point target){targetPos = target;};
    
    void shoot(float dt);
    void shootMissile(float dt);
    void stop();
    CC_SYNTHESIZE(MotionStreak*, _streak, Trail);
    CC_SYNTHESIZE(ParticleSystemQuad*, _emissionPart, EmissionPart);
    void setPosition(Point pos);
    virtual bool hurt(float damage);
    virtual bool heal(float hp);
    virtual void die();
    void hideWarningLayer();
    
    void touchMoved(Point prev, Point delta);
protected:
    float targetAngle = 0;
    Point targetPos = Point(0,0);
    Point _trailOffset = Point(0,-40);
    int shootDirection = 0;
    
    Point _prev;
    Point _delta;
};


#endif /* defined(__Moon3d__Friend_Player__) */
