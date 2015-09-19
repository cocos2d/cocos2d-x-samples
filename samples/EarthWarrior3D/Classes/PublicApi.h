//
//  PublicApi.h
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#ifndef __Moon3d__PublicApi__
#define __Moon3d__PublicApi__

#include "cocos2d.h"
#define visible_size_macro Director::getInstance()->getVisibleSize()
#define origin_point Director::getInstance()->getVisibleOrigin();
class PublicApi
{
public:
    static float hp2percent(float hp);
protected:
    
};

#endif /* defined(__Moon3d__PublicApi__) */
