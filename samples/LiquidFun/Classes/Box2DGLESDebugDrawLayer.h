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

#ifndef B2_DEBUG_DRAW_LAYER_H
#define B2_DEBUG_DRAW_LAYER_H

#include "cocos2d.h"
#include <Box2D/Box2D.h>

class GLESDebugDraw;

class Box2DGLESDebugDrawLayer : public cocos2d::Layer
{
public:
    Box2DGLESDebugDrawLayer(b2World* const world, const float scale);
    static Box2DGLESDebugDrawLayer* create(b2World* const world,
                                         const float scale);
    GLESDebugDraw* GetGLESDebugDraw() const { return m_debugDraw; }

    virtual bool init();
    virtual void draw(cocos2d::Renderer *renderer, const kmMat4& transform, bool transformUpdated) override;

protected:
    b2World* m_world;
    GLESDebugDraw* m_debugDraw;
    const float m_scale;
};

#endif // __B2_DEBUG_DRAW_LAYER_H__
