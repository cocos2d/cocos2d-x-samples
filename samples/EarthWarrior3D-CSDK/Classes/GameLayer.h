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

#ifndef __Moon3d__GameLayer__
#define __Moon3d__GameLayer__
#include "cocos2d.h"
USING_NS_CC;
class Player;
//class QuadTree;
class AirCraft;
class GameEntity;
class CCFPlayer;
class GameLayer : public Layer
{
public:
    virtual bool init();
    void update(float dt);
    CREATE_FUNC(GameLayer);
    static bool isDie;
    //virtual void onEnter();

protected:
    float xScroll;
    float speed;
    Sprite *_spr;
    Sprite *_cloud;
    Player *_player;
    MotionStreak *_streak;
    ParticleSystemQuad *_emissionPart;
    void schedulePlayer();
    //QuadTree *_collisionTree;
    
    CCFPlayer *_friendPlayer;
    void scheduleFriendPlayer();
    void listenToReceiveMessage(cocos2d::EventCustom *event);
    void listenToDisconnect(cocos2d::EventCustom *event);
    void scheduleReceiveMessage(float dt);
    void scheduleDisconnect(float dt);
    
    //QuadTree *container;
    void gameMaster(float dt);
    float _elapsed; //testing purpose, this was set to near boss timer
    bool _bossOut;
    
private:
    void removeBulletAndEnmeys(float dt);
};
#endif /* defined(__Moon3d__GameLayer__) */