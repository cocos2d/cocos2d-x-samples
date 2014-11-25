LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := liquidfun_testbed_shared

LOCAL_MODULE_FILENAME := libliquidfun_testbed

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/ParticleParameter.cpp \
                   ../../Classes/VisibleRect.cpp \
                   ../../Classes/TestEntries.cpp \
                   ../../Classes/Test.cpp \
                   ../../Classes/GLESDebugDraw.cpp \
                   ../../Classes/Box2dView.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += liquidfun_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,liquidfun)
