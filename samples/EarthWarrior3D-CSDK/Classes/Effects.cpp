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

#include "Effects.h"

Node* EffectManager::_effectLayer = nullptr;
Vector<SmallExplosion*> EffectManager::_smallExplPool;
Vector<BigExplosion*> EffectManager::_bigExplPool;

void EffectManager::createExplosion(Vec2 pos)
{
    if(!_effectLayer)
    {
        return;
    }
    
    SmallExplosion* explosion = nullptr;
    
    if (!_smallExplPool.empty())
    {
        explosion = _smallExplPool.back();
        _smallExplPool.popBack();
    }
    else
    {
        explosion = SmallExplosion::create();
        explosion->retain();
    }
    
    explosion->createExplosion(_effectLayer, pos);

}

void EffectManager::createBigExplosion(Vec2 pos)
{
    if(!_effectLayer)
    {
        return;
    }
    
    BigExplosion* explosion = nullptr;
    
    if (!_bigExplPool.empty())
    {
        explosion = _bigExplPool.back();
        _bigExplPool.popBack();
    }
    else
    {
        explosion = BigExplosion::create();
        explosion->retain();
    }
    
    explosion->createExplosion(_effectLayer, pos);
    
}

void EffectManager::setLayer(Node *layer)
{
    _effectLayer = layer;
}