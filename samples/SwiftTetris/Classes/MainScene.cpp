
//  MainScene.cpp
//  Created by Justin Graham on 6/25/14.

#include "MainScene.h"

#include "base/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
#   import "swiftress_Mac-swift.h"
#else
#   import "swiftress-Swift.h"
#endif

MainScene::MainScene()
{
    [[Director getInstance] runWithScene:[SceneSplash new]];
}
