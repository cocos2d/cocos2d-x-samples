/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#include "EffectSprite3D.h"
#include "3d/CCAnimation3D.h"
#include "3d/CCAnimate3D.h"
#include "2d/CCCamera.h"
#include <algorithm>

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

void Effect3D::applyRenderState()
{
    _isCullEnabled = glIsEnabled(GL_CULL_FACE);
    _isDepthEnabled = glIsEnabled(GL_DEPTH_TEST);
}

void Effect3D::restoreRenderState()
{
    if (_isCullEnabled)
    {
        glEnable(GL_CULL_FACE);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }
    
    if (_isDepthEnabled)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
}

static int tuple_sort( const std::tuple<ssize_t,Effect3D*,CustomCommand> &tuple1, const std::tuple<ssize_t,Effect3D*,CustomCommand> &tuple2 )
{
    return std::get<0>(tuple1) < std::get<0>(tuple2);
}

EffectSprite3D* EffectSprite3D::create(const std::string &modelPath)
{
    if (modelPath.length() < 4)
        CCASSERT(false, "improper name specified when creating Sprite3D");
    
    auto sprite = new EffectSprite3D();
    if (sprite && sprite->initWithFile(modelPath))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

EffectSprite3D* EffectSprite3D::createFromObjFileAndTexture(const std::string &objFilePath, const std::string &textureFilePath)
{
    auto sprite = new EffectSprite3D();
    if (sprite && sprite->initWithFile(objFilePath))
    {
        sprite->autorelease();
        if(textureFilePath.size() > 0)
            sprite->setTexture(textureFilePath);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

EffectSprite3D::EffectSprite3D()
: _defaultEffect(nullptr)
{
    
}

EffectSprite3D::~EffectSprite3D()
{
    for(auto effect : _effects)
    {
        CC_SAFE_RELEASE_NULL(std::get<1>(effect));
    }
    _effects.clear();
    CC_SAFE_RELEASE(_defaultEffect);
}

void EffectSprite3D::setEffect3D(Effect3D *effect)
{
    if(_defaultEffect == effect) return;
    CC_SAFE_RETAIN(effect);
    CC_SAFE_RELEASE(_defaultEffect);
    _defaultEffect = effect;
}

void EffectSprite3D::addEffect(const Vec3& outlineColor, float width, ssize_t order)
{
    if(this->_meshes.size()>0)
    {
        for(auto &mesh : _meshes)
        {
            Effect3DOutline* effect = Effect3DOutline::create();
            effect->retain();
            effect->setTarget(this,mesh);
            effect->setOutlineColor(outlineColor);
            effect->setOutlineWidth(width);
            
            _effects.push_back(std::make_tuple(order,effect,CustomCommand()));
            std::sort(std::begin(_effects), std::end(_effects), tuple_sort);
        }
    }
    addChildEffect(outlineColor,width,order);
}
void EffectSprite3D::addChildEffect(const Vec3& outlineColor, float width,ssize_t order)
{
    auto& children = this->getChildren();
    for(const auto &obj : children)
    {
        Sprite3D * sprite3D = dynamic_cast<Sprite3D *>(obj);
        if(sprite3D && sprite3D->getMesh())
        {
            Effect3DOutline* effect = Effect3DOutline::create();
            effect->setOutlineColor(outlineColor);
            effect->setOutlineWidth(width);
            effect->retain();
            effect->setTarget(sprite3D,sprite3D->getMesh());
            _effects.push_back(std::make_tuple(order,effect,CustomCommand()));
            std::sort(std::begin(_effects), std::end(_effects), tuple_sort);
        }
    }
}
const std::string Effect3DOutline::_vertShaderFile = "shader3D/OutLine.vert";
const std::string Effect3DOutline::_fragShaderFile = "shader3D/OutLine.frag";
const std::string Effect3DOutline::_keyInGLProgramCache = "Effect3DLibrary_Outline";
const std::string Effect3DOutline::_vertSkinnedShaderFile = "shader3D/SkinnedOutline.vert";
const std::string Effect3DOutline::_fragSkinnedShaderFile = "shader3D/OutLine.frag";
const std::string Effect3DOutline::_keySkinnedInGLProgramCache = "Effect3DLibrary_Outline";

GLProgram* Effect3DOutline::getOrCreateProgram(bool isSkinned /* = false */ )
{
    GLProgram *program = NULL;
    
    if(isSkinned)
    {
        program = GLProgramCache::getInstance()->getGLProgram(_keySkinnedInGLProgramCache);
        if(program == nullptr)
        {
            program = GLProgram::createWithFilenames(_vertSkinnedShaderFile, _fragSkinnedShaderFile);
            GLProgramCache::getInstance()->addGLProgram(program, _keySkinnedInGLProgramCache);
        }
    }
    else
    {
        program = GLProgramCache::getInstance()->getGLProgram(_keyInGLProgramCache);
        if(program == nullptr)
        {
            program = GLProgram::createWithFilenames(_vertShaderFile, _fragShaderFile);
            GLProgramCache::getInstance()->addGLProgram(program, _keyInGLProgramCache);
        }
    }
    
    return program;
}

Effect3DOutline* Effect3DOutline::create()
{
    Effect3DOutline* effect = new Effect3DOutline();
    if(effect && effect->init())
    {
        effect->autorelease();
        return effect;
    }
    else
    {
        CC_SAFE_DELETE(effect);
        return nullptr;
    }
}

bool Effect3DOutline::init()
{
    return true;
}

Effect3DOutline::Effect3DOutline()
: _outlineWidth(1.0f)
, _outlineColor(1, 1, 1)
, _sprite(nullptr)
,_childMesh(nullptr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                            [this](EventCustom*)
                                                            {
                                                                auto glProgram = _glProgramState->getGLProgram();
                                                                glProgram->reset();
                                                                glProgram->initWithFilenames(_vertShaderFile, _fragShaderFile);
                                                                glProgram->link();
                                                                glProgram->updateUniforms();
                                                            }
                                                            );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

Effect3DOutline::~Effect3DOutline()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

void Effect3DOutline::setOutlineColor(const Vec3& color)
{
    if(_outlineColor != color)
    {
        _outlineColor = color;
        if(_glProgramState)
            _glProgramState->setUniformVec3("OutLineColor", _outlineColor);
    }
}

void Effect3DOutline::setOutlineWidth(float width)
{
    if(_outlineWidth != width)
    {
        _outlineWidth = width;
        if(_glProgramState)
            _glProgramState->setUniformFloat("OutlineWidth", _outlineWidth);
    }
}

void Effect3DOutline::setTarget(Sprite3D *sprite,Mesh* childMesh)
{
    CCASSERT(nullptr != sprite && nullptr != childMesh,"Error: Setting a null pointer or a null mesh EffectSprite3D to Effect3D");
    
    if(sprite != _sprite)
    {
        bool isSkinned =false;
        if(childMesh->getSkin())
        {
            isSkinned=true;
        }
        GLProgram* glprogram=Effect3DOutline::getOrCreateProgram(isSkinned);
        CCASSERT(nullptr != glprogram ,"Error: Setting a null pointer or a null glprogram EffectSprite3D to Effect3D");
        _glProgramState = GLProgramState::create(glprogram);
        
        _glProgramState->retain();
        _glProgramState->setUniformVec3("OutLineColor", _outlineColor);
        _glProgramState->setUniformFloat("OutlineWidth", _outlineWidth);
        
        
        _sprite   =  sprite;
        _childMesh = childMesh;
        long offset = 0;
        for (auto i = 0; i < childMesh->getMeshVertexAttribCount(); i++)
        {
            auto meshvertexattrib = childMesh->getMeshVertexAttribute(i);
            
            _glProgramState->setVertexAttribPointer(s_attributeNames[meshvertexattrib.vertexAttrib],
                                                    meshvertexattrib.size,
                                                    meshvertexattrib.type,
                                                    GL_FALSE,
                                                    childMesh->getVertexSizeInBytes(),
                                                    (void*)offset);
            offset += meshvertexattrib.attribSizeBytes;
        }
        
        Color4F color(_sprite->getDisplayedColor());
        color.a = _sprite->getDisplayedOpacity() / 255.0f;
        _glProgramState->setUniformVec4("u_color", Vec4(color.r, color.g, color.b, color.a));
    }
}

static void MatrixPalleteCallBack( GLProgram* glProgram, Uniform* uniform, int paletteSize, const float* palette)
{
    glUniform4fv( uniform->location, (GLsizei)paletteSize, (const float*)palette );
}

void Effect3DOutline::draw(const Mat4 &transform)
{
    
    if(_sprite && _childMesh && _glProgramState && _childMesh->isVisible())
    {
        Color4F color(_sprite->getDisplayedColor());
        color.a = _sprite->getDisplayedOpacity() / 255.0f;
        _glProgramState->setUniformVec4("u_color", Vec4(color.r, color.g, color.b, color.a));
        
        applyRenderState();
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glEnable(GL_DEPTH_TEST);
        // auto mesh = _childMesh;
        glBindBuffer(GL_ARRAY_BUFFER, _childMesh->getVertexBuffer());
        
        auto skin = _childMesh->getSkin();
        if(_sprite && skin)
        {
            auto function = std::bind(MatrixPalleteCallBack, std::placeholders::_1, std::placeholders::_2,
                                      skin->getMatrixPaletteSize(), (float*)skin->getMatrixPalette());
            _glProgramState->setUniformCallback("u_matrixPalette", function);
        }
        
        if(_sprite)
            _glProgramState->apply(transform);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _childMesh->getIndexBuffer());
        glDrawElements(_childMesh->getPrimitiveType(), _childMesh->getIndexCount(), _childMesh->getIndexFormat(), 0);
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _childMesh->getIndexCount());
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        

        glDisable(GL_DEPTH_TEST);
        glCullFace(GL_BACK);
        //glDisable(GL_CULL_FACE);
        restoreRenderState();
    }
}

void EffectSprite3D::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    _groupCmd.init(_globalZOrder);
    _groupCmd.set3D(true);
    _groupCmd.setTransparent(false);
    renderer->addCommand(&_groupCmd);
    renderer->pushGroup(_groupCmd.getRenderQueueID());
    
    if(!_defaultEffect)
    {
        Sprite3D::draw(renderer, transform, flags);
    }
    else
    {
        _command.init(_globalZOrder, transform, flags);
        _command.func = CC_CALLBACK_0(Effect3D::draw, _defaultEffect, transform);
        renderer->addCommand(&_command);
    }
    for(auto &effect : _effects)
    {
        if(std::get<0>(effect) >=0)
            break;
        CustomCommand &cc = std::get<2>(effect);
        cc.init(_globalZOrder, transform, flags);
        cc.setTransparent(true);
        cc.func = CC_CALLBACK_0(Effect3D::draw,std::get<1>(effect),transform);
        
        renderer->addCommand(&cc);
        
    }
    renderer->popGroup();
}
