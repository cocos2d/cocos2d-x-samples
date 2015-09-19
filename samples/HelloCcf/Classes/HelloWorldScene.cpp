#include "HelloWorldScene.h"
#include "PopLayer.h"
#include "ChatScene.h"

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    layer->setTag(10086);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello Intel CCF\nDiscovery Node would be listed here", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    auto peerListener = EventListenerCustom::create("IntelCCFPeerUpdate", CC_CALLBACK_1(HelloWorld::listenToPeerUpdate, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(peerListener, this);
    
    auto peerInviteListener = EventListenerCustom::create("IntelCCFPeerInvite", CC_CALLBACK_1(HelloWorld::listenToPeerInvite, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(peerInviteListener, this);
    
    auto peerAcknowledgmentListener = EventListenerCustom::create("IntelCCFInviteAcknowledgment", CC_CALLBACK_1(HelloWorld::listenToAcknowledgment, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(peerAcknowledgmentListener, this);
    
    initListView();

    schedulePeer(0);
    
    return true;
}

void HelloWorld::initListView()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _listView = ListView::create();
    _listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    _listView->setTouchEnabled(true);
    _listView->setBounceEnabled(true);
    _listView->setBackGroundImage("listviewbg.png");
    _listView->setBackGroundImageScale9Enabled(true);
    _listView->setSize(Size(480, visibleSize.height));
    _listView->setPosition(Point(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
    _listView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(HelloWorld::selectedItemEvent, this));

    addChild(_listView,1);
}

void HelloWorld::selectedItemEvent(Ref *pSender, ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            Widget *tempWiget = listView->getItem(listView->getCurSelectedIndex());
            PeerButton *tempButton = (PeerButton *)tempWiget->getChildByTag(10011);
            if (tempButton) {
                ConnectionInterface::InvitePeer(tempButton->getPeer());
            }
            
            break;
        }
        default:
            break;
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    ConnectionInterface::Disconnect();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::listenToPeerUpdate(EventCustom *event)
{
    this->scheduleOnce(schedule_selector(HelloWorld::schedulePeer), 0);
}

void HelloWorld::schedulePeer(float dt)
{
    std::list<tagPEER> listPeer;
    ConnectionInterface::getPeerList(listPeer);
    
    if (listPeer.size() == 0) return;
    
    while(listPeer.size()){
        tagPEER tempPeer = listPeer.front();
        
        CCLOG("HelloWorld schedulePeer:%s", tempPeer._sessionName.c_str());

        Widget *pItem = queryPeerMenuItem(tempPeer);
        if (tempPeer.add && pItem == NULL) {

            PeerButton* custom_button = PeerButton::create("backtotoppressed.png", "backtotopnormal.png");
            custom_button->setTitleText(tempPeer._sessionName);
            custom_button->setTitleFontSize(20);
            custom_button->setScale9Enabled(true);
            custom_button->setPeer(tempPeer);
            custom_button->setTag(10011);
            
            
            Layout *custom_item = Layout::create();
            custom_item->setContentSize(custom_button->getContentSize());
            custom_item->setTouchEnabled(true);
            custom_item->setTag(10010);
            custom_item->addChild(custom_button, 0);
            custom_button->setPosition(Vec2(_listView->getContentSize().width/2, -100));
            
            _listView->addChild(custom_item);
        }
        
        if(!tempPeer.add && pItem != NULL){
            pItem->removeFromParent();
        }
        
        listPeer.pop_front();
    }
}

void HelloWorld::listenToPeerInvite(EventCustom *event)
{
    this->scheduleOnce(schedule_selector(HelloWorld::schedulePop), 0);
}

void HelloWorld::schedulePop(float dt)
{
    auto popLayer = PopLayer::create();
    addChild(popLayer, 2);
}

void HelloWorld::listenToAcknowledgment(cocos2d::EventCustom *event)
{
    this->scheduleOnce(schedule_selector(HelloWorld::scheduleAcknowledgement), 0);
}

void HelloWorld::scheduleAcknowledgement(float dt)
{
    auto scene = ChatLayer::createScene();
    Director::getInstance()->replaceScene(scene);
}

Widget* HelloWorld::queryPeerMenuItem(tagPEER peer)
{
    for (auto& child : _listView->getChildren())
    {
        if(child && child->getTag() == 10010)
        {
            PeerButton *tempButton = (PeerButton *)child->getChildByTag(10011);
            if (tempButton && tempButton->getPeer()._sessionId == peer._sessionId) {
                return  (Widget*)child;
            }
        }
    }
    
    return NULL;
}
