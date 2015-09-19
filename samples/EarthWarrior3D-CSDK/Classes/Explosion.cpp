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

#include "Explosion.h"
#include "Effects.h"
#include "ParticleManager.h"

USING_NS_CC;

bool SmallExplosion::init(){
    
    auto part1_frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("toonSmoke.png");
    ValueMap vm1=ParticleManager::getInstance()->GetPlistData("toonSmoke");
    part1 = ParticleSystemQuad::create(vm1);
    //part1->setDisplayFrame(part1_frame);
    part1->setTextureWithRect(part1_frame->getTexture(), part1_frame->getRect());
    this->addChild(part1);
    auto part2_frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("toonFlare.png");
    ValueMap vm2=ParticleManager::getInstance()->GetPlistData("flare");
    part2 = ParticleSystemQuad::create(vm2);
    //part2->setDisplayFrame(part2_frame);
    part2->setTextureWithRect(part2_frame->getTexture(), part2_frame->getRect());
    this->addChild(part2);
    part1->setTotalParticles(10);
    part1->setEmissionRate(9999999999);
    part2->setTotalParticles(3);
    part2->setEmissionRate(9999999999);
    part1->setRotation3D(Vec3(30,0,0));
    part2->setRotation3D(Vec3(30,0,0));
    return true;
}

void SmallExplosion::createExplosion(Node* _effectLayer, Vec2 pos){
    
    part1->setTotalParticles(8);
    part1->setEmissionRate(9999999999);
    part1->setScale(0.7);
    part2->setTotalParticles(5);
    part2->setEmissionRate(9999999999);
    _effectLayer->addChild(this,7);
    part1->setRotation3D(Vec3(30,0,0));
    part2->setRotation3D(Vec3(30,0,0));
    this->setPosition(pos);
    this->scheduleOnce(schedule_selector(SmallExplosion::recycle), 1.5);
}

void SmallExplosion::recycle(float dt){
    this->removeFromParentAndCleanup(false);
    EffectManager::_smallExplPool.pushBack(this);
}

bool BigExplosion::init(){
    auto part1_frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("toonSmoke.png");
    ValueMap vm1=ParticleManager::getInstance()->GetPlistData("toonSmoke");
    part1 = ParticleSystemQuad::create(vm1);
    //part1->setDisplayFrame(part1_frame);
    part1->setTextureWithRect(part1_frame->getTexture(), part1_frame->getRect());
    this->addChild(part1);
    auto part2_frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("toonGlow.png");
    ValueMap vm2=ParticleManager::getInstance()->GetPlistData("glow");
    part2 = ParticleSystemQuad::create(vm2);
    //part2->setDisplayFrame(part2_frame);
    part2->setTextureWithRect(part2_frame->getTexture(), part2_frame->getRect());
    this->addChild(part2);
    auto part3_frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("toonFlare2.png");
    ValueMap vm3=ParticleManager::getInstance()->GetPlistData("debris");
    part3 = ParticleSystemQuad::create(vm3);
    //part3->setDisplayFrame(part3_frame);
    part3->setTextureWithRect(part3_frame->getTexture(), part3_frame->getRect());
    this->addChild(part3);
    part1->setTotalParticles(10);
    part1->setEmissionRate(9999999999);
    part2->setTotalParticles(3);
    part2->setEmissionRate(9999999999);
    part3->setTotalParticles(20);
    part3->setEmissionRate(9999999999);
    part3->setScale(1.5);
    part1->setRotation3D(Vec3(30,0,0));
    part2->setRotation3D(Vec3(30,0,0));
    part3->setRotation3D(Vec3(30,0,0));
    return true;
}

void BigExplosion::createExplosion(Node *_effectLayer, Vec2 pos){

    _effectLayer->addChild(this,6);
    part1->resetSystem();
    part2->resetSystem();
    part3->resetSystem();
    setPosition(pos);

    this->scheduleOnce(schedule_selector(BigExplosion::recycle), 1.2);
}

void BigExplosion::recycle(float dt){
    this->removeFromParentAndCleanup(false);
    EffectManager::_bigExplPool.pushBack(this);
}

bool BulletExplosion::init(){
    
    auto texture = Director::getInstance()->getTextureCache()->addImage("player_bullet_explosion.png");
    Sprite::initWithTexture(texture);
    setTextureRect(Rect(0,0,26,17));
    //this -> setTexture(texture);
    return true;
}

void BulletExplosion::showExplosion(Vec2 point){
    auto animation = AnimationCache::getInstance()->getAnimation("bullet_expl");
    auto animate = Animate::create(animation);
    this->runAction(Sequence::create(animate,
                                     CallFuncN::create(CC_CALLBACK_1(BulletExplosion::explosionFinished,this)),                                  NULL));
    this->setScale(0.5);
    this->runAction(ScaleBy::create(0.4, 2));
    this->runAction(FadeOut::create(0.4));
    this->setPosition(point);
    this->setRotation3D(Vec3(30,0,0));
    this->setBlendFunc(BlendFunc::ADDITIVE);
    Director::getInstance()->getRunningScene()->getChildByTag(100)->getChildByTag(123)->addChild(this,3);
}

void BulletExplosion::explosionFinished(Ref* obj){
    auto expl=static_cast<Sprite*>(obj);
    expl->removeFromParentAndCleanup(false);
}
