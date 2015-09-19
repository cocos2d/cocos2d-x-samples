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
 
#include "HelloWorldScene.h"
#include "GameLayer.h"
#include "HelloWorldScene.h"
#include "GameOverLayer.h"
#include "GameControllers.h"

USING_NS_CC;

HelloWorld::~HelloWorld()
{
    //NotificationCenter::getInstance()->destroyInstance();
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    layer->setTag(100);
    // add layer as a child to scene
    scene->addChild(layer,2);

    // add warning layer
    auto warningLayer = LayerColor::create(Color4B(255, 0, 0, 60));
    warningLayer->setOpacity(0);
    warningLayer->setTag(456);
    scene->addChild(warningLayer,7);
    
    
    // return the scene
    return scene;
}

HelloWorld::HelloWorld()
:score(0)
, hpView(nullptr)
, scoreLabel(nullptr)
{
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto sb = GameLayer::create();
    sb->setTag(123);
    sb->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(sb);
    auto fog = Sprite::createWithSpriteFrameName("fog.png");
    addChild(fog);
    fog->setPosition(visibleSize.width/2,visibleSize.height/2+285);
    fog->setScaleX(visibleSize.width/10);
    
    //HP
    auto lefttopUI = Sprite::createWithSpriteFrameName("hp_empty.png");
    lefttopUI->setAnchorPoint(Vec2(0,1));
    lefttopUI->setPosition(Vec2(0, visibleSize.height+origin.y));
    addChild(lefttopUI);
    
    hpView = ProgressTimer::create(Sprite::createWithSpriteFrameName("hp.png"));
    hpView->setType(ProgressTimer::Type::BAR);
    hpView->setMidpoint(Vec2(0,0));
    hpView->setPercentage(1);
    hpView->setBarChangeRate(Vec2(0, 1));
    hpView->setPercentage(100);
    hpView->setAnchorPoint(Vec2(0,1));
    hpView->setPosition(Vec2(18, visibleSize.height+origin.y-32));
    addChild(hpView);
    
    auto hpAbove = Sprite::createWithSpriteFrameName("hp_above.png");
    hpAbove->setAnchorPoint(Vec2(0,1));
    hpAbove->setPosition(Vec2(18, visibleSize.height+origin.y-32));
    addChild(hpAbove);
    
    //Score
    auto rightTopUI = Sprite::createWithSpriteFrameName("right_top_ui.png");
    rightTopUI->setAnchorPoint(Vec2(1,1));
    rightTopUI->setPosition(origin+visibleSize);
    this->addChild(rightTopUI);
    
    //the menuitem to show score
    scoreLabel = LabelAtlas::create("0", "score_right_top.png", 23, 28, '0');
    scoreLabel->setAnchorPoint(Vec2(1,0.5));
    scoreLabel->setPosition(visibleSize.width-40,visibleSize.height-45);
    this->addChild(scoreLabel);

    this->schedule(schedule_selector(HelloWorld::increaseScore), (float)1/10);
    //this->addChild(scoreLabel);

    
    NotificationCenter::getInstance()->destroyInstance();
    NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(HelloWorld::ShowGameOver),"ShowGameOver",NULL);

    return true;
}

void HelloWorld::increaseScore(float dt)
{
    this->score++;
    std::stringstream ss;
    std::string str;
    ss<<score;
    ss>>str;
    const char *p = str.c_str();
    scoreLabel->setString(p);
}

void HelloWorld::ShowGameOver(Ref* pObj)
{
    //unschedule(schedule_selector(HelloWorld::increaseScore));
//    BulletController::reset();
//    EnemyController::reset();
    auto gameoverlayer=GameOverLayer::create(score);
    addChild(gameoverlayer,10);
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
