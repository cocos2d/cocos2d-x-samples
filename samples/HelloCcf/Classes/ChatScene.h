//
//  ChatScene.h
//  HelloCcf
//
//  Created by calf on 14-7-28.
//
//

#ifndef __HelloCcf__ChatScene__
#define __HelloCcf__ChatScene__

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"
using namespace cocos2d::ui;


class ChatLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
        
    // implement the "static create()" method manually
    CREATE_FUNC(ChatLayer);
    
    void receiveMessage(std::string message);
    
private:
    void listenToReceiveMessage(cocos2d::EventCustom *event);
    
    void listenToDisconnect(cocos2d::EventCustom *event);
    
    void touchEvent(Ref*pSender, Widget::TouchEventType type);
    
    void scheduleReceiveMessage(float dt);
    
    void scheduleDisconnect(float dt);
    
    void initListView();
    
    
    ListView *_listView;
    TextField *textField;
};

#endif /* defined(__HelloCcf__ChatScene__) */
