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
#include "FaucetEmitter.h"

// world is a pointer to the world.
// origin is center of faucet
// startingVelocity indicates starting velocity for particles
// emitRate is particles/second
// color is the particle color you want
FaucetEmitter::FaucetEmitter(
    b2World *world, const b2Vec2 &origin,
	const b2Vec2 &startingVelocity, const float32 size,
	const float32 emitRate, const std::vector<b2ParticleColor>& colors,
    const float32 colorCycleTime) :
  m_startingVelocity(startingVelocity),
  m_origin(origin),
  m_size(size),
  m_emitRate(emitRate),
  m_world(world),
  m_currentColorIndex(0),
  m_colorCycleTime(colorCycleTime),
  m_colorTime(0.0f),
  m_counter(0),
  m_isEmitting(false)
{
  m_colors = colors;
}

// dt is seconds that have passed, flags are the particle flags that you want set on each particle
void FaucetEmitter::Step(float32 dt, uint32 flags) {

  if(!m_isEmitting) {
    return;
  }

  // How many (fractional) particles should we have emitted this frame?
  m_counter += m_emitRate * dt;
  m_colorTime += dt;

  // Update the color cycler.
  int colorCycles = static_cast<int>(m_colorTime / m_colorCycleTime);
  m_colorTime -= static_cast<float>(colorCycles) * m_colorCycleTime;
  m_currentColorIndex = (m_currentColorIndex + colorCycles) %
	m_colors.size();

  b2ParticleDef pd;
  pd.color = m_colors[m_currentColorIndex];

  b2ParticleSystemDef particleSystemDef;
  particleSystemDef.dampingStrength = 0.2f;
  particleSystemDef.radius = 0.3f;
  m_particleSystem = m_world->CreateParticleSystem(&particleSystemDef);

  // Keep emitting particles on this frame until we only have a fractional
  // particle left
  while(m_counter > 1) {
    m_counter -= 1;

    // Randomly pick a position along the line that is the faucet.
    pd.position.Set(m_origin.x + (rand() % 100)/100.0f * m_size - m_size/2,
					m_origin.y);
    // Send it flying
    pd.velocity = m_startingVelocity;
    pd.flags = flags;

    m_particleSystem->CreateParticle(pd);
  }
}

void FaucetEmitter::SetIsEmitting(bool val) {
  m_isEmitting = val;
}
