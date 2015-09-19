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

#include "CCFLayer.h"

CCFLayer* CCFLayer::create(const char* type_file_name)
{
	CCFLayer *pRet = new CCFLayer();
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


bool CCFLayer::init()
{
    auto window = Sprite::create(type_file_name);
    //window->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(window,1);
    window->setScale(0.2f);
    window->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f),
                                         ScaleTo::create(0.1f, 0.9f),
                                         ScaleTo::create(0.1f, 1.0f),
                                         NULL));
    
    this->setContentSize(window->getContentSize());

    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(CCFLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CCFLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CCFLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto peerListener = EventListenerCustom::create("IntelCCFPeerUpdate", CC_CALLBACK_1(CCFLayer::listenToPeerUpdate, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(peerListener, this);

    initListView();
    
    schedulePeer(0);

    return true;
}

void CCFLayer::dismiss(){
    this->removeFromParent();
}

bool CCFLayer::onTouchBegan(Touch *touch, Event *event)
{
    this->runAction(Sequence::create(ScaleTo::create(0.2f, 0.2f),CallFunc::create(CC_CALLBACK_0(CCFLayer::dismiss,this)), NULL));
    return true;
}
void CCFLayer::onTouchMoved(Touch *touch, Event *event)
{
    
}
void CCFLayer::onTouchEnded(Touch *touch, Event *event)
{
}

void CCFLayer::initListView()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _listView = ListView::create();
    _listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    _listView->setTouchEnabled(true);
    _listView->setBounceEnabled(true);
    _listView->setBackGroundImage("listviewbg.png");
    _listView->setBackGroundImageScale9Enabled(true);
    _listView->setSize(this->getContentSize());//Size(480, visibleSize.height));
//    _listView->setPosition(Point(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
    _listView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(CCFLayer::selectedItemEvent, this));
    
    addChild(_listView,1);
}

void CCFLayer::selectedItemEvent(Ref *pSender, ListView::EventType type)
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

void CCFLayer::listenToPeerUpdate(EventCustom *event)
{
    this->scheduleOnce(schedule_selector(CCFLayer::schedulePeer), 0);
}

void CCFLayer::schedulePeer(float dt)
{
    std::list<tagPEER> listPeer;
    ConnectionInterface::getPeerList(listPeer);
    
    if (listPeer.size() == 0) return;
    
    while(listPeer.size()){
        tagPEER tempPeer = listPeer.front();
        
        CCLOG("CCFLayer schedulePeer:%s", tempPeer._sessionName.c_str());
        
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


Widget* CCFLayer::queryPeerMenuItem(tagPEER peer)
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