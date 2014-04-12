/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2014 Google, Inc

http://www.cocos2d-x.org

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
#ifndef __LIQUIDFUN_SCENE_H__
#define __LIQUIDFUN_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <list>
#include <vector>

#define MAX_EMITTERS 10

class FaucetEmitter;

class LiquidFunScene : public cocos2d::Layer
{
 private:
  // Kills particles that enter this shape.
  class ParticleKillField {
   public:
    // Instance a particle kill zone.
    ParticleKillField(
        const b2Transform& xf, const b2Shape& shape, int32 shapeSize,
        b2BlockAllocator * const allocator, b2World * const world) :
        m_transform(xf), m_allocator(allocator), m_shapeSize(shapeSize),
        m_world(world) {
      m_shape = shape.Clone(allocator);
    }

    ~ParticleKillField() { m_allocator->Free(m_shape, m_shapeSize); }

    // Destroy particles within the kill zone's area.
    void Step() {
      m_world->DestroyParticlesInShape(*m_shape, m_transform);
    }

   protected:
    b2Transform m_transform;
    b2BlockAllocator *m_allocator;
    b2Shape *m_shape;
    int32 m_shapeSize;
    b2World *m_world;
  };

  typedef std::list<FaucetEmitter*> FaucetEmitterList;
  typedef std::list<ParticleKillField*> ParticleKillFieldList;

  // The Box2D/Liquidfun world
  b2World *m_world;
  // Extents of the world (these are adjusted based upon the aspect ratio of
  // the view)
  b2Vec2 m_worldExtents;
  // Maximum and minimum extents of the world.
  float m_worldExtentMin;
  float m_worldExtentMax;
  // Extents of the world excluding the walls.
  b2Vec2 m_worldExtentsInWalls;
  b2Vec2 m_worldOffsetInWalls;

  // List of particle emitters.
  FaucetEmitterList m_emitters;

  // Allocator for kill field shapes.
  b2BlockAllocator m_shapeAllocator;
  // List of kill fields.
  ParticleKillFieldList m_killFields;

  // Shows finger / pointer locations
  cocos2d::Sprite *m_startSprite;
  cocos2d::Sprite *m_endSprite;

 private:
  LiquidFunScene();
  virtual ~LiquidFunScene();

  // Creates boundaries for world
  void CreateWalls();

  // Creates distractor balls
  void CreateBalls(const int numberOfBalls, const float relativeBallSize);

  // Creates a block of particles
  void CreateBlockOfParticles();

  // Call this before adding any emitters
  void InitEmitters();

  // Adds a single emitter at this location
  FaucetEmitter* AddEmitter(const b2Vec2& origin,
                            const std::vector<b2ParticleColor> &colors,
                            const float colorCycleRate);
  FaucetEmitter* AddEmitter(const b2Vec2& origin, const float32 faucetSize,
                            const float32 emitRate,
                            const b2Vec2& startingVelocity,
                            const std::vector<b2ParticleColor>& colors,
                            const float colorCycleRate);

  // Add a kill field.
  ParticleKillField* AddParticleKillField(const b2Transform &xf,
                                          const b2Shape &shape,
                                          const int32 shapeSize);

  void LayoutLevel(int level);
  void StartLevel();
  void Reset();

  // Create a pointer sprite.
  cocos2d::Sprite* CreatePointerSprite(
      const char * const assetName, const cocos2d::Point& position,
      const float scale);

  // Get the maximum dimension from the view size.
  float GetMaxViewDimension() const;

  // Convert a relative world coordinates to a position in meters.
  // (0.0f, 0.0f) (top, left) and (1.0f, 1.0f) = (bottom, right).
  b2Vec2 ConvertRelativePositionToWorld(const b2Vec2& relativeLocation) const;
  // Convert a size relative to world space to a size in meters.
  b2Vec2 ConvertRelativeSizeToWorld(const b2Vec2& relativeSize) const;
  // Convert a screen location to a position in meters.
  b2Vec2 ConvertScreenPositionToWorld(const b2Vec2& screenLocation) const;
  // Convert meters to screen location.
  cocos2d::Point ConvertWorldToScreenPosition(
      const b2Vec2& worldPosition) const;

  // Calculate the scale factor for sprite's size to match the specified size
  // in world space.
  float CalculateSpriteScale(cocos2d::Sprite * const sprite,
                             const b2Vec2& worldSize) const;

  // Create a ball.
  void CreateBall(const b2Vec2& worldPosition, const b2Vec2& worldSize);

  // Create a box fixture as part of the specified body.
  static b2Fixture* CreateBoxFixture(b2Body * const body,
                                     const b2Vec2& position,
                                     const b2Vec2& size);

 public:
  // Here's a difference.  Method 'init' in cocos2d-x returns bool, instead
  // of returning 'id' in cocos2d-iphone
  virtual bool init();

  // There's no 'id' in cpp, so we recommend returning the class instance
  // pointer.
  static cocos2d::Scene* scene();

  // a selector callback
  void menuCloseCallback(cocos2d::Object* pSender);

  // Called every frame
  void update(float dt);

  virtual void onEnter();
  virtual void onExit();

  // Touch events
  virtual bool ccTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  virtual void ccTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
  virtual void ccTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

  // implement the "static node()" method manually
  CREATE_FUNC(LiquidFunScene);
};

#endif // __LIQUIDFUN_SCENE_H__
