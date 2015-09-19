//
//  GameOverLayer.h
//  Moon3d
//
//  Created by Jacky on 14-3-12.
//
//

#ifndef __Moon3d__GameOverLayer__
#define __Moon3d__GameOverLayer__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class GameOverLayer : public LayerColor
{
public:
    
    static GameOverLayer* create(int score);
    
    virtual bool init();
    
private:
    
    int m_score;
    MenuItemSprite* backtomenu_Item;
    MenuItemSprite* playagain_Item;
    
    void ShowScore();
    
    void menu_backtomenu_Callback(Ref* sender);
    void menu_playagain_Callback(Ref* sender);
    void menu_backtomenu();
    void menu_playagain();
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
};

#endif /* defined(__Moon3d__GameOverLayer__) */
