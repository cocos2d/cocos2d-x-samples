#include "BillboardParticleSystem.h"
#include "2d/CCParticleBatchNode.h"
#include "renderer/CCTextureAtlas.h"
#include "platform/CCFileUtils.h"
#include "platform/CCImage.h"
#include "base/ccTypes.h"
#include "base/base64.h"
#include "base/ZipUtils.h"
#include "base/CCDirector.h"
#include "base/CCProfiling.h"
#include "renderer/CCTextureCache.h"
#include "platform/CCGL.h"
USING_NS_CC;
BillboardParticleSystem * BillboardParticleSystem::create(const std::string& filename)
{
    BillboardParticleSystem *ret = new (std::nothrow) BillboardParticleSystem();
    if (ret && ret->initWithFile(filename))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}

BillboardParticleSystem * BillboardParticleSystem::create(ValueMap &dictionary)
{
    BillboardParticleSystem *ret = new (std::nothrow) BillboardParticleSystem();
    if (ret && ret->initWithDictionary(dictionary))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}

BillboardParticleSystem::BillboardParticleSystem():
_isBlendAdditive(false)
, _isAutoRemoveOnFinish(false)
, _plistFile("")
, _elapsed(0)
, _particles(nullptr)
, _configName("")
, _emitCounter(0)
, _particleIdx(0)
, _atlasIndex(0)
, _transformSystemDirty(false)
, _allocatedParticles(0)
, _isActive(true)
, _particleCount(0)
, _duration(0)
, _sourcePosition(Vec2::ZERO)
, _posVar(Vec2::ZERO)
, _life(0)
, _lifeVar(0)
, _angle(0)
, _angleVar(0)
, _emitterMode(Mode::GRAVITY)
, _startSize(0)
, _startSizeVar(0)
, _endSize(0)
, _endSizeVar(0)
, _startSpin(0)
, _startSpinVar(0)
, _endSpin(0)
, _endSpinVar(0)
, _emissionRate(0)
, _totalParticles(0)
, _texture(nullptr)
, _blendFunc(BlendFunc::ALPHA_PREMULTIPLIED)
, _opacityModifyRGB(false)
, _yCoordFlipped(1)
, _positionType(PositionType::FREE)
, _camera(nullptr)
,_cameraUp(0,1,0)
,_cameraRight(1,0,0)
,_quads(nullptr)
,_indices(nullptr)
,_VAOname(0)
{
    _depthTestEnabled=false;
    modeA.gravity = Vec2::ZERO;
    modeA.speed = 0;
    modeA.speedVar = 0;
    modeA.tangentialAccel = 0;
    modeA.tangentialAccelVar = 0;
    modeA.radialAccel = 0;
    modeA.radialAccelVar = 0;
    modeA.rotationIsDir = false;
    modeB.startRadius = 0;
    modeB.startRadiusVar = 0;
    modeB.endRadius = 0;
    modeB.endRadiusVar = 0;
    modeB.rotatePerSecond = 0;
    modeB.rotatePerSecondVar = 0;
    memset(_buffersVBO, 0, sizeof(_buffersVBO));
}
BillboardParticleSystem::~BillboardParticleSystem()
{
    CC_SAFE_FREE(_particles);
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_FREE(_quads);
    CC_SAFE_FREE(_indices);
    glDeleteBuffers(2, &_buffersVBO[0]);
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glDeleteVertexArrays(1, &_VAOname);
        GL::bindVAO(0);
    }
}

void BillboardParticleSystem::updateQuadWithParticle(sBillboardParticle* particle, const Vec3& newPosition)
{
    V3F_C4B_T2F_Quad *quad;
    quad = &(_quads[_particleIdx]);
    Color4B color = (_opacityModifyRGB)
    ? Color4B( particle->color.r*particle->color.a*255, particle->color.g*particle->color.a*255, particle->color.b*particle->color.a*255, particle->color.a*255)
    : Color4B( particle->color.r*255, particle->color.g*255, particle->color.b*255, particle->color.a*255);
    
    quad->bl.colors = color;
    quad->br.colors = color;
    quad->tl.colors = color;
    quad->tr.colors = color;
    Vec3  billboardX = _cameraRight.getNormalized();
    Vec3  billboardY = _cameraUp.getNormalized();
    float fLeft   = -0.5f;
    float fRight  =  0.5f;
    float fTop    =  0.5f;
    float fBottom = -0.5f;
    Vec3  leftOff   = billboardX * particle->size * fLeft;
    Vec3  rightOff  = billboardX * particle->size * fRight;
    Vec3  topOff    = billboardY * particle->size * fTop;
    Vec3  bottomOff = billboardY * particle->size * fBottom;
    Vec3 vOffset[4];
    vOffset[0] = leftOff + bottomOff;
    vOffset[1] = rightOff + bottomOff;
    vOffset[2] = leftOff + topOff;
    vOffset[3] = rightOff + topOff;
    if (particle->rotation)
    {
        Vec3 axis=vOffset[3] - vOffset[0];
        axis.cross((vOffset[2] - vOffset[1]));
        Mat4 rotMat;
        Mat4::createRotation(axis, CC_DEGREES_TO_RADIANS(particle->rotation), &rotMat);
        rotMat.transformVector(&vOffset[0]);
        rotMat.transformVector(&vOffset[1]);
        rotMat.transformVector(&vOffset[2]);
        rotMat.transformVector(&vOffset[3]);
    }
    quad->bl.vertices = newPosition + vOffset[0];
    
    // bottom-right vertex:
    quad->br.vertices = newPosition + vOffset[1];
    
    // top-left vertex:
    quad->tl.vertices= newPosition + vOffset[2];
    // top-right vertex:
    quad->tr.vertices = newPosition + vOffset[3];
}
void BillboardParticleSystem::setCamera(Camera* camera)
{
    _camera = camera;
}
void BillboardParticleSystem::update(float dt)
{
    if(_camera)
    {
        const Mat4& cameraViewMatrix = _camera->getViewMatrix().getInversed();
        cameraViewMatrix.getRightVector(&_cameraRight);
        cameraViewMatrix.getUpVector(&_cameraUp);
    }
    const Mat4& WorldMat = getNodeToWorldTransform();
    Quaternion rotation;;
    WorldMat.getRotation(&rotation);
    Mat4 roaMat;
    Mat4::createRotation(rotation,&roaMat);
    
    CC_PROFILER_START_CATEGORY(kProfilerCategoryParticles , "CCParticleSystem - update");
    if (_isActive && _emissionRate)
    {
        float rate = 1.0f / _emissionRate;
        //issue #1201, prevent bursts of particles, due to too high emitCounter
        if (_particleCount < _totalParticles)
        {
            _emitCounter += dt;
        }
        
        while (_particleCount < _totalParticles && _emitCounter > rate)
        {
            this->addParticle();
            _emitCounter -= rate;
        }
        
        _elapsed += dt;
        if (_duration != -1 && _duration < _elapsed)
        {
            this->stopSystem();
        }
    }
    
    _particleIdx = 0;
    
    Vec3 currentPosition = Vec3::ZERO;
    if (_positionType == PositionType::FREE)
    {
        currentPosition = this->convertToWorldSpace3D(Vec3::ZERO);
    }
    else if (_positionType == PositionType::RELATIVE)
    {
        currentPosition.x = _position.x;
        currentPosition.y = _position.y;
        currentPosition.z = _positionZ;
    }
    
    {
        while (_particleIdx < _particleCount)
        {
            sBillboardParticle *p = &_particles[_particleIdx];
            
            // life
            p->timeToLive -= dt;
            
            if (p->timeToLive > 0)
            {
                // Mode A: gravity, direction, tangential accel & radial accel
                if (_emitterMode == Mode::GRAVITY)
                {
                    Vec2 tmp, radial, tangential;
                    
                    radial = Vec2::ZERO;
                    // radial acceleration
                    if (p->pos.x || p->pos.y)
                    {
                        radial = p->pos.getNormalized();
                    }
                    tangential = radial;
                    radial = radial * p->modeA.radialAccel;
                    
                    // tangential acceleration
                    float newy = tangential.x;
                    tangential.x = -tangential.y;
                    tangential.y = newy;
                    tangential = tangential * p->modeA.tangentialAccel;
                    
                    // (gravity + radial + tangential) * dt
                    tmp = radial + tangential + modeA.gravity;
                    tmp = tmp * dt;
                    p->modeA.dir = p->modeA.dir + tmp;
                    
                    // this is cocos2d-x v3.0
                    //                    if (_configName.length()>0 && _yCoordFlipped != -1)
                    
                    // this is cocos2d-x v3.0
                    tmp = p->modeA.dir * dt * _yCoordFlipped;
                    p->pos = p->pos + tmp;
                }
                
                // Mode B: radius movement
                else
                {
                    // Update the angle and radius of the particle.
                    p->modeB.angle += p->modeB.degreesPerSecond * dt;
                    p->modeB.radius += p->modeB.deltaRadius * dt;
                    
                    p->pos.x = - cosf(p->modeB.angle) * p->modeB.radius;
                    p->pos.y = - sinf(p->modeB.angle) * p->modeB.radius;
                    p->pos.y *= _yCoordFlipped;
                }
                
                // color
                p->color.r += (p->deltaColor.r * dt);
                p->color.g += (p->deltaColor.g * dt);
                p->color.b += (p->deltaColor.b * dt);
                p->color.a += (p->deltaColor.a * dt);
                
                // size
                p->size += (p->deltaSize * dt);
                p->size = MAX( 0, p->size );
                
                // angle
                p->rotation += (p->deltaRotation * dt);
                
                //
                // update values in quad
                //
                
                Vec3    newPos;
                Vec3 parPos(p->pos.x,p->pos.y,0);
                roaMat.transformVector(&parPos);
                if (_positionType == PositionType::FREE)
                {
                    Vec3 diff = convertToNodeSpace3D(currentPosition) - convertToNodeSpace3D(p->startPos);
                    //newPos.x =  p->pos.x - diff.x;
                    //newPos.y =  p->pos.y - diff.y;
                    //newPos.z = - diff.z;
                    newPos = parPos-diff;
                }
                else if(_positionType == PositionType::RELATIVE)
                {
                    Vec3 diff = currentPosition - p->startPos;
                    newPos.x = p->pos.x - diff.x;
                    newPos.y =  p->pos.y - diff.y;
                    newPos.z = - diff.z;
                }
                else
                {
                    newPos.x = p->pos.x;
                    newPos.y = p->pos.y;
                    newPos.z = 0;
                }
                
                updateQuadWithParticle(p, newPos);
                //updateParticleImp(self, updateParticleSel, p, newPos);
                
                // update particle counter
                ++_particleIdx;
            }
            else
            {
                // life < 0
//                int currentIndex = p->atlasIndex;
                if( _particleIdx != _particleCount-1 )
                {
                    _particles[_particleIdx] = _particles[_particleCount-1];
                }
                --_particleCount;
                
                if( _particleCount == 0 && _isAutoRemoveOnFinish )
                {
                    this->unscheduleUpdate();
                    _parent->removeChild(this, true);
                    return;
                }
            }
        } //while
        _transformSystemDirty = false;
    }
    
    // only update gl buffer when visible
    if (_visible)
    {
        // postStep();
    }
    
    CC_PROFILER_STOP_CATEGORY(kProfilerCategoryParticles , "BillboardParticleSystem - update");
}
void BillboardParticleSystem::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    begin();
    Vec3 scale;
    transform.getScale(&scale);
    Mat4 billboardTransform;
    billboardTransform.translate(transform.m[12],transform.m[13],transform.m[14]);
    billboardTransform.scale(scale);
    CCASSERT( _particleIdx == 0 || _particleIdx == _particleCount, "Abnormal error in particle quad");
    
    flags |= FLAGS_RENDER_AS_3D;
    
    //quad command
    if(_particleIdx > 0)
    {
        _quadCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, _quads, _particleIdx, transform, flags);
        renderer->addCommand(&_quadCommand);
    }
    end();
}
void BillboardParticleSystem::begin()
{
    
    _beginCommand.init(_globalZOrder);
    _beginCommand.func = CC_CALLBACK_0(BillboardParticleSystem::onBegin, this);
    Director::getInstance()->getRenderer()->addCommand(&_beginCommand);
}
void BillboardParticleSystem::end()
{
    _endCommand.init(_globalZOrder);
    _endCommand.func = CC_CALLBACK_0(BillboardParticleSystem::onEnd, this);
    
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    Renderer *renderer = director->getRenderer();
    renderer->addCommand(&_endCommand);
    
}
void BillboardParticleSystem::onBegin()
{
    if (_depthTestEnabled)
    {
        //glEnable(GL_DEPTH_TEST);
        glDepthMask(false);
    }
}
void BillboardParticleSystem::onEnd()
{
    if (_depthTestEnabled)
    {
        //glDisable(GL_DEPTH_TEST);
        glDepthMask(true);
    }
}
void BillboardParticleSystem::setDepthTestEnabled(bool enable)
{
    _depthTestEnabled = enable;
}
bool BillboardParticleSystem::initWithFile(const std::string& plistFile)
{
    bool ret = false;
    _plistFile = FileUtils::getInstance()->fullPathForFilename(plistFile);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(_plistFile.c_str());
    
    CCASSERT( !dict.empty(), "Particles: file not found");
    
    // XXX compute path from a path, should define a function somewhere to do it
    string listFilePath = plistFile;

    ret = this->initWithDictionary(dict, "");
    
    return ret;
}

bool BillboardParticleSystem::initWithDictionary(ValueMap& dictionary)
{
    return initWithDictionary(dictionary, "");
}

bool BillboardParticleSystem::initWithDictionary(ValueMap& dictionary, const std::string& dirname)
{
    bool ret = false;
    unsigned char *buffer = nullptr;
    unsigned char *deflated = nullptr;
//    Image *image = nullptr;
    do
    {
        int maxParticles = dictionary["maxParticles"].asInt();
        // self, not super
        if(this->initWithTotalParticles(maxParticles))
        {
            // Emitter name in particle designer 2.0
            _configName = dictionary["configName"].asString();
            
            // angle
            _angle = dictionary["angle"].asFloat();
            _angleVar = dictionary["angleVariance"].asFloat();
            
            // duration
            _duration = dictionary["duration"].asFloat();
            
            // blend function
            if (_configName.length()>0)
            {
                _blendFunc.src = dictionary["blendFuncSource"].asFloat();
            }
            else
            {
                _blendFunc.src = dictionary["blendFuncSource"].asInt();
            }
            _blendFunc.dst = dictionary["blendFuncDestination"].asInt();
            
            // color
            _startColor.r = dictionary["startColorRed"].asFloat();
            _startColor.g = dictionary["startColorGreen"].asFloat();
            _startColor.b = dictionary["startColorBlue"].asFloat();
            _startColor.a = dictionary["startColorAlpha"].asFloat();
            
            _startColorVar.r = dictionary["startColorVarianceRed"].asFloat();
            _startColorVar.g = dictionary["startColorVarianceGreen"].asFloat();
            _startColorVar.b = dictionary["startColorVarianceBlue"].asFloat();
            _startColorVar.a = dictionary["startColorVarianceAlpha"].asFloat();
            
            _endColor.r = dictionary["finishColorRed"].asFloat();
            _endColor.g = dictionary["finishColorGreen"].asFloat();
            _endColor.b = dictionary["finishColorBlue"].asFloat();
            _endColor.a = dictionary["finishColorAlpha"].asFloat();
            
            _endColorVar.r = dictionary["finishColorVarianceRed"].asFloat();
            _endColorVar.g = dictionary["finishColorVarianceGreen"].asFloat();
            _endColorVar.b = dictionary["finishColorVarianceBlue"].asFloat();
            _endColorVar.a = dictionary["finishColorVarianceAlpha"].asFloat();
            
            // particle size
            _startSize = dictionary["startParticleSize"].asFloat();
            _startSizeVar = dictionary["startParticleSizeVariance"].asFloat();
            _endSize = dictionary["finishParticleSize"].asFloat();
            _endSizeVar = dictionary["finishParticleSizeVariance"].asFloat();
            
            // position
            float x = dictionary["sourcePositionx"].asFloat();
            float y = dictionary["sourcePositiony"].asFloat();
            this->setPosition( Vec2(x,y) );
            _posVar.x = dictionary["sourcePositionVariancex"].asFloat();
            _posVar.y = dictionary["sourcePositionVariancey"].asFloat();
            
            // Spinning
            _startSpin = dictionary["rotationStart"].asFloat();
            _startSpinVar = dictionary["rotationStartVariance"].asFloat();
            _endSpin= dictionary["rotationEnd"].asFloat();
            _endSpinVar= dictionary["rotationEndVariance"].asFloat();
            
            _emitterMode = (Mode) dictionary["emitterType"].asInt();
            
            // Mode A: Gravity + tangential accel + radial accel
            if (_emitterMode == Mode::GRAVITY)
            {
                // gravity
                modeA.gravity.x = dictionary["gravityx"].asFloat();
                modeA.gravity.y = dictionary["gravityy"].asFloat();
                
                // speed
                modeA.speed = dictionary["speed"].asFloat();
                modeA.speedVar = dictionary["speedVariance"].asFloat();
                
                // radial acceleration
                modeA.radialAccel = dictionary["radialAcceleration"].asFloat();
                modeA.radialAccelVar = dictionary["radialAccelVariance"].asFloat();
                
                // tangential acceleration
                modeA.tangentialAccel = dictionary["tangentialAcceleration"].asFloat();
                modeA.tangentialAccelVar = dictionary["tangentialAccelVariance"].asFloat();
                
                // rotation is dir
                modeA.rotationIsDir = dictionary["rotationIsDir"].asBool();
            }
            
            // or Mode B: radius movement
            else if (_emitterMode == Mode::RADIUS)
            {
                if (_configName.length()>0)
                {
                    modeB.startRadius = dictionary["maxRadius"].asInt();
                }
                else
                {
                    modeB.startRadius = dictionary["maxRadius"].asFloat();
                }
                modeB.startRadiusVar = dictionary["maxRadiusVariance"].asFloat();
                if (_configName.length()>0)
                {
                    modeB.endRadius = dictionary["minRadius"].asInt();
                }
                else
                {
                    modeB.endRadius = dictionary["minRadius"].asFloat();
                }
                
                if (dictionary.find("minRadiusVariance") != dictionary.end())
                {
                    modeB.endRadiusVar = dictionary["minRadiusVariance"].asFloat();
                }
                else
                {
                    modeB.endRadiusVar = 0.0f;
                }
                
                if (_configName.length()>0)
                {
                    modeB.rotatePerSecond = dictionary["rotatePerSecond"].asInt();
                }
                else
                {
                    modeB.rotatePerSecond = dictionary["rotatePerSecond"].asFloat();
                }
                modeB.rotatePerSecondVar = dictionary["rotatePerSecondVariance"].asFloat();
                
            } else {
                CCASSERT( false, "Invalid emitterType in config file");
                CC_BREAK_IF(true);
            }
            
            // life span
            _life = dictionary["particleLifespan"].asFloat();
            _lifeVar = dictionary["particleLifespanVariance"].asFloat();
            
            // emission Rate
            _emissionRate = _totalParticles / _life;
            
            
            // Set a compatible default for the alpha transfer
            _opacityModifyRGB = false;
            
//            // texture
//            // Try to get the texture from the cache
//            std::string textureName = dictionary["textureFileName"].asString();
//            
//            size_t rPos = textureName.rfind('/');
//            
//            if (rPos != string::npos)
//            {
//                string textureDir = textureName.substr(0, rPos + 1);
//                
//                if (!dirname.empty() && textureDir != dirname)
//                {
//                    textureName = textureName.substr(rPos+1);
//                    textureName = dirname + textureName;
//                }
//            }
//            else if (!dirname.empty() && !textureName.empty())
//            {
//                textureName = dirname + textureName;
//            }
//            
//            Texture2D *tex = nullptr;
//            
//            if (textureName.length() > 0)
//            {
//                // set not pop-up message box when load image failed
//                bool notify = FileUtils::getInstance()->isPopupNotify();
//                FileUtils::getInstance()->setPopupNotify(false);
//                tex = Director::getInstance()->getTextureCache()->addImage(textureName);
//                // reset the value of UIImage notify
//                FileUtils::getInstance()->setPopupNotify(notify);
//            }
//            
//            if (tex)
//            {
//                setTexture(tex);
//            }
//            else if( dictionary.find("textureImageData") != dictionary.end() )
//            {
//                std::string textureData = dictionary.at("textureImageData").asString();
//                CCASSERT(!textureData.empty(), "");
//                
//                auto dataLen = textureData.size();
//                if (dataLen != 0)
//                {
//                    // if it fails, try to get it from the base64-gzipped data
//                    int decodeLen = base64Decode((unsigned char*)textureData.c_str(), (unsigned int)dataLen, &buffer);
//                    CCASSERT( buffer != nullptr, "CCParticleSystem: error decoding textureImageData");
//                    CC_BREAK_IF(!buffer);
//                    
//                    ssize_t deflatedLen = ZipUtils::inflateMemory(buffer, decodeLen, &deflated);
//                    CCASSERT( deflated != nullptr, "CCParticleSystem: error ungzipping textureImageData");
//                    CC_BREAK_IF(!deflated);
//                    
//                    // For android, we should retain it in VolatileTexture::addImage which invoked in Director::getInstance()->getTextureCache()->addUIImage()
//                    image = new (std::nothrow) Image();
//                    bool isOK = image->initWithImageData(deflated, deflatedLen);
//                    CCASSERT(isOK, "CCParticleSystem: error init image with Data");
//                    CC_BREAK_IF(!isOK);
//                    
//                    setTexture(Director::getInstance()->getTextureCache()->addImage(image, textureName.c_str()));
//                    
//                    image->release();
//                }
//            }
            
            _yCoordFlipped = dictionary.find("yCoordFlipped") == dictionary.end() ? 1 : dictionary.at("yCoordFlipped").asInt();
            
//            if( !this->_texture)
//                CCLOGWARN("cocos2d: Warning: ParticleSystemQuad system without a texture");
            ret = true;
        }
    } while (0);
    free(buffer);
    free(deflated);
    return ret;
}
// ParticleSystem - Texture protocol
void BillboardParticleSystem::setTexture(Texture2D* texture)
{
    const Size& s = texture->getContentSize();
    this->setTextureWithRect(texture, Rect(0, 0, s.width, s.height));
}
void BillboardParticleSystem::updateBlendFunc()
{
    
    if(_texture)
    {
        bool premultiplied = _texture->hasPremultipliedAlpha();
        
        _opacityModifyRGB = false;
        
        if( _texture && ( _blendFunc.src == CC_BLEND_SRC && _blendFunc.dst == CC_BLEND_DST ) )
        {
            if( premultiplied )
            {
                _opacityModifyRGB = true;
            }
            else
            {
                _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
            }
        }
    }
}

Texture2D * BillboardParticleSystem::getTexture() const
{
    return _texture;
}

// ParticleSystem - Additive Blending
void BillboardParticleSystem::setBlendAdditive(bool additive)
{
    if( additive )
    {
        _blendFunc = BlendFunc::ADDITIVE;
    }
    else
    {
        if( _texture && ! _texture->hasPremultipliedAlpha() )
            _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
        else
            _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    }
}

bool BillboardParticleSystem::isBlendAdditive() const
{
    return( _blendFunc.src == GL_SRC_ALPHA && _blendFunc.dst == GL_ONE);
}
Vec3 BillboardParticleSystem::convertToNodeSpace3D(const Vec3& worldPoint) const
{
    Mat4 tmp = getWorldToNodeTransform();
    Vec3 vec3(worldPoint.x, worldPoint.y, worldPoint.z);
    Vec3 ret;
    tmp.transformPoint(vec3,&ret);
    return Vec3(ret.x, ret.y,ret.z);
}

Vec3 BillboardParticleSystem::convertToWorldSpace3D(const Vec3& nodePoint) const
{
    Mat4 tmp = getNodeToWorldTransform();
    Vec3 vec3(nodePoint.x, nodePoint.y, nodePoint.z);
    Vec3 ret;
    tmp.transformPoint(vec3,&ret);
    return Vec3(ret.x, ret.y,ret.z);
    
}
bool BillboardParticleSystem::initWithTotalParticles(int numberOfParticles)
{
    _totalParticles = numberOfParticles;
    
    CC_SAFE_FREE(_particles);
    
    _particles = (sBillboardParticle*)calloc(_totalParticles, sizeof(sBillboardParticle));
    
    if( ! _particles )
    {
        CCLOG("Particle system: not enough memory");
        this->release();
        return false;
    }
    _allocatedParticles = numberOfParticles;
    // default, active
    _isActive = true;
    
    // default blend function
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    
    // default movement type;
    _positionType = PositionType::FREE;
    
    // by default be in mode A:
    _emitterMode = Mode::GRAVITY;
    
    // default: modulate
    // XXX: not used
    //    colorModulate = YES;
    
    _isAutoRemoveOnFinish = false;
    
    // Optimization: compile updateParticle method
    //updateParticleSel = @selector(updateQuadWithParticle:newPosition:);
    //updateParticleImp = (CC_UPDATE_PARTICLE_IMP) [self methodForSelector:updateParticleSel];
    //for batchNode
    _transformSystemDirty = false;
    // allocating data space
    if( ! this->allocMemory() ) {
        this->release();
        return false;
    }
    
    initIndices();
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        setupVBOandVAO();
    }
    else
    {
        setupVBO();
    }
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Need to listen the event only when not use batchnode, because it will use VBO
    auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, CC_CALLBACK_1(BillboardParticleSystem::listenRendererRecreated, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
    
    return true;
}
//void BillboardParticleSystem::postStep()
//{
//    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
//
//    // Option 1: Sub Data
//    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_quads[0])*_totalParticles, _quads);
//
//    // Option 2: Data
//    //  glBufferData(GL_ARRAY_BUFFER, sizeof(quads_[0]) * particleCount, quads_, GL_DYNAMIC_DRAW);
//
//    // Option 3: Orphaning + glMapBuffer
//    // glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0])*_totalParticles, nullptr, GL_STREAM_DRAW);
//    // void *buf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
//    // memcpy(buf, _quads, sizeof(_quads[0])*_totalParticles);
//    // glUnmapBuffer(GL_ARRAY_BUFFER);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    CHECK_GL_ERROR_DEBUG();
//}
void BillboardParticleSystem::setTextureWithRect(Texture2D *texture, const Rect& rect)
{
    // Only update the texture if is different from the current one
    if( !_texture || texture->getName() != _texture->getName() )
    {
        if (_texture != texture)
        {
            CC_SAFE_RETAIN(texture);
            CC_SAFE_RELEASE(_texture);
            _texture = texture;
            updateBlendFunc();
        }
    }
    this->initTexCoordsWithRect(rect);
}
// pointRect should be in Texture coordinates, not pixel coordinates
void BillboardParticleSystem::initTexCoordsWithRect(const Rect& pointRect)
{
    // convert to Tex coords
    
    Rect rect = Rect(
                     pointRect.origin.x * CC_CONTENT_SCALE_FACTOR(),
                     pointRect.origin.y * CC_CONTENT_SCALE_FACTOR(),
                     pointRect.size.width * CC_CONTENT_SCALE_FACTOR(),
                     pointRect.size.height * CC_CONTENT_SCALE_FACTOR());
    
    GLfloat wide = (GLfloat) pointRect.size.width;
    GLfloat high = (GLfloat) pointRect.size.height;
    
    if (_texture)
    {
        wide = (GLfloat)_texture->getPixelsWide();
        high = (GLfloat)_texture->getPixelsHigh();
    }
    
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
    GLfloat left = (rect.origin.x*2+1) / (wide*2);
    GLfloat bottom = (rect.origin.y*2+1) / (high*2);
    GLfloat right = left + (rect.size.width*2-2) / (wide*2);
    GLfloat top = bottom + (rect.size.height*2-2) / (high*2);
#else
    GLfloat left = rect.origin.x / wide;
    GLfloat bottom = rect.origin.y / high;
    GLfloat right = left + rect.size.width / wide;
    GLfloat top = bottom + rect.size.height / high;
#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
    
    // Important. Texture in cocos2d are inverted, so the Y component should be inverted
    CC_SWAP( top, bottom, float);
    
    V3F_C4B_T2F_Quad *quads = nullptr;
    unsigned int start = 0, end = 0;
    quads = _quads;
    start = 0;
    end = _totalParticles;
    for(unsigned int i=start; i<end; i++)
    {
        // bottom-left vertex:
        quads[i].bl.texCoords.u = left;
        quads[i].bl.texCoords.v = bottom;
        // bottom-right vertex:
        quads[i].br.texCoords.u = right;
        quads[i].br.texCoords.v = bottom;
        // top-left vertex:
        quads[i].tl.texCoords.u = left;
        quads[i].tl.texCoords.v = top;
        // top-right vertex:
        quads[i].tr.texCoords.u = right;
        quads[i].tr.texCoords.v = top;
    }
}
const BlendFunc& BillboardParticleSystem::getBlendFunc() const
{
    return _blendFunc;
}

void BillboardParticleSystem::setBlendFunc(const BlendFunc &blendFunc)
{
    if( _blendFunc.src != blendFunc.src || _blendFunc.dst != blendFunc.dst ) {
        _blendFunc = blendFunc;
        this->updateBlendFunc();
    }
}
void BillboardParticleSystem::stopSystem()
{
    _isActive = false;
    _elapsed = _duration;
    _emitCounter = 0;
}

void BillboardParticleSystem::resetSystem()
{
    _isActive = true;
    _elapsed = 0;
    for (_particleIdx = 0; _particleIdx < _particleCount; ++_particleIdx)
    {
        sBillboardParticle *p = &_particles[_particleIdx];
        p->timeToLive = 0;
    }
}
bool BillboardParticleSystem::isFull()
{
    return (_particleCount == _totalParticles);
}
void BillboardParticleSystem::initParticle(sBillboardParticle* particle)
{
    // timeToLive
    // no negative life. prevent division by 0
    particle->timeToLive = _life + _lifeVar * CCRANDOM_MINUS1_1();
    particle->timeToLive = MAX(0, particle->timeToLive);
    
    // position
    particle->pos.x = _sourcePosition.x + _posVar.x * CCRANDOM_MINUS1_1();
    
    particle->pos.y = _sourcePosition.y + _posVar.y * CCRANDOM_MINUS1_1();
    
    // Color
    Color4F start;
    start.r = clampf(_startColor.r + _startColorVar.r * CCRANDOM_MINUS1_1(), 0, 1);
    start.g = clampf(_startColor.g + _startColorVar.g * CCRANDOM_MINUS1_1(), 0, 1);
    start.b = clampf(_startColor.b + _startColorVar.b * CCRANDOM_MINUS1_1(), 0, 1);
    start.a = clampf(_startColor.a + _startColorVar.a * CCRANDOM_MINUS1_1(), 0, 1);
    
    Color4F end;
    end.r = clampf(_endColor.r + _endColorVar.r * CCRANDOM_MINUS1_1(), 0, 1);
    end.g = clampf(_endColor.g + _endColorVar.g * CCRANDOM_MINUS1_1(), 0, 1);
    end.b = clampf(_endColor.b + _endColorVar.b * CCRANDOM_MINUS1_1(), 0, 1);
    end.a = clampf(_endColor.a + _endColorVar.a * CCRANDOM_MINUS1_1(), 0, 1);
    
    particle->color = start;
    particle->deltaColor.r = (end.r - start.r) / particle->timeToLive;
    particle->deltaColor.g = (end.g - start.g) / particle->timeToLive;
    particle->deltaColor.b = (end.b - start.b) / particle->timeToLive;
    particle->deltaColor.a = (end.a - start.a) / particle->timeToLive;
    
    // size
    float startS = _startSize + _startSizeVar * CCRANDOM_MINUS1_1();
    startS = MAX(0, startS); // No negative value
    
    particle->size = startS;
    
    if (_endSize == START_SIZE_EQUAL_TO_END_SIZE)
    {
        particle->deltaSize = 0;
    }
    else
    {
        float endS = _endSize + _endSizeVar * CCRANDOM_MINUS1_1();
        endS = MAX(0, endS); // No negative values
        particle->deltaSize = (endS - startS) / particle->timeToLive;
    }
    
    // rotation
    float startA = _startSpin + _startSpinVar * CCRANDOM_MINUS1_1();
    float endA = _endSpin + _endSpinVar * CCRANDOM_MINUS1_1();
    particle->rotation = startA;
    particle->deltaRotation = (endA - startA) / particle->timeToLive;
    
    // position
    if (_positionType == PositionType::FREE)
    {
        particle->startPos = this->convertToWorldSpace3D(Vec3::ZERO);
    }
    else if (_positionType == PositionType::RELATIVE)
    {
        particle->startPos.x = _position.x;
        particle->startPos.y = _position.y;
        particle->startPos.z = _positionZ;
    }
    
    // direction
    float a = CC_DEGREES_TO_RADIANS( _angle + _angleVar * CCRANDOM_MINUS1_1() );
    
    // Mode Gravity: A
    if (_emitterMode == Mode::GRAVITY)
    {
        Vec2 v(cosf( a ), sinf( a ));
        float s = modeA.speed + modeA.speedVar * CCRANDOM_MINUS1_1();
        
        // direction
        particle->modeA.dir = v * s ;
        
        // radial accel
        particle->modeA.radialAccel = modeA.radialAccel + modeA.radialAccelVar * CCRANDOM_MINUS1_1();
        
        
        // tangential accel
        particle->modeA.tangentialAccel = modeA.tangentialAccel + modeA.tangentialAccelVar * CCRANDOM_MINUS1_1();
        
        // rotation is dir
        if(modeA.rotationIsDir)
            particle->rotation = -CC_RADIANS_TO_DEGREES(particle->modeA.dir.getAngle());
    }
    
    // Mode Radius: B
    else
    {
        // Set the default diameter of the particle from the source position
        float startRadius = modeB.startRadius + modeB.startRadiusVar * CCRANDOM_MINUS1_1();
        float endRadius = modeB.endRadius + modeB.endRadiusVar * CCRANDOM_MINUS1_1();
        
        particle->modeB.radius = startRadius;
        
        if (modeB.endRadius == START_RADIUS_EQUAL_TO_END_RADIUS)
        {
            particle->modeB.deltaRadius = 0;
        }
        else
        {
            particle->modeB.deltaRadius = (endRadius - startRadius) / particle->timeToLive;
        }
        
        particle->modeB.angle = a;
        particle->modeB.degreesPerSecond = CC_DEGREES_TO_RADIANS(modeB.rotatePerSecond + modeB.rotatePerSecondVar * CCRANDOM_MINUS1_1());
    }
}
void BillboardParticleSystem::onEnter()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnEnter))
            return;
    }
#endif
    
    Node::onEnter();
    
    // update after action in run!
    this->scheduleUpdateWithPriority(1);
}

void BillboardParticleSystem::onExit()
{
    this->unscheduleUpdate();
    Node::onExit();
}
bool BillboardParticleSystem::addParticle()
{
    if (this->isFull())
    {
        return false;
    }
    
    sBillboardParticle * particle = &_particles[ _particleCount ];
    this->initParticle(particle);
    ++_particleCount;
    
    return true;
}
void BillboardParticleSystem::setupVBOandVAO()
{
    // clean VAO
    glDeleteBuffers(2, &_buffersVBO[0]);
    glDeleteVertexArrays(1, &_VAOname);
    GL::bindVAO(0);
    
    glGenVertexArrays(1, &_VAOname);
    GL::bindVAO(_VAOname);
    
#define kQuadSize sizeof(_quads[0].bl)
    
    glGenBuffers(2, &_buffersVBO[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _totalParticles, _quads, GL_DYNAMIC_DRAW);
    
    // vertices
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof( V3F_C4B_T2F, vertices));
    
    // colors
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof( V3F_C4B_T2F, colors));
    
    // tex coords
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof( V3F_C4B_T2F, texCoords));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _totalParticles * 6, _indices, GL_STATIC_DRAW);
    
    // Must unbind the VAO before changing the element buffer.
    GL::bindVAO(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    CHECK_GL_ERROR_DEBUG();
}

void BillboardParticleSystem::setupVBO()
{
    glDeleteBuffers(2, &_buffersVBO[0]);
    
    glGenBuffers(2, &_buffersVBO[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _totalParticles, _quads, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _totalParticles * 6, _indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    CHECK_GL_ERROR_DEBUG();
}
bool BillboardParticleSystem::allocMemory()
{
    
    
    CC_SAFE_FREE(_quads);
    CC_SAFE_FREE(_indices);
    
    _quads = (V3F_C4B_T2F_Quad*)malloc(_totalParticles * sizeof(V3F_C4B_T2F_Quad));
    _indices = (GLushort*)malloc(_totalParticles * 6 * sizeof(GLushort));
    
    if( !_quads || !_indices)
    {
        CCLOG("cocos2d: Particle system: not enough memory");
        CC_SAFE_FREE(_quads);
        CC_SAFE_FREE(_indices);
        
        return false;
    }
    memset(_quads, 0, _totalParticles * sizeof(V3F_C4B_T2F_Quad));
    memset(_indices, 0, _totalParticles * 6 * sizeof(GLushort));
    return true;
}
void BillboardParticleSystem::initIndices()
{
    for(int i = 0; i < _totalParticles; ++i)
    {
        const unsigned int i6 = i*6;
        const unsigned int i4 = i*4;
        _indices[i6+0] = (GLushort) i4+0;
        _indices[i6+1] = (GLushort) i4+1;
        _indices[i6+2] = (GLushort) i4+2;
        
        _indices[i6+5] = (GLushort) i4+1;
        _indices[i6+4] = (GLushort) i4+2;
        _indices[i6+3] = (GLushort) i4+3;
    }
}
void BillboardParticleSystem::setTotalParticles(int tp)
{
    // If we are setting the total number of particles to a number higher
    // than what is allocated, we need to allocate new arrays
    if( tp > _allocatedParticles )
    {
        // Allocate new memory
        size_t particlesSize = tp * sizeof(tParticle);
        size_t quadsSize = sizeof(_quads[0]) * tp * 1;
        size_t indicesSize = sizeof(_indices[0]) * tp * 6 * 1;
        
        sBillboardParticle* particlesNew = (sBillboardParticle*)realloc(_particles, particlesSize);
        V3F_C4B_T2F_Quad* quadsNew = (V3F_C4B_T2F_Quad*)realloc(_quads, quadsSize);
        GLushort* indicesNew = (GLushort*)realloc(_indices, indicesSize);
        
        if (particlesNew && quadsNew && indicesNew)
        {
            // Assign pointers
            _particles = particlesNew;
            _quads = quadsNew;
            _indices = indicesNew;
            
            // Clear the memory
            memset(_particles, 0, particlesSize);
            memset(_quads, 0, quadsSize);
            memset(_indices, 0, indicesSize);
            
            _allocatedParticles = tp;
        }
        else
        {
            // Out of memory, failed to resize some array
            if (particlesNew) _particles = particlesNew;
            if (quadsNew) _quads = quadsNew;
            if (indicesNew) _indices = indicesNew;
            
            CCLOG("Particle system: out of memory");
            return;
        }
        
        _totalParticles = tp;
        
        initIndices();
        if (Configuration::getInstance()->supportsShareableVAO())
        {
            setupVBOandVAO();
        }
        else
        {
            setupVBO();
        }
        
        // fixed http://www.cocos2d-x.org/issues/3990
        // Updates texture coords.
        updateTexCoords();
    }
    else
    {
        _totalParticles = tp;
    }
    
    // fixed issue #5762
    // reset the emission rate
    setEmissionRate(_totalParticles / _life);
    
    resetSystem();
}
void BillboardParticleSystem::updateTexCoords()
{
    if (_texture)
    {
        const Size& s = _texture->getContentSize();
        initTexCoordsWithRect(Rect(0, 0, s.width, s.height));
    }
}
void BillboardParticleSystem::setTangentialAccel(float t)
{
    CCASSERT( _emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.tangentialAccel = t;
}

float BillboardParticleSystem::getTangentialAccel() const
{
    CCASSERT( _emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.tangentialAccel;
}

void BillboardParticleSystem::setTangentialAccelVar(float t)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.tangentialAccelVar = t;
}

float BillboardParticleSystem::getTangentialAccelVar() const
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.tangentialAccelVar;
}

void BillboardParticleSystem::setRadialAccel(float t)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.radialAccel = t;
}

float BillboardParticleSystem::getRadialAccel() const
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.radialAccel;
}

void BillboardParticleSystem::setRadialAccelVar(float t)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.radialAccelVar = t;
}

float BillboardParticleSystem::getRadialAccelVar() const
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.radialAccelVar;
}

void BillboardParticleSystem::setRotationIsDir(bool t)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.rotationIsDir = t;
}

bool BillboardParticleSystem::getRotationIsDir() const
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.rotationIsDir;
}

void BillboardParticleSystem::setGravity(const Vec2& g)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.gravity = g;
}

const Vec2& BillboardParticleSystem::getGravity()
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.gravity;
}

void BillboardParticleSystem::setSpeed(float speed)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.speed = speed;
}

float BillboardParticleSystem::getSpeed() const
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.speed;
}

void BillboardParticleSystem::setSpeedVar(float speedVar)
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    modeA.speedVar = speedVar;
}

float BillboardParticleSystem::getSpeedVar() const
{
    CCASSERT(_emitterMode == Mode::GRAVITY, "Particle Mode should be Gravity");
    return modeA.speedVar;
}

// ParticleSystem - Properties of Radius Mode
void BillboardParticleSystem::setStartRadius(float startRadius)
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    modeB.startRadius = startRadius;
}

float BillboardParticleSystem::getStartRadius() const
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    return modeB.startRadius;
}

void BillboardParticleSystem::setStartRadiusVar(float startRadiusVar)
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    modeB.startRadiusVar = startRadiusVar;
}

float BillboardParticleSystem::getStartRadiusVar() const
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    return modeB.startRadiusVar;
}

void BillboardParticleSystem::setEndRadius(float endRadius)
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    modeB.endRadius = endRadius;
}

float BillboardParticleSystem::getEndRadius() const
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    return modeB.endRadius;
}

void BillboardParticleSystem::setEndRadiusVar(float endRadiusVar)
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    modeB.endRadiusVar = endRadiusVar;
}

float BillboardParticleSystem::getEndRadiusVar() const
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    return modeB.endRadiusVar;
}

void BillboardParticleSystem::setRotatePerSecond(float degrees)
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    modeB.rotatePerSecond = degrees;
}

float BillboardParticleSystem::getRotatePerSecond() const
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    return modeB.rotatePerSecond;
}

void BillboardParticleSystem::setRotatePerSecondVar(float degrees)
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    modeB.rotatePerSecondVar = degrees;
}

float BillboardParticleSystem::getRotatePerSecondVar() const
{
    CCASSERT(_emitterMode == Mode::RADIUS, "Particle Mode should be Radius");
    return modeB.rotatePerSecondVar;
}

void BillboardParticleSystem::setScale(float s)
{
    _transformSystemDirty = true;
    Node::setScale(s);
}

void BillboardParticleSystem::setRotation(float newRotation)
{
    _transformSystemDirty = true;
    Node::setRotation(newRotation);
}

void BillboardParticleSystem::setScaleX(float newScaleX)
{
    _transformSystemDirty = true;
    Node::setScaleX(newScaleX);
}

void BillboardParticleSystem::setScaleY(float newScaleY)
{
    _transformSystemDirty = true;
    Node::setScaleY(newScaleY);
}
void BillboardParticleSystem::listenRendererRecreated(EventCustom* event)
{
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        setupVBOandVAO();
    }
    else
    {
        setupVBO();
    }
}