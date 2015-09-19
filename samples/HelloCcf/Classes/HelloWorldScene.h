#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PeerButton.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
//    void menuPeerCallback(cocos2d::Ref* pSender);

protected:
    void listenToPeerUpdate(cocos2d::EventCustom *event);

    void listenToPeerInvite(cocos2d::EventCustom *event);

    void listenToAcknowledgment(cocos2d::EventCustom *event);
    
    void schedulePeer(float dt);

    void scheduleAcknowledgement(float dt);
    
    void schedulePop(float dt);

    void initListView();
    
    void selectedItemEvent(Ref* pSender, ListView::EventType type);

    Widget* queryPeerMenuItem(tagPEER peer);
    
    ListView* _listView;
};

#endif // __HELLOWORLD_SCENE_H__
