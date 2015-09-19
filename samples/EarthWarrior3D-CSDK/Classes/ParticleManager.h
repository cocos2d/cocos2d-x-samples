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
