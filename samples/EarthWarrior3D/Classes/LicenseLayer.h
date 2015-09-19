//
//  LicenseLayer.h
//  Moon3d
//
//  Created by Rye on 14-3-14.
//
//

#ifndef __Moon3d__LicenseLayer__
#define __Moon3d__LicenseLayer__

#include "cocos2d.h"

USING_NS_CC;

class LicenseLayer : public Layer
{
public:
    
    static LicenseLayer* create(const char* type_file_name);
    
    virtual bool init();
    
private:

    MenuItemSprite* license;
    
    const char* type_file_name;
    
    void dismiss();
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
};

#endif /* defined(__Moon3d__LicenseLayer__) */
