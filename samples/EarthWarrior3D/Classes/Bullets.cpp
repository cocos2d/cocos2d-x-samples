//
//  Bullet.cpp
//  Moon3d
//
//  Created by Hao Wu on 3/4/14.
//
//

#include "Bullets.h"
#include "3d/Sprite3D.h"
#include "consts.h"
#include "GameLayer.h"
#include "GameEntity.h"
#include "GameControllers.h"
#include "Enemies.h"
#include "ParticleManager.h"

bool Bullet::init()
{
    _Model = Sprite::create("bullets.png", Rect(5,8,24,32));
    //_Model = ParticleSystemQuad::create("missileFlare.plist");
    if(_Model)
    {
        addChild(_Model);
        _radius=10;
        _type = kEnemyBullet;
        _owner = kEnemy;
        _damage = 10;
        
        auto part_frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("toonFlare.png");
        ValueMap vm=ParticleManager::getInstance()->GetPlistData("missileFlare");
        ParticleSystemQuad *p = ParticleSystemQuad::create(vm,part_frame);
        //p->setEndColor(Color4F(1,0,0,1));
        //p->setStartColor(Color4F(1,0,0,1));
        p->setPositionType(tPositionType::GROUPED);
        p->setScale(2.5);
        p->setTotalParticles(2);
        _Model->addChild(p,-1);
        p->setPosition(Point(_Model->getContentSize()/2));
        setScale(1.5);
        //static_cast<Sprite*>(_Model)->setFlippedY(true);
        return true;
    }
    return false;
}
bool PlayerBullet::init()
{
    _Model = Sprite::create("bullets.png", Rect(54, 57, 36, 67));
    if(_Model)
    {
        addChild(_Model);
        _radius=10;
        _type = kPlayerBullet;
        _owner = kPlayer;
        _damage = 2;
        return true;
    }
    return false;
}

void Bullet::setVector(Point vec)
{
    _vector = vec;
}

Point Bullet::getVector()
{
    return _vector;
}
void Bullet::reset()
{
    setRotation(0);
}

bool Missile::init()
{
    _Model = Sprite3D::create("daodanv001.obj", "daodan_32.png");
    if(_Model)
    {
        addChild(_Model);
        _radius=10;
        _type = kPlayerMissiles;
        _owner = kPlayer;
        _Model->setScale(3);
        _Model->setRotation3D(Vertex3F(90,0,0));
        _damage = 20;
        static_cast<Sprite3D*>(_Model)->setOutline(0.3, Color3B(0,0,0));
        
        _left = (CCRANDOM_MINUS1_1()>0);
        if(_left)
            _yRotSpeed *= -1;
        
        
        // missile effects

        auto part2_frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("toonSmoke.png");
        ValueMap vm2=ParticleManager::getInstance()->GetPlistData("emission");
        auto part2 = ParticleSystemQuad::create(vm2,part2_frame);
        addChild(part2,1);
        part2->setPosition(0,-34);
        part2->setPositionType(tPositionType::GROUPED);
        //part2->setScale(2.5);
        
        
        auto part1_frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("toonFlare.png");
        ValueMap vm1=ParticleManager::getInstance()->GetPlistData("missileFlare");
        auto part1 = ParticleSystemQuad::create(vm1,part1_frame);
        addChild(part1,2);
        part1->setPosition(0,-30);
        part1->setPositionType(tPositionType::GROUPED);
        part1->setScale(2.5);
        return true;
    }
    return false;
}

void Missile::update(float dt)
{
    if(!_target)
    {
        //setTarget(static_cast<GameLayer*>(getParent())->_testDummy);//very hacky
        setTarget(static_cast<GameEntity*>(EnemyController::enemies.getRandomObject()));
    }
    if(_target){
        //turn towards the target
        float angle = -CC_RADIANS_TO_DEGREES((getPosition() - _target->getPosition()).getAngle());
        if(fabsf(angle-90)>70)
        {
            //too much angle to track, get another target instead
            _target = nullptr;
        }
        float curRot = getRotation();
        float angleDif = std::min(std::max((angle-90) - curRot, -_turnRate*dt), _turnRate*dt);
        
        float f = curRot + angleDif;
        setRotation(f);
        setPosition(getPosition()+Point(sinf(CC_DEGREES_TO_RADIANS(f))*_velocity,cosf(CC_DEGREES_TO_RADIANS(f))*_velocity) + _vector*dt);
        _vector = _vector * (1-dt);
        
    }
    else{
        float f = getRotation();
        setRotation(f);
        setPosition(getPosition()+Point(sinf(CC_DEGREES_TO_RADIANS(f))*_velocity,cosf(CC_DEGREES_TO_RADIANS(f))*_velocity) + _vector*dt);
        _vector = _vector * (1-dt*0.5);
    }
    // missiles need to rotate
    _yRotation += _yRotSpeed*dt;
    _Model->setRotation3D(Vertex3F(90,_yRotation, 0));
    
    
    
    
    _velocity += _accel*dt;
}

void Missile::reset()
{
    setTarget(nullptr);
    _velocity = 0;
}

