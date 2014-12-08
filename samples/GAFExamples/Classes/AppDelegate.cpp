#include "AppDelegate.h"

#include "GafFeatures.h"

#include <vector>
#include <string>
#include "GAFShaderManager.h"


static int const kGlobalFPS = 60;
USING_NS_CC;
USING_NS_GAF;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    std::vector<std::string> paths;
    paths.push_back("Resources");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    paths.push_back("../Resources");
#endif

    cocos2d::FileUtils::getInstance()->setSearchPaths(paths);
    cocos2d::Director *pDirector = cocos2d::Director::getInstance();

    cocos2d::GLView* glView = pDirector->getOpenGLView();

    if (!glView)
    {
#if COCOS2D_VERSION < 0x00030300
        glView = cocos2d::GLView::createWithRect("GAF Animation sample", cocos2d::Rect(0, 0, 1024, 768));
#else
        glView = GLViewImpl::create("GAF Animation sample");
#endif
        pDirector->setOpenGLView(glView);
    }

    // turn on display FPS
    pDirector->setDisplayStats(1);

    CCTexture2D::setDefaultAlphaPixelFormat(cocos2d::Texture2D::PixelFormat::RGBA8888);
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);

    pDirector->setAnimationInterval(1.0 / kGlobalFPS);

    glView->setDesignResolutionSize(1024, 768, ResolutionPolicy::FIXED_HEIGHT);

    cocos2d::Size frameSize = glView->getFrameSize();

    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.

    // if the frame's height is larger than the height of medium resource size, select large resource.
    if (frameSize.height > 768)
    {
        pDirector->setContentScaleFactor(2);
    }

    //pDirector->setContentScaleFactor(2.f);

    // create a scene. it's an autorelease object
    cocos2d::Scene *pScene = GafFeatures::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    cocos2d::Director::getInstance()->startAnimation();
}

#ifdef _WIN32

int WINAPI WinMain(__in HINSTANCE hInstance,
    __in_opt HINSTANCE hPrevInstance,
    __in LPSTR lpCmdLine,
    __in int nShowCmd
    )
{
    AppDelegate app;

    return cocos2d::Application::getInstance()->run();
}
#endif
