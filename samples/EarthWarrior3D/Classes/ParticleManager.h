//
//  ParticleManager.h
//  Moon3d
//
//  Created by cocos01 on 14-3-13.
//
//

#ifndef __Moon3d__ParticleManager__
#define __Moon3d__ParticleManager__

#include "cocos2d.h"

USING_NS_CC;

class ParticleManager
{
public:
    
    static ParticleManager* getInstance()
    {
        if ( m_pInstance == nullptr )
            m_pInstance = new ParticleManager();
        return m_pInstance;
    }
    
private:
    
    ParticleManager();
    
    static ParticleManager* m_pInstance;
    
    class CGarbo
    {
    public:
        ~CGarbo()
        {
            if (ParticleManager::m_pInstance!= nullptr)
            {
                delete ParticleManager::m_pInstance;
            }
        }
    };
    
    static CGarbo m_garbo;
    
public:
    
    std::map<std::string, ValueMap> m_plistMap;
    
    void AddPlistData(std::string strPlist,std::string strName);
    
    ValueMap GetPlistData(std::string strplist);
};

#endif /* defined(__Moon3d__ParticleManager__) */
