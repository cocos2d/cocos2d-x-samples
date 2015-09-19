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

#ifndef __Moon3d__CCFLayer__
#define __Moon3d__CCFLayer__

#include "cocos2d.h"
#include "PeerButton.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

USING_NS_CC;

class CCFLayer : public Layer
{
public:
    
    static CCFLayer* create(const char* type_file_name);
    
    virtual bool init();
    
private:

    MenuItemSprite* license;
    
    const char* type_file_name;
    
    void dismiss();
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    
protected:
    
    void listenToPeerUpdate(cocos2d::EventCustom *event);
    void schedulePeer(float dt);
    
    void initListView();
    
    void selectedItemEvent(Ref* pSender, ListView::EventType type);
    
    Widget* queryPeerMenuItem(tagPEER peer);
    
    ListView* _listView;
};

#endif /* defined(__Moon3d__CCFLayer__) */
