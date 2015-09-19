//
//  LisenceLayer.cpp
//  Moon3d
//
//  Created by Rye on 14-3-14.
//
//

#include "LicenseLayer.h"

LicenseLayer* LicenseLayer::create(const char* type_file_name)
{
	LicenseLayer *pRet = new LicenseLayer();
	pRet->type_file_name = type_file_name;
	if (pRet && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = NULL;
	}
    return pRet;
}


bool LicenseLayer::init()
{
    
    auto visibleSize=Director::getInstance()->getVisibleSize();
    
    auto window = Sprite::create(type_file_name);
    //window->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    addChild(window,1);
    window->setScale(0.2f);
    window->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f),
                                         ScaleTo::create(0.1f, 0.9f),
                                         ScaleTo::create(0.1f, 1.0f),
                                         NULL));
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(LicenseLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(LicenseLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(LicenseLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void LicenseLayer::dismiss(){
    this->removeFromParent();
}

bool LicenseLayer::onTouchBegan(Touch *touch, Event *event)
{
    this->runAction(Sequence::create(ScaleTo::create(0.2f, 0.2f),CallFunc::create(CC_CALLBACK_0(LicenseLayer::dismiss,this)), NULL));
    return true;
}
void LicenseLayer::onTouchMoved(Touch *touch, Event *event)
{
    
}
void LicenseLayer::onTouchEnded(Touch *touch, Event *event)
{
}