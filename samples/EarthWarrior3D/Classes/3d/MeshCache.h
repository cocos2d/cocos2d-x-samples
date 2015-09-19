
#ifndef __CCMESH_CACHE_H_
#define __CCMESH_CACHE_H_

#include <string>
#include <map>
#include "cocos2d.h"

class Mesh;
class MeshCache
{
public:
    MeshCache();
    virtual ~MeshCache();

    static MeshCache* getInstance();
    static void purgeMeshCache();

    Mesh* addMesh(const std::string& fileName);
    void removeMesh(const std::string& fileName);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void listenBackToForeground(cocos2d::EventCustom* event);
#endif
    
protected:
    static MeshCache* _cacheInstance;
    std::map<std::string, Mesh*> _cachedMeshes;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::EventListenerCustom* _backToForegroundlistener;
#endif
};

#endif // __CCMESH_CACHE_H_