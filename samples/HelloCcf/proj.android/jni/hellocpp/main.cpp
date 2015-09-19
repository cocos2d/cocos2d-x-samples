#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "ConnectionInterface.h"
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
	void Java_com_intel_csdk_wrapper_JNIMediator_nativePeerAdd(JNIEnv* env, jobject thiz, jobject obj_peer){
		LOGD("Java_com_intel_csdk_wrapper_JNIMediator_nativePeerAdd");

	    jclass peer_cls = env->GetObjectClass(obj_peer);

	    jfieldID nameFieldID = env->GetFieldID(peer_cls,"_sessionName","Ljava/lang/String;");
	    jfieldID idFieldID = env->GetFieldID(peer_cls,"_sessionId","Ljava/lang/String;");
	    jfieldID idAviabileID = env->GetFieldID(peer_cls,"_availability","Z");
	    jfieldID idCloudID = env->GetFieldID(peer_cls,"_availability_cloud","Z");
	    jfieldID idProximityID = env->GetFieldID(peer_cls,"_availability_proximity","Z");

	    jstring sessionName = (jstring)env->GetObjectField(obj_peer , nameFieldID);
	    jstring sessionId = (jstring)env->GetObjectField(obj_peer , idFieldID);

	    const char * c_name = env->GetStringUTFChars(sessionName ,NULL);//转换成 char *
	    const char * c_id = env->GetStringUTFChars(sessionId ,NULL);//转换成 char *

	    tagPEER jniPeer;
	    jniPeer._sessionName = c_name;
	    jniPeer._sessionId = c_id;
	    jniPeer._availability = env->GetObjectField(obj_peer, idAviabileID);
	    jniPeer._availability_cloud = env->GetObjectField(obj_peer, idCloudID);
	    jniPeer._availability_proximity = env->GetObjectField(obj_peer, idProximityID);
	    jniPeer.add = true;

	    ConnectionInterface::OnPeerUpdate(jniPeer);

	    env->ReleaseStringUTFChars(sessionName, c_name); //释放引用
	    env->ReleaseStringUTFChars(sessionId, c_id); //释放引用
	}

	void Java_com_intel_csdk_wrapper_JNIMediator_nativePeerRemove(JNIEnv* env, jobject thiz, jobject obj_peer){
		LOGD("Java_com_intel_csdk_wrapper_JNIMediator_nativePeerRemove");

	    jclass peer_cls = env->GetObjectClass(obj_peer);

	    jfieldID nameFieldID = env->GetFieldID(peer_cls,"_sessionName","Ljava/lang/String;"); //get sessionName
	    jfieldID idFieldID = env->GetFieldID(peer_cls,"_sessionId","Ljava/lang/String;"); //get sessionId

	    jstring sessionName = (jstring)env->GetObjectField(obj_peer , nameFieldID);
	    jstring sessionId = (jstring)env->GetObjectField(obj_peer , idFieldID);

	    const char * c_name = env->GetStringUTFChars(sessionName ,NULL);//转换成 char *
	    const char * c_id = env->GetStringUTFChars(sessionId ,NULL);//转换成 char *

	    tagPEER jniPeer;
	    jniPeer._sessionName = c_name;
	    jniPeer._sessionId = c_id;
	    jniPeer.add = false;

	    ConnectionInterface::OnPeerUpdate(jniPeer);

	    env->ReleaseStringUTFChars(sessionName, c_name); //释放引用
	    env->ReleaseStringUTFChars(sessionId, c_id); //释放引用
	}

	void Java_com_intel_csdk_wrapper_JNIMediator_nativeInvite(JNIEnv* env, jobject thiz, jstring peerID){
		const char *cId = env->GetStringUTFChars(peerID, NULL);
		LOGD("Java_com_intel_csdk_wrapper_JNIMediator_nativeInvite sessionName:%s", cId);
	    ConnectionInterface::OnReciveInvite(cId);
		env->ReleaseStringUTFChars(peerID, cId);
	}

	void Java_com_intel_csdk_wrapper_JNIMediator_nativeReceiveMsg(JNIEnv* env, jobject thiz, jstring msg){
		const char *cMsg = env->GetStringUTFChars(msg, NULL);
		LOGD("Java_com_intel_csdk_wrapper_JNIMediator_nativeReceiveMsg :%s", cMsg);
	    ConnectionInterface::OnReceiveMessage(cMsg);
		env->ReleaseStringUTFChars(msg, cMsg);

	}

	void Java_com_intel_csdk_wrapper_JNIMediator_nativeInviteAcknowledgment(JNIEnv* env, jobject thiz){
		LOGD("Java_com_intel_csdk_wrapper_JNIMediator_nativeInviteAcknowledgment");
		ConnectionInterface::OnAcknowledgment();
	}

	void Java_com_intel_csdk_wrapper_JNIMediator_nativeDisconnect(JNIEnv* env, jobject thiz){
		LOGD("Java_com_intel_csdk_wrapper_JNIMediator_nativeDisconnect");
		ConnectionInterface::OnDisconnect();
	}
}
