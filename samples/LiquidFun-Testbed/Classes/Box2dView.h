/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

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
