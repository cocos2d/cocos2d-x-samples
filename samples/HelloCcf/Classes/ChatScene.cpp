//
//  ChatLayer.cpp
//  HelloCcf
//
//  Created by calf on 14-7-28.
//
//

#include "ChatScene.h"
#include "ConnectionInterface.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* ChatLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChatLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    layer->setTag(10012);
        
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChatLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeBtn = Button::create("CloseNormal.png");
	closeBtn->setPosition(Vec2(origin.x + visibleSize.width - closeBtn->getContentSize().width/2 ,
                                origin.y + visibleSize.height - closeBtn->getContentSize().height/2));
    closeBtn->setTag(217);
    addChild(closeBtn, 0);
    closeBtn->addTouchEventListener(CC_CALLBACK_2(ChatLayer::touchEvent,this));
    
    auto sendBtn = Button::create("backtotoppressed.png");
    sendBtn->setTitleText("send");
    sendBtn->setTitleFontSize(26);
	sendBtn->setPosition(Vec2(origin.x + visibleSize.width - sendBtn->getContentSize().width/2 ,
                               origin.y + sendBtn->getContentSize().height/2));
    sendBtn->setTag(212);
    addChild(sendBtn, 0);
    sendBtn->addTouchEventListener(CC_CALLBACK_2(ChatLayer::touchEvent,this));
    
    textField = TextField::create("input text here", "", 26);
	textField->setPosition(Vec2(origin.x + visibleSize.width/2 - sendBtn->getContentSize().width/2 ,
                              origin.y + sendBtn->getContentSize().height/2));
    textField->setTextHorizontalAlignment(TextHAlignment::LEFT);
    addChild(textField, 0);

    initListView();
    
    auto peerListener1 = EventListenerCustom::create("IntelCCFReceiveMessage", CC_CALLBACK_1(ChatLayer::listenToReceiveMessage, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(peerListener1, this);
    
    auto peerListener2 = EventListenerCustom::create("IntelCCFDisconnect", CC_CALLBACK_1(ChatLayer::listenToDisconnect, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(peerListener2, this);
    
    return true;
}

void ChatLayer::initListView()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _listView = ListView::create();
    _listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    _listView->setTouchEnabled(true);
    _listView->setBounceEnabled(true);
    _listView->setBackGroundImage("listviewbg.png");
    _listView->setBackGroundImageScale9Enabled(true);
    _listView->setSize(Size(visibleSize.width, visibleSize.height - 100));
    _listView->setPosition(Point(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
    _listView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    addChild(_listView,1);
}

void ChatLayer::touchEvent(Ref*pSender, Widget::TouchEventType type)
{
    Button *btn = (Button *)pSender;
    if (type == Widget::TouchEventType::ENDED)
    {
        switch (btn->getTag()) {
            case 212:
            {
                ConnectionInterface::SendMessage(textField->getStringValue());
                
                Text* message = Text::create(textField->getStringValue(),"fonts/Marker Felt.ttf",32);
                message->ignoreContentAdaptWithSize(true);
                message->setTextHorizontalAlignment(TextHAlignment::LEFT);
                message->setTouchScaleChangeEnabled(false);
                message->setTouchEnabled(false);

                _listView->pushBackCustomItem(message);
                textField->setText("");
            }
                break;
            case 217:
                ConnectionInterface::Disconnect();
                auto helloworld = HelloWorld::createScene();
                Director::getInstance()->replaceScene(helloworld);
                break;
        }
        
    }
}


void ChatLayer::listenToReceiveMessage(EventCustom *event)
{
    this->scheduleOnce(schedule_selector(ChatLayer::scheduleReceiveMessage), 0);
}

void ChatLayer::scheduleReceiveMessage(float dt)
{
    std::list<std::string>::iterator iter;
    std::list<std::string> listMessage;
    ConnectionInterface::getMessageList(listMessage);
    
    while (listMessage.size()) {
        std::string msg = listMessage.front();
        
        Text* message = Text::create(msg,"fonts/Marker Felt.ttf",32);
        message->ignoreContentAdaptWithSize(true);
        message->setTextHorizontalAlignment(TextHAlignment::LEFT);
        message->setTouchScaleChangeEnabled(false);
        message->setTouchEnabled(false);
        message->setColor(Color3B::GREEN);
        _listView->pushBackCustomItem(message);
        
        listMessage.pop_front();
    }
}

void ChatLayer::listenToDisconnect(EventCustom *event)
{
    this->scheduleOnce(schedule_selector(ChatLayer::scheduleDisconnect), 0);
}

void ChatLayer::scheduleDisconnect(float dt)
{
    auto helloworld = HelloWorld::createScene();
    Director::getInstance()->replaceScene(helloworld);
}


