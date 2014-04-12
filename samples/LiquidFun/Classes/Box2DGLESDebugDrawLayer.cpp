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
#include "Box2DGLESDebugDrawLayer.h"
#include "GLES-Render.h"

using namespace cocos2d;

Box2DGLESDebugDrawLayer* Box2DGLESDebugDrawLayer::create(b2World* const world,
                                           const float scale)
{
  Box2DGLESDebugDrawLayer *pRet = new Box2DGLESDebugDrawLayer(world, scale);
  if (pRet && pRet->init())
  {
    pRet->autorelease();
    return pRet;
  }
  else
  {
    delete pRet;
    pRet = NULL;
    return NULL;
  }
}

Box2DGLESDebugDrawLayer::Box2DGLESDebugDrawLayer(b2World * const world,
                                                 const float scale) :
    m_world(world), m_scale(scale) { }

bool Box2DGLESDebugDrawLayer::init() {
  if (!CCLayer::init()) return false;

  // Use OpenGL to scale the scene in draw() instead of scaling vertices in
  // GLESDebugDraw.
  m_debugDraw = new GLESDebugDraw();
  // Attach the debug draw object to the world.
  m_world->SetDebugDraw(m_debugDraw);

  // Enable rendering of all physics world components.
  uint32 flags = 0;
  flags |= b2Draw::e_shapeBit;
  flags |= b2Draw::e_jointBit;
  flags |= b2Draw::e_aabbBit;
  flags |= b2Draw::e_pairBit;
  flags |= b2Draw::e_centerOfMassBit;
  m_debugDraw->SetFlags(flags);

  return true;
}


void Box2DGLESDebugDrawLayer::draw(cocos2d::Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
    kmGLPushMatrix();
    kmGLScalef(m_scale, m_scale, 1);
    m_world->DrawDebugData();
    kmGLPopMatrix();
}
