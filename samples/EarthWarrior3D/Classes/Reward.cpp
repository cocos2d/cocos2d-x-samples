//
//  Reward.cpp
//  Moon3d
//
//  Created by Jun Li on 5/20/14.
//
//

#include "Reward.h"
#include "Enemies.h"

void Reward::gain(long count)
{
    _count += count;
}

void Reward::move(float y, float dt)
{
    forward(y);
}

void Reward::reset()
{
    _alive = true;
}

bool Reward::alive()
{
    return _alive;
}

bool Potion::init()
{
    _count = 10;
    _Model = CCSprite::create("potion2.png");
    if(_Model)
    {
        addChild(_Model);
        _count = 10;
        _radius = 30;
        return true;
    }
    return false;
}
void Potion::reset()
{
    Reward::reset();
    _target = nullptr;
    _count = 10;
}

void Potion::setTurnRate(float turn)
{
}

float Potion::getTurnRate()
{
    return _turn;
}
void Potion::move(float y, float dt)
{
    switch(_moveMode)
    {
        case moveMode::kTurn:
            forward(y, getTurnRate()*dt);
            break;
        default:
            //setPosition(getPosition()+pos);
            forward(y);
    }
}

void Potion::gain(long count)
{
    _count += count;
    
    if (_count > 100) {
        _count = 100;
    }
}



