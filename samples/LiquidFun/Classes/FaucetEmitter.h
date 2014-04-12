/****************************************************************************
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
#ifndef __FAUCETEMITTER_H__
#define __FAUCETEMITTER_H__

#include <Box2D/Box2D.h>
#include "cocos2d.h"

// Emits particles along a line, as if it were some kind of faucet.
class FaucetEmitter {
 public:
  // world is a pointer to the world.
  // origin is center of faucet
  // startingVelocity indicates starting velocity for particles
  // emitRate is particles/second
  // colors is a list of colors to cycle through when creating particles
  // colorCycleTime is the time to wait before moving onto the next color.
  FaucetEmitter(b2World *world, const b2Vec2 &origin,
				const b2Vec2 &startingVelocity, float32 size,
				const float32 emitRate,
				const std::vector<b2ParticleColor>& colors,
				const float32 colorCycleTime);

  // dt is seconds that have passed, flags are the particle flags that you
  // want set on each particle.
  void Step(float32 dt, uint32 flags);

  void SetIsEmitting(bool val);

 private:
  // Launch direction.
  b2Vec2 m_startingVelocity;
  // Center of particle emitter
  b2Vec2 m_origin;
  // Total width of particle emitter
  float m_size;
  // Particles per second
  float m_emitRate;

  // Pointer to global world
  b2World *m_world;
  b2ParticleSystem *m_particleSystem;

  // Color you'd like the faucet spray
  std::vector<b2ParticleColor> m_colors;
  int m_currentColorIndex;
  float m_colorCycleTime;
  float m_colorTime;

  // Number particles I need to emit on the next frame
  float m_counter;

  bool m_isEmitting;
};


#endif // FAUCETEMITTER_H
