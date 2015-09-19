#include "AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"
#include "../../../Classes/HelloWorldScene.h"
#include "../../../Classes/MainMenuScene.h"
#include "../../../Classes/FriendControlScene.h"
#include "../../../Classes/GameLayer.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>


#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

void cocos_android_app_init (JNIEnv* env, jobject thiz) {
    LOGD("cocos_android_app_init");
    AppDelegate *pAppDelegate = new AppDelegate();
}

extern "C" {

	void Java_com_cocos2dx_moon3d_AppActivity_SendGift(JNIEnv* env, jobject thiz, jstring type, jstring count){
		const char *sType = env->GetStringUTFChars(type, NULL);
		LOGD("Java_com_cocos2dx_moon3d_AppActivity_SendGift type:%s", sType);
		
		HelloWorld *pScene = (HelloWorld *)Director::getInstance()->getRunningScene();
    if(pScene && pScene->getChildByTag(100) && pScene->getChildByTag(100)->getChildByTag(123))
    {
        GameLayer *pLayer = (GameLayer *)pScene->getChildByTag(100)->getChildByTag(123);
				pLayer->addNodeAsync(sType);
    }
        
		env->ReleaseStringUTFChars(type, sType);
	}
	
	void Java_com_cocos2dx_moon3d_AppActivity_StartGame(JNIEnv* env, jobject thiz, jstring something){
		const char *sTemp = env->GetStringUTFChars(something, NULL);
		
		LOGD("Java_org_cocos2dx_cpp_AppActivity_StartGame something:%s", sTemp);
		
		Scene *pScene = (Scene *)Director::getInstance()->getRunningScene();
        if(pScene && pScene->getChildByTag(1001))
        {
            MainMenuScene *pLayer = (MainMenuScene *)pScene->getChildByTag(1001);
            pLayer->jniStartGame(sTemp);
        }
         
		env->ReleaseStringUTFChars(something, sTemp);
	}	
	
	void Java_com_cocos2dx_moon3d_AppActivity_StartControl(JNIEnv* env, jobject thiz){
		
		LOGD("Java_org_cocos2dx_cpp_AppActivity_StartGame something:");
		
		Scene *pScene = (Scene *)Director::getInstance()->getRunningScene();
        if(pScene && pScene->getChildByTag(1001))
        {
            MainMenuScene *pLayer = (MainMenuScene *)pScene->getChildByTag(1001);
            pLayer->jniStartControl();
        }
   	}		
   	
	void Java_com_cocos2dx_moon3d_AppActivity_ReturnMainMenu(JNIEnv* env, jobject thiz){
		
		LOGD("Java_org_cocos2dx_cpp_AppActivity_ReturnMainMenu");
		
		Scene *pScene = (Scene *)Director::getInstance()->getRunningScene();
        if(pScene && pScene->getChildByTag(1002))
        {
            FriendControl *pLayer = (FriendControl *)pScene->getChildByTag(1002);
            pLayer->jniReturnMainMenu();
        }
   	}		   	
}
