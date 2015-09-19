//
//  Explosion.h
//  Moon3d
//
//  Created by Rye on 14-3-10.
//
//

#ifndef __Moon3d__Explosion__
#define __Moon3d__Explosion__

#include "cocos2d.h"

class SmallExplosion : public cocos2d::Node{
    
public:
    CREATE_FUNC(SmallExplosion);
    bool init();
    void createExplosion(Node* _effectLayer, cocos2d::Point pos);
    
private:
    void recycle(float dt);
    cocos2d::ParticleSystemQuad* part1;
    cocos2d::ParticleSystemQuad* part2;

};

class BigExplosion : public cocos2d::Node{
    
public:
    CREATE_FUNC(BigExplosion);
    bool init();
    void createExplosion(Node* _effectLayer,cocos2d::Point pos);
    cocos2d::ParticleSystemQuad* part1;
    cocos2d::ParticleSystemQuad* part2;
    cocos2d::ParticleSystemQuad* part3;
private:
    void recycle(float dt);

};

class BulletExplosion : public cocos2d::Sprite
{
public:
    CREATE_FUNC(BulletExplosion);
    bool init();
    void showExplosion(cocos2d::Point point);
    void explosionFinished(Ref* obj);
};


#endif /* defined(__Moon3d__Explosion__) */
