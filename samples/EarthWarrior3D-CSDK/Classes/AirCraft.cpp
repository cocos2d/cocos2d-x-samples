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