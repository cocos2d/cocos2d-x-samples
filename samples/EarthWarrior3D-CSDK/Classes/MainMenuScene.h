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

#ifndef __Moon3d__MainMenuScene__
#define __Moon3d__MainMenuScene__

#include "cocos2d.h"
#include "Plane.h"

USING_NS_CC;

class CCFLayer;
class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainMenuScene);
    void update(float dt);
private:
    void startgame(cocos2d::Ref* sender);
    void pkgame(cocos2d::Ref* sender);
    void license(cocos2d::Ref* sender);
    void credits(cocos2d::Ref* sender);
    Plane* plane;
    float pRate;
    void startgame_callback();
    void license_callback();
    void credits_callback();
    void pkgame_callback();
    
    void listenToAcknowledgment(cocos2d::EventCustom *event);
    void scheduleAcknowledgement(float dt);
    
    void listenToPeerInvite(cocos2d::EventCustom *event);    
    void scheduleInvite(float dt);
    
    void listenToStartControl(cocos2d::EventCustom *event);    
private:
    
    MenuItemSprite* startgame_item;
    MenuItemSprite* license_item;
    MenuItemSprite* credits_item;
    MenuItemSprite* pk_item;

};

#endif /* defined(__Moon3d__MainMenuScene__) */
