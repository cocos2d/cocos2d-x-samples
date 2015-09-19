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

#include "LoadingScene.h"
#include "HelloWorldScene.h"
#include "AirCraft.h"
#include "Enemies.h"
#include "Bullets.h"
#include "GameControllers.h"
#include "ParticleManager.h"
#include "consts.h"
#include "Sprite3DEffect.h"

int LoadingScene::updatecount=0;
int LoadingScene::m_curPreload_fodder_count=0;
int LoadingScene::m_curPreload_fodderL_count=0;
int LoadingScene::m_curPreload_BigDude_count=0;
int LoadingScene::m_curPreload_Missile_count=0;
int LoadingScene::m_curPreload_Boss_count=0;

int LoadingScene::audioloaded = false;
int LoadingScene::particleloaded = false;

LoadingScene::~LoadingScene()
{
}

Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	InitBk();
    InitCoco();
    LoadingResource();
    
    //NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(LoadingScene::GotoNextScene),"GotoNextScene",NULL);
    scheduleUpdate();
    
    return true;
}

void LoadingScene::InitBk()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("loadingAndHP.plist","loadingAndHP.png");
    
    //bk
    auto loading_bk=Sprite::createWithSpriteFrameName("loading_bk.png");
    loading_bk->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(loading_bk,0);
    
    
    //LabelPercent
    m_pPercent=Label::createWithBMFont("num.fnt","0%");
    m_pPercent->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+170));
    this->addChild(m_pPercent,1);
    
    //progress
    auto progress_bk=Sprite::createWithSpriteFrameName("loading_progress_bk.png");
    progress_bk->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2+300));
    addChild(progress_bk);
    
    m_pProgress=Sprite::createWithSpriteFrameName("loading_progress_thumb.png");
    m_pProgress->setPosition(Vec2(100, visibleSize.height/2+320));
    addChild(m_pProgress);
}

void LoadingScene::InitCoco()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto coco = EffectSprite3D::createFromObjFileAndTexture("coconut.c3b", "coco.png");
    if(coco)
    {
		coco->setRotation3D(Vec3(90,0,180));
        coco->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2-150));
        GameEntity::UseOutlineEffect(static_cast<Sprite3D*>(coco), 0.03, Color3B(0,0,0));
        
        addChild(coco,1);
        coco->runAction(RepeatForever::create(RotateBy::create(0.8f,Vec3(0,360,0))));
    }
}

void LoadingScene::LoadingResource()
{
    if(!particleloaded)
    LoadingParticle();
    //Loading Music
    if(!audioloaded)
    LoadingMusic();
    
    //Loading Picture
    LoadingPic();
}

void LoadingScene::LoadingMusic()
{
    audioloaded = true;
    auto Audio = CocosDenshion::SimpleAudioEngine::getInstance();
    Audio->preloadEffect("explodeEffect.mp3");
    Audio->preloadEffect("hit.mp3");
    Audio->preloadEffect("boom2.mp3");
    Audio->preloadEffect("boom.mp3");
    Audio->preloadBackgroundMusic("Orbital Colossus_0.mp3");
    //Audio->preloadBackgroundMusic("Star_Chaser.mp3");
    
    // Music By Matthew Pable (http://www.matthewpablo.com/)
    // Licensed under CC-BY 3.0 (http://creativecommons.org/licenses/by/3.0/)
    Audio->playBackgroundMusic("Flux2.mp3");
}

void LoadingScene::LoadingPic()
{
	auto TexureCache=Director::getInstance()->getTextureCache();
    TexureCache->addImageAsync("boss.png",CC_CALLBACK_1(LoadingScene::LoadingCallback,this));
    TexureCache->addImageAsync("coco.png",CC_CALLBACK_1(LoadingScene::LoadingCallback,this));
    TexureCache->addImageAsync("groundLevel.jpg", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("bullets.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("daodan_32.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("diji02_v002_128.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("dijiyuanv001.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("playerv002_256.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
    TexureCache->addImageAsync("streak.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
    
    TexureCache->addImageAsync("gameover_score_num_0.png",CC_CALLBACK_1(LoadingScene::LoadingCallback,this));
    TexureCache->addImageAsync("num_0.png",CC_CALLBACK_1(LoadingScene::LoadingCallback,this));
    TexureCache->addImageAsync("score_right_top.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
    
    TexureCache->addImageAsync("gameover.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));

}

void LoadingScene::LoadingCallback(Ref* pObj)
{
    ++currentNum;
    char tmp[10];
	int percent=(int)(((float)currentNum / totalNum) * 100);
    sprintf(tmp, "%d%%", percent);
    m_pPercent->setString(tmp);
    m_pProgress->runAction(MoveBy::create(0.01f, Vec2(420/TOTAL_PIC_NUM,0)));
//    m_pSlider->setValue(percent);
    

    if (currentNum == totalNum)
    {
        //NotificationCenter::getInstance()->postNotification("GotoNextScene",NULL);
        GotoNextScene();
    }
}

void LoadingScene::GotoNextScene()
{
    //goto next scene.
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameover.plist","gameover.png");
    
    scheduleOnce(schedule_selector(LoadingScene::RunNextScene), 1.0f);
}

void LoadingScene::RunNextScene(float dt)
{
    this->removeAllChildren();
    auto helloworldScene=HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionZoomFlipX::create(1.0f,helloworldScene));

}

void LoadingScene::update(float dt)
{
    ++updatecount;
    log("updateCount:%d........",updatecount);
    
    if (m_curPreload_fodder_count<PRELOAD_FODDER_COUNT) {
        LoadingEnemy(kEnemyFodder);
        m_curPreload_fodder_count++;
    }
    else if(m_curPreload_fodderL_count<PRELOAD_FODDERL_COUNT)
    {
        LoadingEnemy(kEnemyFodderL);
        m_curPreload_fodderL_count++;
    }
    else if (m_curPreload_BigDude_count<PRELOAD_BIGDUDE_COUBR)
    {
        LoadingEnemy(kEnemyBigDude);
        m_curPreload_BigDude_count++;
    }
    else if (m_curPreload_Missile_count<PRELOAD_MISSILE_COUNT)
    {
        LoadingBullet(kPlayerMissiles);
        m_curPreload_Missile_count++;
    }
    else if (m_curPreload_Boss_count<PRElOAD_BOSS_COUNT)
    {
        LoadingEnemy(kEnemyBoss);
        m_curPreload_Boss_count++;
    }
    else
    {
        unscheduleUpdate();
    }
}

void LoadingScene::LoadingEnemy(int type)
{
    switch(type)
    {
        case kEnemyFodder:
        {
            auto enemy_fodder = Fodder::create();
            enemy_fodder->retain();
            EnemyController::_fodderPool.pushBack(enemy_fodder);
        }
            break;
        case kEnemyFodderL:
        {
            auto enemy_fodderL= FodderLeader::create();
            enemy_fodderL->retain();
            EnemyController::_fodderLPool.pushBack(enemy_fodderL);
        }
            break;
        case kEnemyBigDude:
        {
            auto enmey_bigdude= BigDude::create();
            enmey_bigdude->retain();
            EnemyController::_bigDudePool.pushBack(enmey_bigdude);
        }
        case kEnemyBoss:
        {
            auto enemy_boss =Boss::create();
            enemy_boss->retain();
            EnemyController::_bossPool.pushBack(enemy_boss);
        }
            break;
        default:
            break;
    }
}

void LoadingScene::LoadingBullet(int type)
{
    switch (type) {
        case kPlayerMissiles:
            {
            auto bullet = Missile::create();
            bullet->retain();
            BulletController::_missilePool.pushBack(bullet);
            }
            break;
        default:
            break;
    }
}

void LoadingScene::LoadingParticle()
{
    particleloaded = true;
    auto particle=ParticleManager::getInstance();
    particle->AddPlistData("missileFlare.plist","missileFlare");
    particle->AddPlistData("emission.plist", "emission");
    particle->AddPlistData("missileFlare.plist","missileFlare");
    particle->AddPlistData("toonSmoke.plist", "toonSmoke");
    particle->AddPlistData("flare.plist", "flare");
    particle->AddPlistData("glow.plist", "glow");
    particle->AddPlistData("debris.plist", "debris");
    particle->AddPlistData("emissionPart.plist", "emissionPart");
    particle->AddPlistData("engine.plist", "engine");
}
