//
//  LoadingScene.h
//  Moon3d
//
//  Created by Jacky on 3/10/14.
//
//

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
    LabelBMFont* m_pPercent;
    
    static int m_curPreload_fodder_count;
    static int m_curPreload_fodderL_count;
    static int m_curPreload_BigDude_count;
    static int m_curPreload_Missile_count;
    static int m_curPreload_Boss_count;
    
    static int updatecount;

    static int particleloaded;
};



#endif /* defined(__Moon3d__LoadingScene__) */
