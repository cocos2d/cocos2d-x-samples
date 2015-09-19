//
//  PopLayer.cpp
//  HelloCcf
//
//  Created by calf on 14-7-25.
//
//

#include "PopLayer.h"
#include "ConnectionInterface.h"

Scene * PopLayer::scene()
{
	Scene * scene = NULL;
	do
	{
		scene = CCScene::create();
		PopLayer * layer = PopLayer::create();
		scene->addChild(layer);
	}
	while(0);
    
	return scene;
}

bool PopLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
        
		Size winSize = Director::getInstance()->getWinSize();
        
		Sprite * background = Sprite::create("listviewbg.png");
        background->setScale(2);
		m_bgSprite = background;
		background->setPosition(Vec2(winSize.width/2,winSize.height/2));
		this->addChild(background);
        
		Size contentSize = background->getContentSize();
		m_size = contentSize;
        
        auto item1 = MenuItemLabel::create(Label::create("Accept","fonts/Marker Felt.ttf", 20), CC_CALLBACK_1(PopLayer::yesButton, this));
		auto item2 = MenuItemLabel::create(Label::create("Reject","fonts/Marker Felt.ttf", 20), CC_CALLBACK_1(PopLayer::noButton, this));
        
		Menu * menu = Menu::create(item1,item2,NULL);
		menu->alignItemsHorizontallyWithPadding(50);
		menu->setPosition(Vec2(contentSize.width/2,contentSize.height/3));
        
		background->addChild(menu);
        
		this->setTitle();
		this->setContent();
        
		bRet = true;
	}
	while(0);
    
	return bRet;
}

void PopLayer::yesButton(Ref *pSender)
{
    ConnectionInterface::SendInviteResponse(true);
    
    CCLOG("yesButton");
    cocos2d::EventCustom event("OnStartControl");
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    
    this->removeFromParent();
}

void PopLayer::noButton(Ref *pSender)
{
    ConnectionInterface::SendInviteResponse(false);
    this->removeFromParent();
}

void PopLayer::setTitle()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto title = Label::create("Earth Warrior invite", "fonts/Marker Felt.ttf", 24);
	title->setPosition(Vec2(m_size.width/2,m_size.height-title->getContentSize().height/2));
	m_bgSprite->addChild(title);
#endif
}

void PopLayer::setContent()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
 
	auto content = Label::create("Accept connection", "fonts/Marker Felt.ttf",24);
	content->setPosition(Vec2(m_size.width/2,m_size.height/2));
    content->setHorizontalAlignment(TextHAlignment::LEFT);
	m_bgSprite->addChild(content);
#endif
}