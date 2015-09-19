//
//  ScrollingBackground.h
//  Moon3d
//
//  Created by Hao Wu on 2/24/14.
//
//

#ifndef __Moon3d__GameLayer__
#define __Moon3d__GameLayer__
#include "cocos2d.h"
USING_NS_CC;
class Player;
class FriendPlayer;
//class QuadTree;
class AirCraft;
class GameEntity;

class GameLayer : public Layer
{
public:
    virtual bool init();
    void update(float dt);
    CREATE_FUNC(GameLayer);
    static bool isDie;
    
    //virtual void onEnter();
    
    void addNodeAsync(const char* type);
protected:
    float xScroll = 0.0f;
    float speed = -60.0f;
    Sprite *_spr;
    Sprite *_cloud;
    Player *_player;
    FriendPlayer *_friendPlayer;
    MotionStreak *_streak;
    ParticleSystemQuad *_emissionPart;
    void schedulePlayer();
    void scheduleFriendPlayer();
    //QuadTree *_collisionTree;
    


    //QuadTree *container;
    void gameMaster(float dt);
    float _elapsed = 20; //testing purpose, this was set to near boss timer
    bool _bossOut = false;

    void addNode(float dt);

private:
    void removeBulletAndEnmeys(float dt);
};
#endif /* defined(__Moon3d__GameLayer__) */