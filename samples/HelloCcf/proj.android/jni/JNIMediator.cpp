#include <jni.h>
#include "com_intel_csdk_wrapper_JNIMediator.h"
#include "STC_RESULTS.h"
#include <sys/socket.h>
#include <sys/un.h>
#include "include/STCAPI.h"
#include "include/osal.h"
#include <string.h>
#include <string>
#include <sstream>
#include <limits.h>
#include <stdlib.h>
#include "include/uuid.h"
#include <thread>

#define STC_INVITE_STATUS_DISCONNECTED 25




typedef struct BLAH {
	JavaVM *jvm;
	jobject jobj;
	jclass jclazz;
	int responseLength;
}jniStruct;

/// Structure to have all the Peer Device information
typedef struct SESSION {
	STCSessionUpdate info;
	int responseLength;
} session;

static session s_sessions[100];
static session s_localSession;
static std::string s_applicationId;
static std::string s_myClientId;
static STCApplicationId* applicationId;
static STC_HANDLE s_sdkHandle;

static jniStruct s_jni_struct = {0};
static int s_sock = STC_INVALID_SOCKET;
static bool s_IsUnboxed = false;


void RegisterLocalSession();
//  start Callback  function used in CCF
void CALLBACK onInviteRequestCallback(PSTCInviteRequest message, PVOID callbackArg);
void CALLBACK onPeerUpdateCallback(PSTCSessionUpdate update, PVOID callbackArg);
void CALLBACK onLocalSessionUpdateCallback(PSTCSessionUpdate update, PVOID callbackArg);
void CALLBACK onInviteCompleteCallback(PSTCInviteComplete message, PVOID callbackArg);
void CALLBACK onStreamEventUpdateCallback(PSTCStreamEvent message, PVOID callbackArg);
void CALLBACK onNodeUpdate(PSTCDiscoveryNodeCredentialsUpdate Update, PVOID callbackArg);
// End of callback function used in CCF


/*
 * Class:     com_intel_csdk_JNILayer
 * Method:    STCInit
 * Signature: ([JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)J
 */

/*
extern "C" JNIEXPORT jlong JNICALL Java_com_intel_csdk_JNILayer_STCInit
(JNIEnv *env, jobject obj, jlongArray inSdkHandle, jstring inOriginPath, jstring inUuid, jstring inClientId, jstring inClientSecret)
*/

extern "C" JNIEXPORT jlong JNICALL Java_com_intel_csdk_wrapper_JNIMediator_nativeInit
  (JNIEnv *env, jobject obj, jstring inOriginPath, jstring inUuid, jstring inClientId, jstring inClientSecret)
{
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Entering JNIMediator_nativeInit");
	env->GetJavaVM(&s_jni_struct.jvm);
	s_jni_struct.jobj = reinterpret_cast<jobject>(env->NewGlobalRef(obj));
	jclass clazz =env->FindClass("com/intel/csdk/wrapper/JNIMediator");
	s_jni_struct.jclazz = reinterpret_cast<jclass>(env->NewGlobalRef(clazz));
	int hResult = 0;
	if (!inUuid || !inClientId || !inClientSecret)
	{
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Error in Argument");
		return -10;
	}

/**Allocating J parameters to C parameters**/
	const char* strOriginPath = (*env).GetStringUTFChars(inOriginPath, NULL);///Need to set the path of the app
	const char* strUUID = (*env).GetStringUTFChars(inUuid, NULL); //Appliaction ID
	const char* strClientId = (*env).GetStringUTFChars(inClientId, NULL); //Client ID
	const char* strClientSecret = (*env).GetStringUTFChars(inClientSecret, NULL); //Client Secret
	int iconSize = 10;

	GUID myApplicationId;
	StringToUuid(strUUID, &myApplicationId);

	STCApplicationId ApplicationId = {0};
	ApplicationId.applicationId = myApplicationId;
	strcpy(ApplicationId.clientId, strClientId);
	strcpy(ApplicationId.clientSecret, strClientSecret);

	ApplicationId.applicationIconFormat = 0;
	ApplicationId.applicationIconSize = iconSize;
	ApplicationId.numPlayers = 2;
	strcpy(ApplicationId.applicationName, "NativeChat");
	strcpy(ApplicationId.applicationDescription, "Chat using C SDK in Android");
	strcpy(ApplicationId.inviteIntent, "com.intel.stc.csdk.wrapper.JNIMediator");
	strcpy(ApplicationId.launchActivity, "com.intel.stc.csdk.JNIMediator");
/**Finished allocating J parameters to C parameters**/

	 hResult = STCInitialize(strOriginPath,&s_sdkHandle, ApplicationId, 0);
	 if(hResult==0)
	 {
		 __android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Initialize success: STCInit()");
		 hResult = STCQueryUnboxedState(s_sdkHandle,&s_IsUnboxed)	;
		 if(hResult == 0){
			 if(s_IsUnboxed)
			 {
//				Calling Java : Providing info stating Unboxing is Done
				 jmethodID methodID = env->GetMethodID(clazz,"requestIdentityDetails","(Z)V");
				 env->CallVoidMethod(obj,methodID,false);
				 RegisterLocalSession();

			 }
			 else
			 {

				 jmethodID methodID = env->GetMethodID(clazz,"requestIdentityDetails","(Z)V");
				 env->CallVoidMethod(obj,methodID,true);
				 //call java  RequestforIdentitydetails(true); Requesting for identity details

			 }
		 }else
		 {
			 std::stringstream logdata;
			 logdata << "[Nativechat] STCQueryUnboxedState  Fail  hResult:  "<< hResult;
			 __android_log_write(ANDROID_LOG_ERROR, CSDK_TAG,logdata.str().c_str() );
		 }

	 }
	 else
	 {
		 std::stringstream logdata;
		 logdata << "[Nativechat] Initialize Fail  hResult:  "<< hResult;
		 __android_log_write(ANDROID_LOG_ERROR, CSDK_TAG,logdata.str().c_str() );
	 }

	return hResult;

}

//Register the function which will provided details for onLocalSessionUpdateCallback
void RegisterLocalSession()
{
	int stcResult= STC_SUCCESS;

	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Calling STCSetLocalSessionUpdateCallback");
	stcResult = STCSetLocalSessionInfoCallback(s_sdkHandle, onLocalSessionUpdateCallback, (PVOID)&s_jni_struct);
	if(stcResult==0)
	{
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Registering LocalSession Success");
	}else
	{
		std::stringstream logdata;
		 logdata << "[Nativechat] STCSetLocalSessionUpdateCallback  Fail  hResult:  "<< stcResult;
		 __android_log_write(ANDROID_LOG_ERROR, CSDK_TAG,logdata.str().c_str() );

	}
}

/*
 * Class:     com_intel_csdk_ApplicationService_JNIMediator
 * Method:    nativeIdentity
 * Signature: (Ljava/lang/String;Ljava/lang/String;[B)J
 */
//
JNIEXPORT jlong JNICALL Java_com_intel_csdk_wrapper_JNIMediator_nativeIdentity
  (JNIEnv *env, jobject obj, jstring userName, jstring deviceName, jbyteArray avatar, jint size)
{
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] nativeIdentity started");
	std::stringstream logdata;
	int stcResult= STC_SUCCESS;
	Byte_t *PtrAvatar;
	int AvatarSize = 1024;
	const char* strUserName = (*env).GetStringUTFChars(userName, NULL); //UserName
	const char* strDeviceName = (*env).GetStringUTFChars(deviceName, NULL); //DeviceName
	PtrAvatar = (Byte_t*)malloc(size);
	DWORD avatarSize = (env)->GetArrayLength (avatar);
	PBYTE buf = new BYTE[avatarSize];
		(env)->GetByteArrayRegion (avatar, 0, avatarSize, reinterpret_cast<jbyte*>(buf));

	 stcResult = STCSetUserName(s_sdkHandle, strUserName);
	if(stcResult==STC_SUCCESS)
	{
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Calling STCSetDeviceName");
		stcResult = STCSetDeviceName(s_sdkHandle, strDeviceName);
		if(stcResult==STC_SUCCESS)
		{
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Calling STCSetAvatar");
			 stcResult = STCSetAvatar(s_sdkHandle, avatarSize,0, buf);
			 if(!s_IsUnboxed)
			 {
				 RegisterLocalSession();
				 s_IsUnboxed = true;
			 }
		}
	}

	if(stcResult!=STC_SUCCESS)
	{

		logdata << "[Nativechat] Error in Setting Identity    hResult:  "<< stcResult;
		 __android_log_write(ANDROID_LOG_ERROR, CSDK_TAG,logdata.str().c_str() );
	}


}

// Function called when It is registered to STCSetSessionUpdateCallback()
// Notify the application change status of all the remote  system which are connected
void CALLBACK  onPeerUpdateCallback(PSTCSessionUpdate update, PVOID callbackArg)
{
	bool attached = false;
	std::stringstream logdata;
	logdata << "[Nativechat] Entering  onPeerUpdateCallback  UserName:  "<< update->szUserName;
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG,logdata.str().c_str() );
	jniStruct js_cb = {0};// To call the JNI class
	js_cb = *((jniStruct*)callbackArg);
	if(!js_cb.jvm) return;
		JNIEnv *myEnv = NULL;
		int retVal = js_cb.jvm->GetEnv((void**)&myEnv, JNI_VERSION_1_6);
		if(retVal == JNI_EDETACHED) {
			retVal = js_cb.jvm->AttachCurrentThread(&myEnv, NULL);
			if(retVal != JNI_OK) {
				return;
			}
			if(retVal == JNI_OK) {
				attached = true;
				retVal = js_cb.jvm->GetEnv((void**)&myEnv, JNI_VERSION_1_6);
				if(retVal != JNI_OK) {
					__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Failed to getEnv after attaching to JVM.");
				}
				__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Attached thread to JVM");
			}
		}
		else if(retVal == JNI_OK) {
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Already attached thread to JVM");
		}
		else if(retVal == JNI_EVERSION) {
			__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Wrong version of JNI to attach to JVM");
		}
		else if(retVal == JNI_ERR) {
			__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] JNI Error");
		}
		if(!myEnv) return;
		//Setting Calling Java Function " onPeerDiscovery" name
		jmethodID methodId = myEnv->GetMethodID(js_cb.jclazz, "onPeerDiscovery","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[B[Ljava/lang/Object;ZZZ)V");
		//(UUID,USERNAME,DEVICENAME,Avatar,AppliationIDs,isAvailable,isAvailableCloud,isAvailableProximity);
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "Setting Calling Java Function :sessionUpdate name");
		if(update) {
			jstring jUserName = myEnv->NewStringUTF(std::string(update->szUserName).c_str());
			jstring jDeviceName = myEnv->NewStringUTF(std::string(update->szSessionName).c_str());
			jstring jSessionId = myEnv->NewStringUTF(UuidToString(update->sessionId).c_str());
			jint jAvatarLength = update->avatarSize;
			jobjectArray jMessageArray;
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "Setting values from update coming from CCF Framework");
			jbyteArray jAvatar = myEnv->NewByteArray(update->avatarSize);
			jMessageArray = (jobjectArray)myEnv->NewObjectArray(update->applicationCount, myEnv->FindClass("java/lang/String"), myEnv->NewStringUTF(""));
			for(int i=0; i<update->applicationCount; i++) {
				myEnv->SetObjectArrayElement(jMessageArray, i, myEnv->NewStringUTF(UuidToString(update->applications[i]).c_str()));
			}
			myEnv->SetByteArrayRegion(jAvatar, 0, update->avatarSize, (jbyte*)update->avatar);
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Sending sessionUpdate to Java layer of application.");
			myEnv->CallVoidMethod(js_cb.jobj, methodId,jSessionId, jUserName, jDeviceName,jAvatar,jMessageArray,update->isAvailable,update->isAvailableCloud,update->isAvailableProximity);

		}
		if(attached) retVal = js_cb.jvm->DetachCurrentThread();
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat]  sessionUpdate completed.");
}

void CALLBACK onLocalSessionUpdateCallback(PSTCSessionUpdate update, PVOID callbackArg)
{
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Callback update localSessionUpdateCallback");
}

extern "C" JNIEXPORT jlong JNICALL Java_com_intel_csdk_JNILayer_STCCleanup
  (JNIEnv *env, jobject obj, jlong){

}
//Function called when it is registered to  STCListenForInvites()
// Receives the Invite  Request from the Remote systems
// Sends the responds to the remote system stating accepting the connection

void CALLBACK onInviteRequestCallback(PSTCInviteRequest message, PVOID callbackArg)
{
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Entering inviteRequestCallback()");

	int sTemp = STC_INVALID_SOCKET;
	if(s_sock != sTemp){
		std::stringstream logdata;
			STC_RESULT stcResult = STC_SUCCESS;
			HSTCINVITE hInvite = message->hInvite;
			bool temp = false;
			stcResult = STCSendInviteResponse(s_sdkHandle,hInvite,temp);
			if(stcResult != STC_SUCCESS){
				logdata << "[Nativechat]  onInviteRequestCallback --> invitation rejected due to existing connection. "<<stcResult;
				__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, logdata.str().c_str());
			}
			return;
	}

	jniStruct js_cb = {0};
	js_cb = *((jniStruct*)callbackArg);
	bool attached = false;
	if(!js_cb.jvm) return;
	JNIEnv *myEnv = NULL;
	int retVal = js_cb.jvm->GetEnv((void**)&myEnv, JNI_VERSION_1_6);
	if(retVal == JNI_EDETACHED) {
		retVal = js_cb.jvm->AttachCurrentThread(&myEnv, NULL);
		if(retVal != JNI_OK) {
			return;
		}
		if(retVal == JNI_OK) {
			attached = true;
			retVal = js_cb.jvm->GetEnv((void**)&myEnv, JNI_VERSION_1_6);
			if(retVal != JNI_OK) {
				__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Failed to getEnv after attaching to JVM.");
			}
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Attached thread to JVM");
		}
	}
	else if(retVal == JNI_OK) {
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Already attached thread to JVM");
	}
	else if(retVal == JNI_EVERSION) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Wrong version of JNI to attach to JVM");
	}
	else if(retVal == JNI_ERR) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] JNI Error");
	}
	if(!myEnv) return;
	jmethodID methodId = myEnv->GetMethodID(js_cb.jclazz, "onInvitationReceived", "(Ljava/lang/String;J)V");

	if(message) {
		jstring jSessionId = myEnv->NewStringUTF(UuidToString(message->sessionId).c_str());
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Sending invite to Java layer of application.");
		// calling java function onInvitationReceived
		myEnv->CallVoidMethod(js_cb.jobj, methodId,  jSessionId, message->hInvite);
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] invite sent");
	}
	else {
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Invite associated with session is NULL.");
	}
	if(attached) retVal = js_cb.jvm->DetachCurrentThread();
	if(retVal != JNI_OK && attached) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Failed to detach thread from JVM");
	}
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Returning from inviteRequestCallback()");
}

//Updating the application regarding the status of Peer connection.
void sendToJavaChat(std::string message) {
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, std::string("[Nativechat] Received Message: " + message).c_str());
	jniStruct js_cb = s_jni_struct;
	bool attached = false;
	if(!js_cb.jvm) return;
	JNIEnv *myEnv = NULL;
	int retVal = js_cb.jvm->GetEnv((void**)&myEnv, JNI_VERSION_1_6);
	if(retVal == JNI_EDETACHED) {
		retVal = js_cb.jvm->AttachCurrentThread(&myEnv, NULL);
		if(retVal != JNI_OK) {
			return;
		}
		if(retVal == JNI_OK) {
			attached = true;
			retVal = js_cb.jvm->GetEnv((void**)&myEnv, JNI_VERSION_1_6);
			if(retVal != JNI_OK) {
				__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Failed to getEnv after attaching to JVM.");
			}
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Attached thread to JVM");
		}
	}
	else if(retVal == JNI_OK) {
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Already attached thread to JVM");
	}
	else if(retVal == JNI_EVERSION) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Wrong version of JNI to attach to JVM");
	}
	else if(retVal == JNI_ERR) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] JNI Error");
	}
	if(!myEnv) return;
	jstring jMessage = myEnv->NewStringUTF(message.c_str());
	jmethodID methodId = myEnv->GetMethodID(js_cb.jclazz, "peerConnectionStatus", "(Ljava/lang/String;J)V");
	jlong temp = 25;
	myEnv->CallVoidMethod(js_cb.jobj, methodId, jMessage, temp);
	if(attached) retVal = js_cb.jvm->DetachCurrentThread();
	if(retVal != JNI_OK && attached) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Failed to detach thread from JVM");
	}
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] remote session disconnected");
}

//Receiving the text data from the remote user and sending it to the Application
void sendMessageToApp( std::string message) {
	jniStruct js_cb = s_jni_struct;

	bool attached = false;
	if(!js_cb.jvm) return;
	JNIEnv *myEnv = NULL;
	int retVal = js_cb.jvm->GetEnv((void**)&myEnv, JNI_VERSION_1_6);
	if(retVal == JNI_EDETACHED) {
		retVal = js_cb.jvm->AttachCurrentThread(&myEnv, NULL);
		if(retVal != JNI_OK) {
			return;
		}
		if(retVal == JNI_OK) {
			attached = true;
			retVal = js_cb.jvm->GetEnv((void**)&myEnv, JNI_VERSION_1_6);
			if(retVal != JNI_OK) {
				__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Failed to getEnv after attaching to JVM.");
			}
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Attached thread to JVM");
		}
	}
	else if(retVal == JNI_OK) {
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Already attached thread to JVM");
	}
	else if(retVal == JNI_EVERSION) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Wrong version of JNI to attach to JVM");
	}
	else if(retVal == JNI_ERR) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] JNI Error");
	}
	if(!myEnv) return;

	jstring jMessage = myEnv->NewStringUTF(message.c_str());
	jmethodID methodId = myEnv->GetMethodID(js_cb.jclazz, "onReceiveMsg", "(Ljava/lang/String;)V");
		myEnv->CallVoidMethod(js_cb.jobj, methodId,  jMessage);
	if(attached) retVal = js_cb.jvm->DetachCurrentThread();
	if(retVal != JNI_OK && attached) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Failed to detach thread from JVM");
	}
}

//Thread which will receive the chat text provided by remote user

void recvChat() {


__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] onReceiveMsg sent");

	std::string local = "";
	char buffer[256] = {0};
	int bytesRead = recv(s_sock, buffer, sizeof(buffer)-1, 0);
	while(bytesRead > 0) {

		std::stringstream logdata;
		logdata << "[Nativechat] Chat Receive text :  invitation to: " << buffer;
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
		sendMessageToApp(buffer);

		if( buffer[bytesRead-1] == -1) {
			sendToJavaChat("Lost connection");
			break;
		}
		::memset(&buffer, 0, 256);
		bytesRead = recv(s_sock, buffer, sizeof(buffer)-1, 0);
	}

	if(bytesRead <= 0) {
		sendToJavaChat("Remote User left the conversation");

	}
	else {
		sendToJavaChat("Socket connection has been disconnected.");

	}


	s_sock = STC_INVALID_SOCKET;
}

// Function called when It is registered to  STCSetInviteCallback
//Functioned called When the connection handshake is completed and the application is now ready to communicate with the remote device
void CALLBACK onInviteCompleteCallback(PSTCInviteComplete message, PVOID callbackArg)
{

	std::stringstream logdata;
	logdata << "[Nativechat] inviteCompleteCallback :  invitation to: " << message->statusCode;
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
	// Creating socket only when statucode is INVITE_COMPLETE or INVITE_ACCEPTED
	if(message->statusCode == STC_INVITE_STATUS_INVITE_COMPLETE || message->statusCode == STC_INVITE_STATUS_INVITE_ACCEPTED) {
		STC_RESULT stcResult = STC_SUCCESS;
		if(STC_SUCCESS == (stcResult = STCConnectSocket(message->sdkHandle, &s_sock, message->hStream))) {

			std::thread mythread(recvChat);
			mythread.detach();
			logdata.str("");
			logdata << "Called STCConnectSocket() with: SockRet= " << s_sock << " sdkHandle= " << message->sdkHandle << " hStream= " << message->hStream;
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, std::string("[Nativechat] " + logdata.str()).c_str() );
		}
	}// end of Creating socket
	jniStruct js_cb = {0};
	js_cb = *((jniStruct*)callbackArg);
	bool attached = false;
	if(!js_cb.jvm) return;
	JNIEnv *myEnv = NULL;
	int retVal = js_cb.jvm->GetEnv((void**)&myEnv, JNI_VERSION_1_6);
	if(retVal == JNI_EDETACHED) {
		retVal = js_cb.jvm->AttachCurrentThread(&myEnv, NULL);
		if(retVal != JNI_OK) {
			return;
		}
		if(retVal == JNI_OK) {
			attached = true;
			retVal = js_cb.jvm->GetEnv((void**)&myEnv, JNI_VERSION_1_6);
			if(retVal != JNI_OK) {
				__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Failed to getEnv after attaching to JVM.");
			}
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Attached thread to JVM");
		}
	}
	else if(retVal == JNI_OK) {
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Already attached thread to JVM");
	}
	else if(retVal == JNI_EVERSION) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Wrong version of JNI to attach to JVM");
	}
	else if(retVal == JNI_ERR) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] JNI Error");
	}
	if(!myEnv) return;
	jstring jSessionId = myEnv->NewStringUTF(UuidToString(message->sessionId).c_str());
	jmethodID methodId = myEnv->GetMethodID(js_cb.jclazz, "peerConnectionStatus", "(Ljava/lang/String;J)V");
	myEnv->CallVoidMethod(js_cb.jobj, methodId, jSessionId, message->statusCode);
	if(attached) retVal = js_cb.jvm->DetachCurrentThread();
	if(retVal != JNI_OK && attached) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Failed to detach thread from JVM");
	}
			// Tell java land to go to chat view.
__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Returning from inviteCompleteCallback()");

}


void CALLBACK onStreamEventUpdateCallback(PSTCStreamEvent message, PVOID callbackArg)
{
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Callback update streamEventUpdateCallback");
}

/*
 * Class:     com_intel_csdk_wrapper_JNIMediator
 * Method:    nativePeerInvitation
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_csdk_wrapper_JNIMediator_nativePeerInvitation
  (JNIEnv *env, jobject obj, jstring sessionId)
{
	std::stringstream logdata;
	const char* strUUID = (*env).GetStringUTFChars(sessionId, NULL);
	STC_RESULT stcResult = STC_SUCCESS;
	HSTCINVITE hInvite;
	GUID remoteSessionId;
	StringToUuid(strUUID, &remoteSessionId);
	GUID myApplicationId;
	StringToUuid(s_applicationId.c_str(), &myApplicationId);
	int timeout = 60;//60 sec

	logdata << "[Nativechat] Sending invitation to: " << strUUID;
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());

	char* myData = "NATIVE CHAT BLOB";
	stcResult = STCSendInviteRequestEx((STC_HANDLE)s_sdkHandle, &hInvite, remoteSessionId, myApplicationId, timeout, (BYTE*)myData, strlen(myData));
	if(stcResult == STC_SUCCESS) {
		logdata << "[Nativechat]  invitation Send Sucessfuly to : " << strUUID;
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
	}
	else
	{
		logdata << "[Nativechat]  invitation Send failed to : " <<strUUID<<"Return value : "<<stcResult;
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, logdata.str().c_str());
	}

	(env)->ReleaseStringUTFChars(sessionId, strUUID);
	return stcResult;
}


/*
 * Class:     com_intel_csdk_wrapper_JNIMediator
 * Method:    nativeInviteStatus
 * Signature: (Ljava/util/UUID;Z)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_csdk_wrapper_JNIMediator_nativeInviteStatus
  (JNIEnv *env, jobject obj,jstring string, jlong handle, jboolean IsconnectionStatus){
	std::stringstream logdata;
	STC_RESULT stcResult = STC_SUCCESS;
	HSTCINVITE hInvite = handle;
	stcResult = STCSendInviteResponse(s_sdkHandle,hInvite,IsconnectionStatus);
	if(stcResult == STC_SUCCESS)
	{
	logdata << "[Nativechat]  STCSendInviteResponse  Return value : "<<stcResult;
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
	}else
	{
		logdata << "[Nativechat]  STCSendInviteResponse  failed Return value "<<stcResult;
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, logdata.str().c_str());
	}
}


/*
 * Class:     com_intel_csdk_wrappjlonger_JNIMediator
 * Method:    nativeSendMsg
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_csdk_wrapper_JNIMediator_nativeSendMsg
  (JNIEnv *env, jobject obj, jstring chattext)
{
	std::stringstream logdata;
	const char* strMessage = (*env).GetStringUTFChars(chattext, NULL);
	std::string messageChat = strMessage;
	int sent = 0;
	sent = send( s_sock, messageChat.c_str(), (int)strlen(messageChat.c_str())+1, 0);

	if(sent == -1) {
		logdata << "[Nativechat]  Error when trying to send bytes   Return value : "<<sent;
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, logdata.str().c_str());
		return sent ;
	}
	logdata << "[Nativechat]  Message Send : "<< messageChat;
	__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, logdata.str().c_str());
	(env)->ReleaseStringUTFChars(chattext, strMessage);
	return sent;
}

JNIEXPORT jlong JNICALL Java_com_intel_csdk_wrapper_JNIMediator_nativeDisconnectPeer
  (JNIEnv *env, jobject obj, jobject jobj){

	std::stringstream logdata;
	int retval = shutdown(s_sock,SHUT_RDWR);
	__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "CLosing the socket connection");
	logdata << "[Nativechat]  CLosing the socket connection  Return value : "<<retval;
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());

	s_sock = STC_INVALID_SOCKET;
}
//Register the function which will call to notify the change in application and its status of the remote devices which are connected.
JNIEXPORT jlong JNICALL Java_com_intel_csdk_wrapper_JNIMediator_nativeRegisterDiscovery(){
	int stcResult= STC_SUCCESS;
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] calling  STCSetSessionUpdateCallback");
	stcResult = STCSetSessionUpdateCallback(s_sdkHandle, onPeerUpdateCallback , (PVOID)&s_jni_struct);

	if(stcResult==STC_SUCCESS)
	{
		//Register the function which will call to notify the Updates the status of nodes created,joined or removed.
		stcResult =STCSetDiscoveryNodeUpdateCallback(s_sdkHandle, onNodeUpdate,(PVOID)&s_jni_struct);
	}
	if(stcResult==STC_SUCCESS)
	{
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Registering Discovery Success");
	}else
	{
		std::stringstream logdata;
		 logdata << "[Nativechat] STCSetSessionUpdateCallback  Fail  hResult:  "<< stcResult;
		 __android_log_write(ANDROID_LOG_ERROR, CSDK_TAG,logdata.str().c_str() );

	}
	return stcResult;
}
//Register the function which will called when ever Invite is recived from the remote devices
//Register the function which will be called when connection handshake is completed & application is now ready to communicate with the remote device.
JNIEXPORT jlong JNICALL Java_com_intel_csdk_wrapper_JNIMediator_nativeRegisterCommunication()
{
	int stcResult= STC_SUCCESS;
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Calling STCListenForInvites");
	stcResult = STCListenForInvites(s_sdkHandle, onInviteRequestCallback, (PVOID)&s_jni_struct, STC_ACCEPT_MANY);

	if(stcResult == STC_SUCCESS)
	{
	 __android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Simplechat_C.cpp] Calling STCSetInviteCallback");
		stcResult = STCSetInviteCallback(s_sdkHandle, onInviteCompleteCallback, (PVOID)&s_jni_struct);
	}

	if(stcResult == STC_SUCCESS)
	{
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Simplechat_C.cpp] Calling STCSetStreamEventCallback");
		stcResult = STCSetStreamEventCallback(s_sdkHandle, onStreamEventUpdateCallback, (PVOID)&s_jni_struct);

	}


	if(stcResult==STC_SUCCESS)
	{
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Registering Communication Success");
	}else
	{
		std::stringstream logdata;
		 logdata << "[Nativechat] STCSetSessionUpdateCallback  Fail  hResult:  "<< stcResult;
		 __android_log_write(ANDROID_LOG_ERROR, CSDK_TAG,logdata.str().c_str() );

	}
	return stcResult;
}
void NodePublishStatus(int publishtype,std::string  Nodename)
{
	jniStruct js_cb = s_jni_struct;
	bool attached = false;
	if(!js_cb.jvm) return;
	JNIEnv *myEnv = NULL;
	int retVal = js_cb.jvm->GetEnv((void**)&myEnv, JNI_VERSION_1_6);
	if(retVal == JNI_EDETACHED) {
		retVal = js_cb.jvm->AttachCurrentThread(&myEnv, NULL);
		if(retVal != JNI_OK) {
			return;
		}
		if(retVal == JNI_OK) {
			attached = true;
			retVal = js_cb.jvm->GetEnv((void**)&myEnv, JNI_VERSION_1_6);
			if(retVal != JNI_OK) {
				__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Failed to getEnv after attaching to JVM.");
			}
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] NodePublishStatus  Attached thread to JVM");
		}
	}
	else if(retVal == JNI_OK) {
		__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Already attached thread to JVM");
	}
	else if(retVal == JNI_EVERSION) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Wrong version of JNI to attach to JVM");
	}
	else if(retVal == JNI_ERR) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] JNI Error");
	}
	if(!myEnv) return;
	jstring jMessage = myEnv->NewStringUTF(Nodename.c_str());
	jmethodID methodId = myEnv->GetMethodID(js_cb.jclazz, "nodeStatusUpdates", "(Ljava/lang/String;I)V");

	myEnv->CallVoidMethod(js_cb.jobj, methodId, jMessage, publishtype);
	if(attached) retVal = js_cb.jvm->DetachCurrentThread();
	if(retVal != JNI_OK && attached) {
		__android_log_write(ANDROID_LOG_ERROR, CSDK_TAG, "[Nativechat] Failed to detach thread from JVM");
	}
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, "[Nativechat] Send nodeStatusUpdates to Android");

}
void JoinNode(std::string  Nodename)
{
	std::stringstream logdata;
	int stcResult= STC_SUCCESS;
	DWORD ServiceStatus;
	stcResult = STCQueryDiscoveryNodeServiceStatus(s_sdkHandle, &ServiceStatus);
	if(stcResult == S_OK)
	{
		if(ServiceStatus==STC_SERVICESTATUS_SERVICEONLINE)
		{
			DWORD SubscriptionResult =0 ;
			STCDiscoveryNodeCredentials nodedetails={0};
			GUID myApplicationId;
			StringToUuid(s_applicationId.c_str(), &myApplicationId);
			nodedetails.nodeFlags = STC_NODE_TYPE_PUBLISH;
			nodedetails.applicationId = myApplicationId;
//			const char* nodeName = (*env).GetStringUTFChars(node, NULL); //Nodename
			strcpy(nodedetails.data,Nodename.c_str());
			logdata << "[Nativechat]  Cloud Service is online --> Joining node ---------->1 :  "<<nodedetails.data ;
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());

			stcResult = STCJoinDiscoveryNode(s_sdkHandle, &nodedetails,&SubscriptionResult);
			logdata << "[Nativechat]  Cloud Service is online --> Joining node ---------->2 :  "<<nodedetails.data ;
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
			if(stcResult)
			{
				if(SubscriptionResult != STC_SUBSCRIPTIONRESULT_SUBSCRIPTIONCHANGED)
				{
					logdata << "[Nativechat]  Node Subscription failed  SubscriptionResult:  "<< SubscriptionResult;
					__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
					return ;
				}
				else
				{
					logdata << "[Nativechat]  Node Subscription Sucess:  "<< Nodename.c_str();
					__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
					return ;
				}

			}else
			{
				logdata << "[Nativechat] STCJoinDiscoveryNode fails :  "<< stcResult;
				__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());

			}

		}else
		{
			logdata << "[Nativechat]  Cloud Service is Failed:  "<< ServiceStatus;
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
		}
	}
}
//Function called when it is registered to STCSetDiscoveryNodeUpdateCallback()
// Gets the information update over the Node Creating,Subscribing,Publishing,Deleting over the cloud
void CALLBACK onNodeUpdate(PSTCDiscoveryNodeCredentialsUpdate Update, PVOID callbackArg)
{
	std::stringstream logdata;
	 logdata << "[Nativechat] onNodeUpdate:  The node  "<< Update->discoveryNodeCredentials.data<<"  the lasterror:"<<Update->lastError<<" The satus :"<<Update->status;
	__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());

	switch(Update->lastError)
		{
			 case STC_NODE_ERROR_NOERROR:
			 {
				switch(Update->status)
				{

					case STC_DISCOVERYNODESTATUS_PUBLISHED :
						{// Add the node name into the list
							char Nodename[1024];
							strcpy(Nodename,Update->discoveryNodeCredentials.data);
							std::string strNodename(Nodename);
							NodePublishStatus(STC_DISCOVERYNODESTATUS_PUBLISHED,strNodename);
							return;

						}

					case STC_DISCOVERYNODESTATUS_DELETED :
						{
							char Nodename[1024];
							strcpy(Nodename,Update->discoveryNodeCredentials.data);
							std::string strNodename(Nodename);
						    NodePublishStatus(STC_DISCOVERYNODESTATUS_DELETED,strNodename);
							break;
						}

				}//End of switch Update->status

				break;
			 }
			 case STC_NODE_ERROR_NODEEXISTS:
				 {
//					 CString msg;
//					 msg.Format(L" The node  %s trying to be created already exists.",convertFromUTF8(Update->discoveryNodeCredentials.data).c_str());
//					 ::MessageBox(Local_Hwnd_dlg,msg,L"File Transfer",MB_OK);
					 // Removing the Node from the list
					 logdata << "[Nativechat]  The node  "<< Update->discoveryNodeCredentials.data<<"  created already : Please join the node";
					__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());

					 char Nodename[1024];
					 strcpy(Nodename,Update->discoveryNodeCredentials.data);
					 JoinNode(Nodename);
					 break;
				 }
			 case STC_NODE_ERROR_NODENOTFOUND:
				 {
//					 CString msg;
//					 msg.Format(L" The node  %s  does not exist.Please create the node",convertFromUTF8(Update->discoveryNodeCredentials.data).c_str());
//					 ::MessageBox(Local_Hwnd_dlg,msg,L"File Transfer",MB_OK);


					 logdata << "[Nativechat]  The node  "<< Update->discoveryNodeCredentials.data<<"  doesnt exist Please create the node";
					 __android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
					 // Removing the Node from the list
					 break;
				 }
			 case STC_NODE_ERROR_INSUFFICIENTPRIVILEGES://Insufficient privileges.
			 case STC_NODE_ERROR_INTERNALERROR:// The process performed on the node has experienced an internal error. If the problem persists, please contact a member of the CCF team.
			 case STC_NODE_ERROR_UNKNOWNERROR ://The process performed on the node has experienced an unknown error. If the problem persists, please contact a member of the CCF team.
				 break;
		}

}



JNIEXPORT jint JNICALL Java_com_intel_csdk_wrapper_JNIMediator_nativeConnectNode
  (JNIEnv *env, jobject obj, jstring node, jboolean visible){
	std::stringstream logdata;
	int stcResult= STC_SUCCESS;
	DWORD ServiceStatus;

	stcResult = STCQueryDiscoveryNodeServiceStatus(s_sdkHandle, &ServiceStatus);
	if(stcResult == S_OK)
	{
		if(ServiceStatus==STC_SERVICESTATUS_SERVICEONLINE)
		{

			STCDiscoveryNodeCredentials nodedetails={0};
			GUID myApplicationId;
			StringToUuid(s_applicationId.c_str(), &myApplicationId);
			nodedetails.nodeFlags = STC_NODE_TYPE_PUBLISH;
			nodedetails.applicationId = myApplicationId;
			const char* nodeName = (*env).GetStringUTFChars(node, NULL); //Nodename
			strcpy(nodedetails.data,nodeName);
			logdata << "[Nativechat]  Cloud Service is online --> Creating node "<<nodeName;
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
			DWORD SubscriptionResult ;
			stcResult = STCCreateDiscoveryNode(s_sdkHandle, &nodedetails,&SubscriptionResult);
			if(stcResult)
			{
				if(SubscriptionResult != STC_SUBSCRIPTIONRESULT_SUBSCRIPTIONCHANGED)
				{
					logdata << "[Nativechat]  Node Subscription failed  SubscriptionResult:  "<< SubscriptionResult;
					__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
					return SubscriptionResult;
				}
				else
				{
					logdata << "[Nativechat]  Node Subscription Sucess:  "<< nodeName;
					__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
					return STC_SUBSCRIPTIONRESULT_SUBSCRIPTIONCHANGED;
				}

			}

		}else
		{
			logdata << "[Nativechat]  Cloud Service is Failed:  "<< ServiceStatus;
			__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
		}
	}
	return STC_SUBSCRIPTIONRESULT_FAILED;

}

JNIEXPORT jint JNICALL Java_com_intel_csdk_wrapper_JNIMediator_nativeDisconnectNode
  (JNIEnv *env, jobject obj, jstring node){
	std::stringstream logdata;
		int stcResult= STC_SUCCESS;
		DWORD ServiceStatus;

		stcResult = STCQueryDiscoveryNodeServiceStatus(s_sdkHandle, &ServiceStatus);
		if(stcResult == S_OK)
		{
			if(ServiceStatus==STC_SERVICESTATUS_SERVICEONLINE)
			{

				STCDiscoveryNodeCredentials nodedetails={0};
				GUID myApplicationId;
				StringToUuid(s_applicationId.c_str(), &myApplicationId);
				nodedetails.nodeFlags = STC_NODE_TYPE_PUBLISH;
				nodedetails.applicationId = myApplicationId;
				const char* nodeName = (*env).GetStringUTFChars(node, NULL); //Nodename
				strcpy(nodedetails.data,nodeName);
				logdata << "[Nativechat]  Cloud Service is online --> Leaving node "<<nodeName;
				__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
				DWORD SubscriptionResult ;
				stcResult = STCLeaveDiscoveryNode(s_sdkHandle, &nodedetails,&SubscriptionResult);
				if(stcResult)
				{
					if(SubscriptionResult != STC_SUBSCRIPTIONRESULT_SUBSCRIPTIONCHANGED)
					{
						logdata << "[Nativechat]  Node Subscription failed  SubscriptionResult:  "<< SubscriptionResult;
						__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
						return SubscriptionResult;
					}
					else
					{
						logdata << "[Nativechat]  Node Subscription Sucess:  "<< nodeName;
						__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
						return STC_SUBSCRIPTIONRESULT_SUBSCRIPTIONCHANGED;
					}

				}

			}else
			{
				logdata << "[Nativechat]  Cloud Service is Failed:  "<< ServiceStatus;
				__android_log_write(ANDROID_LOG_INFO, CSDK_TAG, logdata.str().c_str());
			}
		}
		return STC_SUBSCRIPTIONRESULT_FAILED;

}

JNIEXPORT jlong JNICALL Java_com_intel_csdk_wrapper_JNIMediator_nativeQueryCloudStatus(){
	int stcResult= STC_SUCCESS;
	DWORD ServiceStatus;
	stcResult = STCQueryDiscoveryNodeServiceStatus(s_sdkHandle, &ServiceStatus);
	return ServiceStatus;
}
