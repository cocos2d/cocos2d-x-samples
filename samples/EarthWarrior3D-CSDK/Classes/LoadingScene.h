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

#ifndef __Moon3d__LoadingScene__
#define __Moon3d__LoadingScene__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

#define TOTAL_PIC_NUM 13

#define PRELOAD_FODDER_COUNT 18
#define PRELOAD_FODDERL_COUNT 3
#define PRELOAD_BIGDUDE_COUBR 5
#define PRELOAD_MISSILE_COUNT 5
#define PRElOAD_BOSS_COUNT    1

class LoadingScene : public Layer
{
public:
    
    LoadingScene():currentNum(0),
    totalNum(TOTAL_PIC_NUM){};
    
    ~LoadingScene();
    
    static Scene* createScene();
    
    virtual bool init();
    
    void update(float dt);
    static int audioloaded;
    CREATE_FUNC(LoadingScene);
    
private:
    void InitBk();
    void InitCoco();
    void LoadingResource();
    void LoadingMusic();
    void LoadingPic();
    void LoadingEnemy(int type);
    void LoadingBullet(int type);
    void LoadingParticle();
    
    void LoadingCallback(Ref* pObj);
    void GotoNextScene();
    void RunNextScene(float dt);
    
    
private:
    static bool isReg;
    int currentNum;
    int totalNum;
    
    Sprite* m_pProgress;
    Label* m_pPercent;
    
    static int m_curPreload_fodder_count;
    static int m_curPreload_fodderL_count;
    static int m_curPreload_BigDude_count;
    static int m_curPreload_Missile_count;
    static int m_curPreload_Boss_count;
    
    static int updatecount;

    static int particleloaded;
};



#endif /* defined(__Moon3d__LoadingScene__) */
