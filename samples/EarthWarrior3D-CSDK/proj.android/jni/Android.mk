LOCAL_PATH := $(call my-dir)

CCF_PATH := intel_ccf
include $(CLEAR_VARS)
LOCAL_MODULE := AFE
LOCAL_SRC_FILES := $(CCF_PATH)/$(TARGET_ARCH_ABI)/libAFE.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := STC
LOCAL_SRC_FILES := $(CCF_PATH)/$(TARGET_ARCH_ABI)/libSTC.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := stcapi
LOCAL_SRC_FILES := $(CCF_PATH)/$(TARGET_ARCH_ABI)/libstcapi.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := stcjnimediator
LOCAL_SRC_FILES := $(CCF_PATH)/$(TARGET_ARCH_ABI)/libstcjnimediator.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES += AFE
LOCAL_SHARED_LIBRARIES += STC
LOCAL_SHARED_LIBRARIES += stcapi
LOCAL_SHARED_LIBRARIES += stcjnimediator

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/AirCraft.cpp \
                   ../../Classes/GameEntity.cpp \
                   ../../Classes/GameLayer.cpp \
                   ../../Classes/Player.cpp \
                   ../../Classes/PublicApi.cpp \
                   ../../Classes/Enemies.cpp \
                   ../../Classes/Bullets.cpp \
                   ../../Classes/Effects.cpp \
                   ../../Classes/Explosion.cpp \
                   ../../Classes/GameControllers.cpp \
                   ../../Classes/LoadingScene.cpp \
                   ../../Classes/MainMenuScene.cpp \
                   ../../Classes/GameOverLayer.cpp \
                   ../../Classes/ParticleManager.cpp \
                   ../../Classes/Plane.cpp \
                   ../../Classes/Sprite3DEffect.cpp \
                   ../../Classes/LicenseLayer.cpp \
                   ../../Classes/ConnectionInterface.cpp \
                   ../../Classes/PopLayer.cpp \
                   ../../Classes/CCFLayer.cpp \
                   ../../Classes/CCFPlayer.cpp \
                   ../../Classes/FriendControlScene.cpp \
                   ../../Classes/PeerButton.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
 LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
 $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
