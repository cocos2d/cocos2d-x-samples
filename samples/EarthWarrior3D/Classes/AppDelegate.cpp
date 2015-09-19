#include "AppDelegate.h"
#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    //glview->setDesignResolutionSize(480,800,ResolutionPolicy::FIXED_HEIGHT);
    if(!glview) {
        int height, width;
        height = 800;
        width = height*(640.0/960.0);
        
        glview = GLView::createWithRect("EarthWarrior3D", Rect(0, 0, width, height));
        
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(640, 960, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //auto scene = LoadingScene::createScene();
    auto scene = MainMenuScene::createScene();
    //auto scene = HelloWorld::createScene();
    // run
    director->runWithScene(scene);
    glEnable(GL_CULL_FACE);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    SimpleAudioEngine::getInstance()->pauseAllEffects();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    Director::getInstance()->stopAnimation();
    
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    SimpleAudioEngine::getInstance()->resumeAllEffects();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
 
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

