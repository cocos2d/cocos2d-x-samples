//
//  PublicApi.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "PublicApi.h"
USING_NS_CC;

float PublicApi::hp2percent(float hp){
    float percent = 100.0f;
    if(hp>=100){
        percent = 100.f;
    }else if(83<=hp && hp<=99){
        percent = 100.0/7*6;
    }else if(65<=hp && hp<=82){
        percent = 100.0/7*5;
    }else if(47<=hp && hp<=64){
        percent = 100.0/7*4;
    }else if(29<=hp && hp<=46){
        percent = 100.0/7*3;
    }else if(11<=hp && hp<=28){
        percent = 100.0/7*2;
    }else if(1<=hp && hp<=10){
        percent = 100.0/7*1;
    }else if(hp<=0){
        percent = 0;
    }
    return percent;
}
