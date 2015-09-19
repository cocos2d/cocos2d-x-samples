//
//  MainMenuScene.cpp
//  Moon3d
//
//  Created by Rye on 14-3-12.
//
//

#include "MainMenuScene.h"
#include "LoadingScene.h"
#include "PublicApi.h"
#include "Plane.h"
#include "GameLayer.h"
#include "HelloWorldScene.h"
#include "LicenseLayer.h"
#include "consts.h"
#include "GameControllers.h"
#include "FriendControlScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
    layer->setTag(1001);
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
    // Music By Matthew Pable (http://www.matthewpablo.com/)
    // Licensed under CC-BY 3.0 (http://creativecommons.org/licenses/by/3.0/)
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Star_Chaser.mp3");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("menu_scene.plist","menu_scene.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Particle.plist","Particle.png");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
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
    flare->setRotation3D(Vertex3F(-originX,-originY,-originZ));
    flare->setPosition(-39,0);
    flare->setPositionType(tPositionType::GROUPED);
    flare->setStartColor(Color4F(0,0.99,1,1));
    plane->addChild(flare, -1);
    
    auto emis = ParticleSystemQuad::create("menuEmission.plist");
    emis->setScale(3);
    emis->setRotation3D(Vertex3F(-originX,-originY,-originZ));
    emis->setPosition(-40,0);
    emis->setPositionType(tPositionType::GROUPED);
    emis->setRotation(180);
    plane->addChild(emis, -2);

    
    //************ adds vanishing ****************
    auto fileUtil = FileUtils::getInstance();
    auto plistData = fileUtil->getValueMapFromFile("vanishingPoint.plist");
    //auto sf = SpriteFrame::create("bullets.png", Rect(5,8,24,32));
    auto vanishing = ParticleSystemQuad::create(plistData);
    vanishing->setAnchorPoint(Point(0.5f,0.5f));
    vanishing->setPosition(visible_size_macro.width-90,visible_size_macro.height/2 +50);
    this->addChild(vanishing,1,1);
    
    //************* adds background ***********
    auto background = Sprite::createWithSpriteFrameName("mainmenu_BG.png");
    background->setAnchorPoint(Point(0,0));
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
    auto menu = Menu::create(startgame_item, pk_item, license_item,credits_item, NULL);
    menu->setPosition(origin);
    this->addChild(menu,3);
    
    return true;
}

void MainMenuScene::update(float dt){
    pRate+=0.01;
    plane->setPosition3D(Vertex3F(visible_size_macro.width/2+50,480-20*sin(1.05*pRate),0));
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "com/cocos2dx/moon3d/AppActivity", "showFriend", "(Ljava/lang/String;)V")) {
        jstring stringArg1 = t.env->NewStringUTF("");
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
#endif
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
    license->setAnchorPoint(Point(0.5f,0.5f));
    license->setPosition(Point(visible_size_macro.width/2, visible_size_macro.height/2));
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
    license->setAnchorPoint(Point(0.5f,0.5f));
    license->setPosition(Point(visible_size_macro.width/2, visible_size_macro.height/2));
    addChild(license,20);
    license->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f),
                                        ScaleTo::create(0.1f, 0.9f),
                                        ScaleTo::create(0.1f, 1.0f),
                                        NULL));
}

void MainMenuScene::jniStartGame(const char* something)
{
    log("MainMenuScene::jniStartGame");
    
    this->schedule(schedule_selector(MainMenuScene::scheduleStartGame),0.1,0,0);
}

void MainMenuScene::scheduleStartGame(float dt)
{
    startgame(NULL);
}

void MainMenuScene::jniStartControl()
{
    log("MainMenuScene::jniStartControl");
    
    this->schedule(schedule_selector(MainMenuScene::scheduleStartControl),0.1,0,0);
}

void MainMenuScene::scheduleStartControl(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    GameLayer::isDie=false;
    auto scene = FriendControl::createScene();
    Director::getInstance()->replaceScene(scene);
}
