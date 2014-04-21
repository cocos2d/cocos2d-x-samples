#ifndef _EYECANDY_LAYER_H_
#define _EYECANDY_LAYER_H_

#include "cocos2d.h"
#include <Box2D/Box2D.h>

class GLESDebugDraw;

class EyeCandyLayer : public cocos2d::Layer
{
public:
    static EyeCandyLayer* create();

    EyeCandyLayer();
    ~EyeCandyLayer();

    void initPhysics();

    void addNewSpriteAtPosition(cocos2d::Point p);
    void update(float dt);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

protected:

    virtual void draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;
    void onDraw(const kmMat4 &transform, bool transformUpdated);

    GLESDebugDraw *_debugDraw;
    cocos2d::CustomCommand _customCmd;

    //
    b2World* _world;
    b2ParticleSystem *_particleSystem;
    b2RevoluteJoint *_joint;
    b2Body *_mover;
};

#endif // _EYECANDY_LAYER_H_
