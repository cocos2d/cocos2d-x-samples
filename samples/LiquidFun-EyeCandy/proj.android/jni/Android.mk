LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := liquidfun_eyecandy_shared

LOCAL_MODULE_FILENAME := libliquidfun_eyecandy

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/EyeCandyLayer.cpp \
                   ../../Classes/GLESDebugDraw.cpp \
                   ../../Classes/LFParticleSystemNode.cpp \
                   ../../Classes/LFSpriteNode.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += liquidfun_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,liquidfun)
