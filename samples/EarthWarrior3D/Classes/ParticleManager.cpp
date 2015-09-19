//
//  ParticleManager.cpp
//  Moon3d
//
//  Created by cocos01 on 14-3-13.
//
//

#include "ParticleManager.h"

ParticleManager* ParticleManager::m_pInstance=NULL;
ParticleManager::CGarbo ParticleManager::m_garbo;
ParticleManager::ParticleManager()
{
    m_plistMap.clear();
}

void ParticleManager::AddPlistData(std::string strPlist,std::string strName)
{
    auto plistData=FileUtils::getInstance()->getValueMapFromFile(strPlist);
    std::map<std::string, ValueMap>::iterator it = m_plistMap.begin();
    m_plistMap.insert(it,std::pair<std::string, ValueMap>(strName,plistData));
}

ValueMap ParticleManager::GetPlistData(std::string strplist)
{
    auto plistData=m_plistMap.find(strplist)->second;
    return plistData;
}
