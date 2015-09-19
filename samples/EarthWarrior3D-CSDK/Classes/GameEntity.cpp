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

#include "GameEntity.h"
#include "Sprite3DEffect.h"

USING_NS_CC_MATH;

Node *GameEntity::getModel(){
    return _Model;
}

Vec3 GameEntity::getOrientation(){
    return _orientation;
}

void GameEntity::forward(float dist){
    float f = getRotation();
    setPosition(getPosition()
                +Vec2(
                       sinf(CC_DEGREES_TO_RADIANS(f))*dist,
                       cosf(CC_DEGREES_TO_RADIANS(f))*dist)
                );
}
void GameEntity::forward(float dist, float angle)
{
    setRotation(getRotation()-angle);
    forward(dist);
}

void GameEntity::UseOutlineEffect(Sprite3D* sprite, float width, Color3B color)
{
    if(nullptr == sprite)
        CCLOGERROR("Can not apply outline effect to a null Sprite3D");
    EffectSprite3D* _effectSprite3D = dynamic_cast<EffectSprite3D*>(sprite);
    if(_effectSprite3D)
    {
        Effect3DOutline* effect(nullptr);
        for (ssize_t index = 0; index < _effectSprite3D->getEffectCount(); ++index)
        {
            effect = dynamic_cast<Effect3DOutline*>(_effectSprite3D->getEffect(index));
            if(nullptr != effect) break;
        }
        if(effect)
        {
            effect->setOutlineColor(Vec3(color.r/255.0f, color.g/255.0f, color.b/255.0f));
            effect->setOutlineWidth(width);
        }
        else
        {
            effect = Effect3DOutline::create();
            effect->setOutlineColor(Vec3(color.r/255.0f, color.g/255.0f, color.b/255.0f));
            effect->setOutlineWidth(width);
            _effectSprite3D->addEffect(effect, 1);
        }
        
    }
//    Sprite3DOutlineEffect* effect = Sprite3DOutlineEffect::create();
//    sprite->setEffect(effect);
//    effect->setOutlineColor(Vec3(color.r/255.0f, color.g/255.0f, color.b/255.0f));
//    effect->setOutlineWidth(width);
}