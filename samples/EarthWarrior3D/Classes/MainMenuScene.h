//
//  MainMenuScene.h
//  Moon3d
//
//  Created by Rye on 14-3-12.
//
//

#ifndef __Moon3d__MainMenuScene__
#define __Moon3d__MainMenuScene__

#include "cocos2d.h"
#include "3d/Sprite3D.h"
#include "Plane.h"

USING_NS_CC;

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainMenuScene);
    void update(float dt);
    
    void jniStartGame(const char* something);

    void jniStartControl();
    
private:
    void startgame(cocos2d::Ref* sender);
    void pkgame(cocos2d::Ref* sender);
    void license(cocos2d::Ref* sender);
    void credits(cocos2d::Ref* sender);
    Plane* plane;
    float pRate = 3.1415926/2;
    void startgame_callback();
    void pkgame_callback();
    void license_callback();
    void credits_callback();
    
    void scheduleStartGame(float dt);
    
    void scheduleStartControl(float dt);
        
private:
    MenuItemSprite* startgame_item;
    MenuItemSprite* pk_item;
    MenuItemSprite* license_item;
    MenuItemSprite* credits_item;

};

#endif /* defined(__Moon3d__MainMenuScene__) */
