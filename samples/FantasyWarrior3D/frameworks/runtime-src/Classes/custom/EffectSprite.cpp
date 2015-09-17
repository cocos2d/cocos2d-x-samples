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

#include "EffectSprite.h"
#include <algorithm>
#include <tuple>
// Outline
static int tuple_sort( const std::tuple<ssize_t,Effect*,QuadCommand> &tuple1, const std::tuple<ssize_t,Effect*,QuadCommand> &tuple2 )
{
    return std::get<0>(tuple1) < std::get<0>(tuple2);
}
Effect::Effect()
: _glprogramstate(nullptr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _backgroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                      [this](EventCustom*)
                                                      {
                                                          auto glProgram = _glprogramstate->getGLProgram();
                                                          glProgram->reset();
                                                          glProgram->initWithByteArrays(ccPositionTextureColor_noMVP_vert, _fragSource.c_str());
                                                          glProgram->link();
                                                          glProgram->updateUniforms();
                                                      }
                                                      );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backgroundListener, -1);
#endif
}

Effect::~Effect()
{
    CC_SAFE_RELEASE_NULL(_glprogramstate);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backgroundListener);
#endif
}
bool Effect::initGLProgramState(const std::string &fragmentFilename)
{
    auto fileUtiles = FileUtils::getInstance();
    auto fragmentFullPath = fileUtiles->fullPathForFilename(fragmentFilename);
    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _fragSource = fragSource;
#endif
    
    _glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
    _glprogramstate->retain();

    return _glprogramstate != nullptr;
}
bool EffectNormalMapped::init()
{
    initGLProgramState("mainmenuscene/example_normal.fsh");
    _kBump = 2;
    return true;
}
bool EffectNormalMapped::initNormalMap(const std::string&normalMapFileName)
{
    auto normalMapTextrue = TextureCache::getInstance()->addImage(normalMapFileName.c_str());
    getGLProgramState()->setUniformTexture("u_normalMap", normalMapTextrue); 
    return true;
}
void EffectNormalMapped::setTarget(EffectSprite* sprite)
{
    _sprite = sprite;
    getGLProgramState()->setUniformFloat("u_kBump", _kBump);
    getGLProgramState()->setUniformVec2("u_contentSize", Vec2(sprite->getContentSize().width,sprite->getContentSize().height)); 
}
void EffectNormalMapped::updateUniforms()
{
    if(_pointLight && _sprite)
    {
        Size winSize=Director::getInstance()->getWinSize();
        getGLProgramState()->setUniformFloat("u_kBump", _kBump);
        Mat4 mat= _pointLight->getNodeToWorldTransform();
        Point lightPosInLocalSpace=PointApplyAffineTransform(Vec2(mat.m[12], mat.m[13]),_sprite->parentToNodeTransform());
        getGLProgramState()->setUniformVec4("u_lightPosInLocalSpace", Vec4(lightPosInLocalSpace.x,lightPosInLocalSpace.y,mat.m[14],1));
        const Color3B &col = _pointLight->getDisplayedColor();
        getGLProgramState()->setUniformVec3("u_diffuseL", Vec3(col.r/255.0f,col.g/255.0f,col.b/255.0f));
    }
}
void EffectSprite::addEffect(Effect *effect, ssize_t order)
{
    effect->retain();
    effect->setTarget(this);
    _effects.push_back(std::make_tuple(order,effect,QuadCommand()));
    std::sort(std::begin(_effects), std::end(_effects), tuple_sort);
}
void EffectSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    // Don't do calculate the culling if the transform was not updated
    _insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
    if(_defaultEffect)
    {
        _defaultEffect->updateUniforms();
    }
    if(_insideBounds)
    {
        // negative effects: order < 0
        int idx=0;
        for(auto &effect : _effects) {


            if(std::get<0>(effect) >=0)
                break;
            std::get<1>(effect)->updateUniforms();
            QuadCommand &q = std::get<2>(effect);
            q.init(_globalZOrder, _texture->getName(), std::get<1>(effect)->getGLProgramState(), _blendFunc, &_quad, 1, transform, flags);
            renderer->addCommand(&q);
            idx++;

        }
        // normal effect: order == 0
        _trianglesCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, _polyInfo.triangles, transform, flags);
        renderer->addCommand(&_trianglesCommand);

        // postive effects: oder >= 0
        for(auto it = std::begin(_effects)+idx; it != std::end(_effects); ++it) {
            QuadCommand &q = std::get<2>(*it);
            q.init(_globalZOrder, _texture->getName(), std::get<1>(*it)->getGLProgramState(), _blendFunc, &_quad, 1, transform, flags);
            renderer->addCommand(&q);
            idx++;
        }
    }
}
void EffectSprite::setEffect(Effect* effect)
{
    if(_defaultEffect != effect) {
        effect->setTarget(this);
        CC_SAFE_RETAIN(effect);
        CC_SAFE_RELEASE(_defaultEffect);
        _defaultEffect = effect;
        CC_SAFE_RETAIN(_defaultEffect);
        setGLProgramState(_defaultEffect->getGLProgramState());
    }
}