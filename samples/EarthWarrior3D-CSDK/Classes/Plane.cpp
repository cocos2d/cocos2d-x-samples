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
 
#include "Plane.h"
#include "PublicApi.h"
#include "Sprite3DEffect.h"


const float Plane::pXW = 1.1f;
const float Plane::pYW = 5.0f;
const float Plane::pZW = 1.0f;
const float Plane::pXA = 1.0f;
const float Plane::pYA = 10.0f;
const float Plane::pZA = 7.0f;

bool Plane::init(){

	pRate = 3.1415926/2;
    originX = -15.0f - 90.f;
    originY = 159.0f;
    originZ = 9.0f;

    _Model = EffectSprite3D::createFromObjFileAndTexture("playerv002.c3b", "playerv002_256.png");
    if(_Model){
        _Model->setScale(55);
        GameEntity::UseOutlineEffect(static_cast<Sprite3D*>(_Model), 0.03, Color3B(0,0,0));
        _Model->setRotation3D(Vec3(originX,originY,originZ));
        this->setRotation3D(Vec3(originX, originY, originZ));
        this->addChild(_Model);
        this->scheduleUpdate();
    }
    return true;
}

void Plane::update(float dt){
    pRate+=0.01;
    _Model->setRotation3D(Vec3(0-pXA*sin(pXW*pRate),0,0-pZA*sin(pZW*pRate)));
}