#include "MainMenuScene.h"
#include "FriendControlScene.h"
#include "CCFPlayer.h"
#include "ParticleManager.h"
#include "ConnectionInterface.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif

USING_NS_CC;

Scene* FriendControl::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = FriendControl::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    layer->setTag(1002);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FriendControl::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(FriendControl::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                 origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(/*leftItem, rightItem, addItem, */closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Move the plane and see what happen in another screen", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(FriendControl::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(FriendControl::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(FriendControl::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    ParticleManager::getInstance()->AddPlistData("engine.plist", "engine");
    
    _friendPlayer = CCFPlayer::create();
    if(_friendPlayer)
    {
        addChild(_friendPlayer);
    
        _friendPlayer->setPosition(Vec2(visibleSize.width/2 + origin.x, -100));
        _friendPlayer->runAction(Sequence::create(
                                        DelayTime::create(0.75),
                                        Spawn::create(
                                                      EaseBackOut::create(MoveTo::create(1.7,Vec2(visibleSize.width/2,visibleSize.height/3))),
                                                      EaseSineOut::create(RotateBy::create(1.7,Vec3(0,720,0))),
                                                      nullptr
                                                      ),
                                        CallFunc::create(CC_CALLBACK_0(FriendControl::schedulePlayer,this)),nullptr));
    
    }
    
    auto peerDisconnectListener = EventListenerCustom::create("IntelCCFDisconnect", CC_CALLBACK_1(FriendControl::listenToDisconnect, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(peerDisconnectListener, this);
    
    return true;
}

void FriendControl::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CCF_ACTIVITY_CLASSNAME, "remoteDisconnectJni", "()V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
    
    Director::getInstance()->replaceScene(MainMenuScene::createScene());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void FriendControl::schedulePlayer()
{
    _friendPlayer->scheduleUpdate();
}

void FriendControl::listenToDisconnect(cocos2d::EventCustom *event)
{
    this->schedule(schedule_selector(FriendControl::scheduleReturnMainMenu),0.1,0,0);
}

void FriendControl::scheduleReturnMainMenu(float dt)
{
    Director::getInstance()->replaceScene(MainMenuScene::createScene());
}

bool FriendControl::onTouchBegan(Touch *touch, Event *event)
{
    return true;
}

long g_serialNo = 1;
void FriendControl::onTouchMoved(Touch *touch, Event *event)
{
    Point prev = _friendPlayer->getPosition();
    Point delta =touch->getDelta();
    _friendPlayer->setPosition(prev + delta);
    
    prev = prev - Point(visibleSize.width/2, visibleSize.height/2);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;

    std::string strMessage = StringUtils::format("{\"serialNo\":%ld, \"type\":4, \"prevX\":%.2f, \"prevY\":%.2f, \"deltaX\":%.2f, \"deltaY\":%.2f}", g_serialNo++, prev.x, prev.y, delta.x, delta.y);
    if (JniHelper::getStaticMethodInfo(t, CCF_ACTIVITY_CLASSNAME, "friendControl", "(Ljava/lang/String;)V")) {
        jstring stringArg1 = t.env->NewStringUTF(strMessage.c_str());
        CCLOG("Doc. %s", strMessage.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
#endif
}

void FriendControl::onTouchEnded(Touch *touch, Event *event)
{
}
