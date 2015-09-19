LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

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
				   ../../Classes/3d/Mesh.cpp \
                   ../../Classes/3d/MeshCache.cpp \
               	   ../../Classes/3d/Sprite3D.cpp \
                   ../../Classes/LoadingScene.cpp \
                   ../../Classes/MainMenuScene.cpp \
                   ../../Classes/GameOverLayer.cpp \
                   ../../Classes/ParticleManager.cpp \
                   ../../Classes/Plane.cpp \
                   ../../Classes/LicenseLayer.cpp \
                   ../../Classes/FriendControlScene.cpp \
                   ../../Classes/Reward.cpp \
                   ../../Classes/FriendPlayer.cpp \
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
