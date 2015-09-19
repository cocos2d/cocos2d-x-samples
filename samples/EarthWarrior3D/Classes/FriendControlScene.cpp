#include "MainMenuScene.h"
#include "FriendControlScene.h"
#include "FriendPlayer.h"
#include "ParticleManager.h"
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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto leftItem = MenuItemImage::create(
                                           "b1.png",
                                           "b2.png",
                                           CC_CALLBACK_1(FriendControl::menuLeftCallback, this));

    auto rightItem = MenuItemImage::create(
                                           "f1.png",
                                           "f2.png",
                                           CC_CALLBACK_1(FriendControl::menuRightCallback, this));
    
    auto addItem = MenuItemImage::create(
                                            "r1.png",
                                            "r2.png",
                                            CC_CALLBACK_1(FriendControl::menuAddCallback, this));
   
    auto closeItem = MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(FriendControl::menuCloseCallback, this));
    
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
	addItem->setPosition(Point(origin.x + visibleSize.width/2 ,
                               origin.y + addItem->getContentSize().height/2 ));

	leftItem->setPosition(Point(origin.x + visibleSize.width/2 - leftItem->getContentSize().width - 50,
                                origin.y + leftItem->getContentSize().height/2 ));

	rightItem->setPosition(Point(origin.x + visibleSize.width/2 + rightItem->getContentSize().width + 50,
                                 origin.y + rightItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(leftItem, rightItem, addItem, closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("1 Clicking a arrow that change the bullet's direction\n2 Clicking the central point that send a 'fulmination'\n3 Clicking right-bottom button to quit", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
/*
    // add "FriendControl" splash screen"
    auto sprite = Sprite::create("potion2.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    sprite->setScale(2, 2);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
*/
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(FriendControl::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(FriendControl::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(FriendControl::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    _friendPlayer = Sprite3D::create("playerv002.obj", "playerv002_256.png");
    if(_friendPlayer)
    {
        _friendPlayer->setScale(8);
        addChild(_friendPlayer);
        _friendPlayer->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        _friendPlayer->setRotation3D(Vertex3F(90,0,0));

        static_cast<Sprite3D*>(_friendPlayer)->setOutline(0.2, Color3B(0,0,0));
    }
        
    return true;
}


void FriendControl::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "com/cocos2dx/moon3d/AppActivity", "remoteDisconnectJni", "()V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
    
    Director::getInstance()->replaceScene(MainMenuScene::createScene());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void FriendControl::menuLeftCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "com/cocos2dx/moon3d/AppActivity", "friendControl", "(Ljava/lang/String;)V")) {
        jstring stringArg1 = t.env->NewStringUTF("{\"type\":1}");
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
#endif
    
}

void FriendControl::menuRightCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "com/cocos2dx/moon3d/AppActivity", "friendControl", "(Ljava/lang/String;)V")) {
        jstring stringArg1 = t.env->NewStringUTF("{\"type\":2}");
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
#endif
}

void FriendControl::menuAddCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "com/cocos2dx/moon3d/AppActivity", "friendControl", "(Ljava/lang/String;)V")) {
        jstring stringArg1 = t.env->NewStringUTF("{\"type\":3}");
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
#endif    
}

void FriendControl::jniReturnMainMenu()
{
    log("FriendControl::jniReturnMainMenu");
    
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

void FriendControl::onTouchMoved(Touch *touch, Event *event)
{
    Point prev = _friendPlayer->getPosition();
    Point delta =touch->getDelta();
    _friendPlayer->setPosition(prev + delta);
    
    prev = prev - Point(visibleSize.width/2, visibleSize.height/2);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "com/cocos2dx/moon3d/AppActivity", "friendControl", "(Ljava/lang/String;)V")) {
        jstring stringArg1 = t.env->NewStringUTF(StringUtils::format("{\"type\":4, \"prevX\":%f, \"prevX\":%f, \"deltaX\":%f, \"deltaY\":%f}", prev.x, prev.y, delta.x, delta.y).c_str());
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
#endif
}

void FriendControl::onTouchEnded(Touch *touch, Event *event)
{
}
