
//  MainScene.cpp
//  Created by Justin Graham on 6/25/14.

#include "MainScene.h"
#import "cocos-Bridge-Contents.h"

#include "base/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
#   import "SwiftTetris-swift.h"
#else
#   import "SwiftTetris-swift.h"
#endif

MainScene::MainScene()
{
    [[Director getInstance] runWithScene:[SceneSplash new]];
}
