//
//  Effects.cpp
//  Moon3d
//
//  Created by Hao Wu on 3/6/14.
//
//

#include "Effects.h"

Node* EffectManager::_effectLayer = nullptr;
Vector<SmallExplosion*> EffectManager::_smallExplPool;
Vector<BigExplosion*> EffectManager::_bigExplPool;

void EffectManager::createExplosion(Point pos)
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

void EffectManager::createBigExplosion(Point pos)
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