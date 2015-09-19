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

#include "MainMenuScene.h"
#include "LoadingScene.h"
#include "PublicApi.h"
#include "Plane.h"
#include "GameLayer.h"
#include "HelloWorldScene.h"
#include "LicenseLayer.h"
#include "CCFLayer.h"
#include "PopLayer.h"
#include "FriendControlScene.h"
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	
	pRate = 3.1415926/2;

    // Music By Matthew Pable (http://www.matthewpablo.com/)
    // Licensed under CC-BY 3.0 (http://creativecommons.org/licenses/by/3.0/)
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Star_Chaser.mp3");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("menu_scene.plist","menu_scene.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Particle.plist","Particle.png");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    Size winSize = Director::getInstance()->getWinSize();
//    if(){
//        log("x");
//    }else if(920 == visibleSize.height){
//        log("y");
//    }
//    log("w:%f",visibleSize.width);
//    log("h:%f",visibleSize.height);
//    log("w:%f",winSize.width);
//    log("h:%f",winSize.height);
    
    
    //************ adds Plane ****************
    plane = Plane::create();
    this->addChild(plane, 10);
    this->scheduleUpdate();
    
    //************ adds emission flare ****************
    auto flare = ParticleSystemQuad::create("missileFlare.plist");
    flare->setScale(5);
    float originX = -9.0f;
    float originY = 159.0f;
    float originZ = 9.0f;
    flare->setTotalParticles(50);
    flare->setRotation3D(Vec3(-originX,-originY,-originZ));
    flare->setPosition(-39,0);
    flare->setPositionType(tPositionType::GROUPED);
    flare->setStartColor(Color4F(0,0.99,1,1));
    plane->addChild(flare, -1);
    
    auto emis = ParticleSystemQuad::create("menuEmission.plist");
    emis->setScale(3);
    emis->setRotation3D(Vec3(-originX,-originY,-originZ));
    emis->setPosition(-40,0);
    emis->setPositionType(tPositionType::GROUPED);
    emis->setRotation(180);
    plane->addChild(emis, -2);

    
    //************ adds vanishing ****************
    auto fileUtil = FileUtils::getInstance();
    auto plistData = fileUtil->getValueMapFromFile("vanishingPoint.plist");
    //auto sf = SpriteFrame::create("bullets.png", Rect(5,8,24,32));
    auto vanishing = ParticleSystemQuad::create(plistData);
    vanishing->setAnchorPoint(Vec2(0.5f,0.5f));
    vanishing->setPosition(visible_size_macro.width-90,visible_size_macro.height/2 +50);
    this->addChild(vanishing,1,1);
    
    //************* adds background ***********
    auto background = Sprite::createWithSpriteFrameName("mainmenu_BG.png");
    background->setAnchorPoint(Vec2(0,0));
    this->addChild(background,-1,-1);
    
    //************* adds start game ***********
    auto start_normal=Sprite::createWithSpriteFrameName("start_game.png");
    auto start_pressed=Sprite::createWithSpriteFrameName("start_game.png");
    startgame_item = MenuItemSprite::create(start_normal, start_pressed, CC_CALLBACK_1(MainMenuScene::startgame, this));
    startgame_item->setPosition(visibleSize.width/2 - 150,200);
    startgame_item->setScale(1.3);
    
    //************* adds PK game ***********
    auto pk_normal=Sprite::create("pkstart.png");
    auto pk_pressed=Sprite::create("pkstart.png");
    pk_item = MenuItemSprite::create(pk_normal, pk_pressed, CC_CALLBACK_1(MainMenuScene::pkgame, this));
    pk_item->setPosition(visibleSize.width/2 + 150,200);
    pk_item->setScale(1.3);
    
    //************* license *******************
    auto license_normal=Sprite::createWithSpriteFrameName("license.png");
    auto license_pressed=Sprite::createWithSpriteFrameName("license.png");
    license_item = MenuItemSprite::create(license_normal, license_pressed, CC_CALLBACK_1(MainMenuScene::license, this));
    license_item->setPosition(visibleSize.width/2-200,100);
    license_item->setScale(0.7);

    //************* credits ******************
    auto credits_normal=Sprite::createWithSpriteFrameName("credits.png");
    auto credits_pressed=Sprite::createWithSpriteFrameName("credits.png");
    credits_item = MenuItemSprite::create(credits_normal, credits_pressed, CC_CALLBACK_1(MainMenuScene::credits, this));
    credits_item->setPosition(visibleSize.width/2+200,100);
    credits_item->setScale(0.7);

    //************* Menu ******************
    auto menu = Menu::create(startgame_item,license_item,credits_item,pk_item, NULL);
    menu->setPosition(origin);
    this->addChild(menu,3);
    
    auto peerInviteListener = EventListenerCustom::create("IntelCCFPeerInvite", CC_CALLBACK_1(MainMenuScene::listenToPeerInvite, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(peerInviteListener, this);
    
    auto peerAcknowledgmentListener = EventListenerCustom::create("IntelCCFInviteAcknowledgment", CC_CALLBACK_1(MainMenuScene::listenToAcknowledgment, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(peerAcknowledgmentListener, this);
    
    auto peerStartControlListener = EventListenerCustom::create("OnStartControl", CC_CALLBACK_1(MainMenuScene::listenToStartControl, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(peerStartControlListener, this);
    
    return true;
}

void MainMenuScene::update(float dt){
    pRate+=0.01;
    plane->setPosition3D(Vec3(visible_size_macro.width/2+50,480-20*sin(1.05*pRate),0));
}

void MainMenuScene::startgame(Ref* sender)
{
    startgame_item->runAction(Sequence::create(ScaleTo::create(0.1f, 1.4f),
                                                ScaleTo::create(0.1f, 1.2f),
                                                ScaleTo::create(0.1f, 1.3f),
                                               CallFunc::create(CC_CALLBACK_0(MainMenuScene::startgame_callback,this)),NULL));
}

void MainMenuScene::startgame_callback()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    GameLayer::isDie=false;
    auto scene = (LoadingScene::audioloaded) ? HelloWorld::createScene() :LoadingScene::createScene();
    Director::getInstance()->replaceScene(scene);
}


void MainMenuScene::pkgame(Ref* sender)
{
    pk_item->runAction(Sequence::create(ScaleTo::create(0.1f, 1.4f),
                                        ScaleTo::create(0.1f, 1.2f),
                                        ScaleTo::create(0.1f, 1.3f),
                                        CallFunc::create(CC_CALLBACK_0(MainMenuScene::pkgame_callback,this)),NULL));
}

void MainMenuScene::pkgame_callback()
{
    auto ccfLayer = CCFLayer::create("credits_03.png");
    ccfLayer->setAnchorPoint(Vec2(0.5f,0.5f));
    ccfLayer->setPosition(Vec2(visible_size_macro.width/2, visible_size_macro.height/2));
    addChild(ccfLayer,20);
    
    ccfLayer->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f),
                                        ScaleTo::create(0.1f, 0.9f),
                                        ScaleTo::create(0.1f, 1.0f),
                                        NULL));
}

void MainMenuScene::credits(Ref* sender){
    credits_item->runAction(Sequence::create(ScaleTo::create(0.1f, 0.8f),
                                               ScaleTo::create(0.1f, 0.6f),
                                               ScaleTo::create(0.1f, 0.7f),
                                             CallFunc::create(CC_CALLBACK_0(MainMenuScene::credits_callback, this)),NULL));
}

void MainMenuScene::credits_callback()
{
    auto license =LicenseLayer::create("credits_03.png");
    license->setAnchorPoint(Vec2(0.5f,0.5f));
    license->setPosition(Vec2(visible_size_macro.width/2, visible_size_macro.height/2));
    addChild(license,20);
    license->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f),
                                        ScaleTo::create(0.1f, 0.9f),
                                        ScaleTo::create(0.1f, 1.0f),
                                        NULL));
}

void MainMenuScene::license(Ref* sender){
    license_item->runAction(Sequence::create(ScaleTo::create(0.1f, 0.8f),
                                               ScaleTo::create(0.1f, 0.6f),
                                               ScaleTo::create(0.1f, 0.7f),
                                             CallFunc::create(CC_CALLBACK_0(MainMenuScene::license_callback, this)),NULL));
}

void MainMenuScene::license_callback()
{
    auto license =LicenseLayer::create("LICENSE_03.png");
    license->setAnchorPoint(Vec2(0.5f,0.5f));
    license->setPosition(Vec2(visible_size_macro.width/2, visible_size_macro.height/2));
    addChild(license,20);
    license->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f),
                                        ScaleTo::create(0.1f, 0.9f),
                                        ScaleTo::create(0.1f, 1.0f),
                                        NULL));
}

void MainMenuScene::listenToAcknowledgment(cocos2d::EventCustom *event)
{
    this->scheduleOnce(schedule_selector(MainMenuScene::scheduleAcknowledgement), 0);
}

void MainMenuScene::scheduleAcknowledgement(float dt)
{
    startgame(NULL);
}

void MainMenuScene::listenToPeerInvite(EventCustom *event)
{
    this->scheduleOnce(schedule_selector(MainMenuScene::scheduleInvite), 0);
}

void MainMenuScene::scheduleInvite(float dt)
{
    auto popLayer = PopLayer::create();
    addChild(popLayer, 30);
}

void MainMenuScene::listenToStartControl(EventCustom *event)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    GameLayer::isDie=false;
    auto scene = FriendControl::createScene();
    Director::getInstance()->replaceScene(scene);
}
