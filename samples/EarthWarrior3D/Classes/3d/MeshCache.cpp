#include "MeshCache.h"
#include "Mesh.h"
#include "cocos2d.h"

using namespace cocos2d;

MeshCache* MeshCache::_cacheInstance = nullptr;

typedef std::map<std::string, Mesh*>::iterator MeshMapIter;

MeshCache::MeshCache()
{
    _cachedMeshes.clear();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // listen the event when app go to foreground
    _backToForegroundlistener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, CC_CALLBACK_1(MeshCache::listenBackToForeground, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundlistener, -1);
#endif
}

MeshCache::~MeshCache()
{
    for (auto iter = _cachedMeshes.begin(); iter != _cachedMeshes.end(); ++iter) {
        CC_SAFE_DELETE(iter->second);
    }
    _cachedMeshes.clear();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundlistener);
#endif
}

MeshCache* MeshCache::getInstance()
{
    if (! _cacheInstance) {
        _cacheInstance = new MeshCache();
    }
    
    return _cacheInstance;
}

void MeshCache::purgeMeshCache()
{
    if (_cacheInstance) {
        CC_SAFE_DELETE(_cacheInstance);
    }
}

Mesh* MeshCache::addMesh(const std::string& fileName)
{
    Mesh* ret = nullptr;
    const std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    MeshMapIter it = _cachedMeshes.find(fullPath);
    if (it == _cachedMeshes.end()) {
        ret = new Mesh(fileName);
        _cachedMeshes.insert(std::make_pair(fullPath, ret));
    }
    else
    {
        ret = it->second;
    }

    return ret;
}

void MeshCache::removeMesh(const std::string& fileName)
{
    const std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    MeshMapIter it = _cachedMeshes.find(fullPath);
    if (it != _cachedMeshes.end()) {
        CC_SAFE_DELETE(it->second);
        _cachedMeshes.erase(it);
    }
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void MeshCache::listenBackToForeground(EventCustom* event)
{
    for (auto iter = _cachedMeshes.begin(); iter != _cachedMeshes.end(); ++iter) {
        Mesh* mesh = iter->second;
        mesh->loadFromFile(iter->first);
    }
}
#endif
