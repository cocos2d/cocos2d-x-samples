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
    auto window = Sprite::create(type_file_name);
    //window->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
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