#ifndef _BOX2D_VIEW_H_
#define _BOX2D_VIEW_H_

#include "cocos2d.h"

class MenuLayer : public cocos2d::Layer
{
    int        m_entryID;
    cocos2d::EventListenerTouchOneByOne* _touchListener;
public:
    MenuLayer(void);
    virtual ~MenuLayer(void);

    bool initWithEntryID(int entryId);

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);


    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

public:
    static MenuLayer* menuWithEntryID(int entryId);
};

struct TestEntry;
class Test;
class Box2DView : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    Box2DView(void);
    virtual ~Box2DView(void);

    bool initWithEntryID(int entryId);
    std::string title() const;
    virtual void draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;

//    virtual void registerWithTouchDispatcher();
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
    //virtual void accelerometer(UIAccelerometer* accelerometer, Acceleration* acceleration);

    static Box2DView* viewWithEntryID(int entryId);

protected:
    void onDraw(const kmMat4 &transform, bool transformUpdated);

    cocos2d::EventListenerTouchOneByOne* _touchListener;
    cocos2d::EventListenerKeyboard* _keyboardListener;
    TestEntry*     m_entry;
    Test*          m_test;
    int            m_entryID;
    cocos2d::CustomCommand _customCmd;
};

#endif
