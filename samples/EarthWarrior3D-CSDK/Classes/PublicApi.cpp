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
