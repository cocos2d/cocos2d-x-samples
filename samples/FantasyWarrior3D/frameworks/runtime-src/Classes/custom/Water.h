//
//  water.h
//  watertest
//
//  Created by WuHao on 14/10/11.
//
//

#ifndef __watertest__water__
#define __watertest__water__

#include "cocos2d.h"

USING_NS_CC;

NS_CC_BEGIN

class Water : public cocos2d::Sprite
{
public:
    static Water * create(const std::string& tex1,const std::string& tex2,const std::string& tex3, const cocos2d::Size& size, float hSpeed, float vSpeed, float saturation);
//    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
protected:
//    CustomCommand _beforeDraw;
//    CustomCommand _afterDraw;
//    void onBeforeDraw();
//    void onAfterDraw();
};

NS_CC_END

#endif