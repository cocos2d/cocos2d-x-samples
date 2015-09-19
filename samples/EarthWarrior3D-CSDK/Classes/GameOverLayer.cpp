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

#include "GameOverLayer.h"
#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "GameLayer.h"
#include "GameControllers.h"
#include "AirCraft.h"
#include "Bullets.h"
#include <sstream>

GameOverLayer* GameOverLayer::create(int score)
{
	GameOverLayer *pRet = new GameOverLayer();
	pRet->m_score=score;
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

bool GameOverLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 50))) {
        return false;
    }
    
    auto visibleSize=Director::getInstance()->getVisibleSize();
    
    auto score_bk=Sprite::createWithSpriteFrameName("gameover_score_bk.png");
    score_bk->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(score_bk,1);
    score_bk->setScale(0.2f);
    score_bk->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f),
                                         ScaleTo::create(0.1f, 0.9f),
                                         ScaleTo::create(0.1f, 1.0f),
                                         CallFunc::create(CC_CALLBACK_0(GameOverLayer::ShowScore,this)),
                                         NULL));
    
    auto backtomenu_normal=Sprite::createWithSpriteFrameName("gameover_backtomenu.png");
    auto backtomenu_pressed=Sprite::createWithSpriteFrameName("gameover_backtomenu.png");
    backtomenu_Item = MenuItemSprite::create(backtomenu_normal,
                                           backtomenu_pressed,
                                           CC_CALLBACK_1(GameOverLayer::menu_backtomenu_Callback,this));
    
//    auto playagain_normal=Sprite::createWithSpriteFrameName("gameover_playagain.png");
//    auto playagain_pressed=Sprite::createWithSpriteFrameName("gameover_playagain.png");
//    playagain_Item = MenuItemSprite::create(playagain_normal,
//                                           playagain_pressed,
//                                           CC_CALLBACK_1(GameOverLayer::menu_playagain_Callback,this));
    
    auto menu = Menu::create(backtomenu_Item,NULL);
    menu->alignItemsHorizontallyWithPadding(20);
    menu->setPosition(visibleSize.width/2, 100);
    this->addChild(menu, 2);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameOverLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameOverLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameOverLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void GameOverLayer::ShowScore()
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    
    auto score_text=Sprite::createWithSpriteFrameName("gameover_score.png");
    score_text->setPosition(Vec2(-200, visibleSize.height/2+30));
    score_text->runAction(MoveTo::create(0.5f, Vec2(visibleSize.width/2,visibleSize.height/2+30)));
    addChild(score_text,2);
    
    std::ostringstream pScore;
    pScore<<m_score;
    auto score_label=LabelBMFont::create(pScore.str(), "gameover_score_num.fnt");
    score_label->setAnchorPoint(Vec2(0.5f,0.5f));
    score_label->setPosition(Vec2(1000,visibleSize.height/2-40));
    score_label->runAction(Sequence::create(
                           MoveTo::create(0.5f, Vec2(visibleSize.width/2,visibleSize.height/2-30)),
                                            ScaleTo::create(0.1f, 1.3f),
                                            ScaleTo::create(0.1f, 0.98f),
                                            ScaleTo::create(0.1f, 1.2f),NULL));
    addChild(score_label,2);

}

void GameOverLayer::menu_backtomenu_Callback(Ref* sender)
{
    backtomenu_Item->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f),
                                                ScaleTo::create(0.1f, 0.9f),
                                                ScaleTo::create(0.1f, 1.0f),
                                                CallFunc::create(CC_CALLBACK_0(GameOverLayer::menu_backtomenu, this)),NULL));
}

void GameOverLayer::menu_backtomenu()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    Director::getInstance()->replaceScene(MainMenuScene::createScene());
    for(int i=EnemyController::enemies.size()-1;i>=0;i--)
    {
        EnemyController::enemies.at(i)->removeFromParentAndCleanup(true);
    }
    EnemyController::enemies.clear();
    for(int i=EnemyController::showCaseEnemies.size()-1;i>=0;i--)
    {
        EnemyController::showCaseEnemies.at(i)->removeFromParentAndCleanup(true);
        //EnemyController::showCaseEnemies.erase(i);
    }
    EnemyController::showCaseEnemies.clear();
    for(int i=BulletController::bullets.size()-1;i>=0;i--)
    {
        BulletController::bullets.erase(i);
    }
    BulletController::bullets.clear();
}

void GameOverLayer::menu_playagain_Callback(Ref* sender)
{
    playagain_Item->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f),
                                                ScaleTo::create(0.1f, 0.9f),
                                                ScaleTo::create(0.1f, 1.0f),
                                               CallFunc::create(CC_CALLBACK_0(GameOverLayer::menu_playagain, this)),NULL));
    
}

void GameOverLayer::menu_playagain()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    GameLayer::isDie = false;
    for(int i=EnemyController::enemies.size()-1;i>=0;i--)
    {
        EnemyController::erase(i);
    }
    for(int i=EnemyController::showCaseEnemies.size()-1;i>=0;i--)
    {
        //EnemyController::erase(i);
        EnemyController::showCaseEnemies.at(i)->removeFromParentAndCleanup(false);
    }
    for(int i=BulletController::bullets.size()-1;i>=0;i--)
    {
        BulletController::erase(i);
    }
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

bool GameOverLayer::onTouchBegan(Touch *touch, Event *event)
{
    return true;
}
void GameOverLayer::onTouchMoved(Touch *touch, Event *event)
{
    
}
void GameOverLayer::onTouchEnded(Touch *touch, Event *event)
{
}