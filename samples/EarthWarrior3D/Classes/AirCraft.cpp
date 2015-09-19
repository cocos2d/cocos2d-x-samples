//
//  AirCraft.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "AirCraft.h"
#include "SimpleAudioEngine.h"
#include "Effects.h"
#include "HelloWorldScene.h"

bool AirCraft::hurt(float damage)
{
    _HP -= damage;
    if(_HP <= 0)
    {
        die();
        return true;
    }
    return false;
}
void AirCraft::die()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explodeEffect.mp3");
    EffectManager::createBigExplosion(getPosition());
    auto helloworld = (HelloWorld*)Director::getInstance()->getRunningScene()->getChildByTag(100);
    int score = helloworld->getScore();
    helloworld->setScore(score+=_score);
    std::stringstream ss;
    std::string str;
    ss<<score;
    ss>>str;
    const char *p = str.c_str();
    helloworld->getScoreLabel()->setString(p);
    _alive = false;
    auto scale = ScaleTo::create(0.1, 1.2);
    auto scaleBack = ScaleTo::create(0.1, 1);
    auto label =helloworld->getScoreLabel();
    label->runAction(Sequence::create(scale, scaleBack,NULL));
    //removeFromParent();
}

void AirCraft::move(float y, float dt)
{
    //setPosition(getPosition().x+getPosition().y+y);
    forward(y);
}

void AirCraft::reset()
{
    _alive = true;
}
bool AirCraft::alive()
{
    return _alive;
}