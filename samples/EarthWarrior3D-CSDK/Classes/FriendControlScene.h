#ifndef __FriendControl_SCENE_H__
#define __FriendControl_SCENE_H__

#include "cocos2d.h"

class CCFPlayer;
class FriendControl : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
        
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    
protected:
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void schedulePlayer();
 
    void scheduleReturnMainMenu(float dt);
    
    void listenToDisconnect(cocos2d::EventCustom *event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(FriendControl);
    
    CCFPlayer *_friendPlayer;
    
    Size visibleSize;
};

#endif // __FriendControl_SCENE_H__
