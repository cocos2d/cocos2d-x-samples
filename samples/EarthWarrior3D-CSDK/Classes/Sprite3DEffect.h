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

#ifndef __Moon3d__Sprite3DEffect__
#define __Moon3d__Sprite3DEffect__

#include <iostream>

#include "cocos2d.h"

USING_NS_CC;

class EffectSprite3D;

class Effect3D : public Ref
{
public:
    virtual void drawWithSprite(EffectSprite3D* sprite, const Mat4 &transform) = 0;
protected:
    Effect3D() : _glProgramState(nullptr) {}
    virtual ~Effect3D()
    {
        CC_SAFE_RELEASE(_glProgramState);
    }
protected:
    GLProgramState* _glProgramState;
};

class Effect3DOutline: public Effect3D
{
public:
    static Effect3DOutline* create();
    
    void setOutlineColor(const Vec3& color);
    
    void setOutlineWidth(float width);
    
    void drawWithSprite(EffectSprite3D* sprite, const Mat4 &transform);
    
protected:
    
    Effect3DOutline();
    virtual ~Effect3DOutline();
    
    bool init();
    
    Vec3 _outlineColor;
    float _outlineWidth;
public:
    static const std::string _vertShaderFile;
    static const std::string _fragShaderFile;
    static const std::string _keyInGLProgramCache;
    static GLProgram* getOrCreateProgram();
    
};

class EffectSprite3D : public Sprite3D
{
public:
    static EffectSprite3D* createFromObjFileAndTexture(const std::string& objFilePath, const std::string& textureFilePath);
//	static EffectSprite3D* createFromC3bFileAndTexture(const std::string& objFilePath, const std::string& textureFilePath);
    void setEffect3D(Effect3D* effect);
    void addEffect(Effect3D* effect, ssize_t order);
    void eraseEffect(Effect3D* effect);
    ssize_t getEffectCount() const;
    Effect3D* getEffect(ssize_t index) const;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
protected:
    EffectSprite3D();
    virtual ~EffectSprite3D();
    
    std::vector<std::tuple<ssize_t,Effect3D*,CustomCommand>> _effects;
    Effect3D* _defaultEffect;
    CustomCommand _command;
};

#endif /* defined(__Moon3d__Sprite3DEffect__) */
