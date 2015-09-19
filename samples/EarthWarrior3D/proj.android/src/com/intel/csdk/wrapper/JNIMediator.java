/*
Copyright (c) 2011-2013, Intel Corporation

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
OF THE POSSIBILITY OF SUCH DAMAGE.
*/
package com.intel.csdk.wrapper;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;
import android.widget.Toast;

import com.intel.csdk.listeners.JNIListener;
import com.intel.csdk.listeners.JNIListener.JNIStatus;
import com.intel.csdk.wrapper.Initialization.InitilizationStatus;
import com.intel.stc.csdk.STCPlatform;

public class JNIMediator extends STCPlatform{

	private Context mContext;
	private JNIListener mListener = null;
	private static final String LOGC = "Moon3d";
	private String mAppId = null;
	private String mClientId = null;
	private String mClientSecret = null;
	private String mUserName = null;
	private String mDeviceName = null;
	private byte [] mAvatar = null;
	private SharedPreferences mPreference = null;
	private List<Peer> mPeerList = new ArrayList<Peer>();
	
	static {
		System.loadLibrary("AFE");
		System.loadLibrary("STC");
 		System.loadLibrary("stcapi");
		System.loadLibrary("stcjnimediator");
	}
	
	public native long nativeInit(String path, String app_id, String client_id,String client_secret);
	public native long nativeIdentity(String userName, String deviceName, byte[] avatar,int size);
	public native long nativeRegisterCommunication();
	public native long nativePeerInvitation(String peerID);
	public native long nativeInviteStatus(UUID peerID,long handle, boolean value);
	public native long nativeSendMsg(String msg);
	public native long nativeDisconnectPeer(UUID peerID);
	public native long nativeDestroyConnection();
	public native long nativeRegisterDiscovery();
	public native int nativeConnectNode(String node, boolean visible);
	public native int nativeQueryCloudStatus();
	public native int nativeDisconnectNode(String node);
	
	
	public JNIMediator(Context context, JNIListener listen){
		mContext = context;
		mListener = listen;
		
		if(mContext!=null)
			mPreference = mContext.getSharedPreferences("Moon3d", Context.MODE_PRIVATE);
	}
	
	void startSTCPlatform(String appId, String clientId,String clientSecret, String userName, String deviceName, byte [] avatar){
		mAppId = appId;
		mClientId = clientId;
		mClientSecret = clientSecret;
		mUserName = userName;
		mDeviceName = deviceName;
		mAvatar = avatar;
		this.start();
		Log.i(LOGC, "Starting STCPlatform to initialize the application with CSDK.");
	}
	public void onLocalPeerUpdates(UUID peerID, String userName, String deviceName, byte [] avatar, boolean isAvailableCloud, boolean isAvailableProximity){
		
	}
	
	public void onPeerDiscovery(String peerID, String userName, String deviceName, byte [] avatar,Object [] appList, boolean isAvailable, boolean isAvailableCloud, boolean isAvailableProximity){
	
		Log.i(LOGC, "sessionName: "+userName+ "sessionId: "+" availability: "+isAvailable+ "appList size: "+appList.length);
		UUID[] _appList = new UUID[appList.length];
		for(int i=0; i<appList.length; i++) {
			_appList[i] = UUID.fromString((String)appList[i]);
		}
		final Peer peer = new Peer(userName, avatar, peerID, _appList, isAvailable, isAvailableCloud, isAvailableProximity);
		
		if(peer.getAvailability()){
			add(peer);
		}else{
			remove(peer);
		}
		
		if(mListener!=null){
			mListener.onPeerUpdated(peer);
		}
		
	}
	
	private void add(Peer peer) {
		for(int i=0; i<mPeerList.size(); i++) {
			if(mPeerList.get(i).compareTo(peer) == 0) {
				mPeerList.set(i, peer);
				return;
			}
		}
		mPeerList.add(peer);
	}
	private void remove(Peer peer) {
		for(int i=0; i<mPeerList.size(); i++) {
			if(mPeerList.get(i).compareTo(peer) == 0) {
				mPeerList.remove(i);
				break;
			}
		}
		
	}
	
	public List<Peer> getPeerList(){
		return mPeerList;
	}
	
	public void onInvitationReceived(String peerID, long handle){
		
		Log.i(LOGC, "JNI onInviteReceived called peerID: "+peerID+" handle: "+handle);
		Peer peer = queryPeer(peerID);
		if(peer == null)
			return;
		Log.i(LOGC, "JNI onInviteReceived called by "+ mListener);
		if(mListener!=null){
			Log.i(LOGC, "JNI onInviteReceived called by "+peer.getName());
			mListener.onP2PConnectionRequest(peer, handle);
		}
	}
	
	private Peer queryPeer(String peerID){
		Peer peer = null;
		for(int i=0; i<mPeerList.size(); i++) {
			if(mPeerList.get(i).getSessionId().equals(peerID)) {
				peer = mPeerList.get(i);
				break;
			}
		}
		return peer;
	}
	
	public void peerConnectionStatus(String peerID, long value){
		
		Log.i(LOGC, "peerConnectionStatus ------"+value+peerID);
		Peer peer = queryPeer(peerID);
		/*if(peer == null)
			return;*/
		
		if(mListener!=null){
			mListener.onP2PConnectionStatus(peer, value);
		}
		
	}
	
	public void onReceiveMsg(String msg){
		Log.i(LOGC, "message received from JNI: "+msg);
		if(mListener!=null){
			mListener.receiveP2PMessage(msg);
		}
	}
	
	public void requestIdentityDetails(boolean value){
		Log.i("", "requestIdentityDetails started");
		if(value){
			Log.i(LOGC, "Setting user details...UserName: "+mUserName+" DeviceName: "+mDeviceName);
			long temp = nativeIdentity(mUserName, mDeviceName, mAvatar, mAvatar.length);
            
		}
	}
	@Override
	public void ProcessStarted(boolean value) {
		Log.i(LOGC, "ProcessStarted " + value);
		if(value){
			Log.i(LOGC, "ProcessStarted calling initialization----");
			long temp = nativeInit(mContext.getFilesDir().getAbsolutePath(), mAppId, mClientId, mClientSecret);
			Log.i(LOGC, "Initialization successful "+temp);
			if(temp==0)
				setInitializationStatus(InitilizationStatus.SUCCESS);
			Toast.makeText(mContext, "Intialization successful", Toast.LENGTH_SHORT).show();
			mListener.onJNIStatusUpdate(JNIStatus.INITIALIZED);
		}
	}
	
	@Override
	public Context getApplicationContext() {
		
		return mContext;
	}
	
	private InitilizationStatus mInitStatus;
	void setInitializationStatus(InitilizationStatus status){
		mInitStatus = status;
	}
	
	InitilizationStatus getInitializationStatus(){
		return mInitStatus;
	}
	
	public void nodeStatusUpdates(String node, int status){
		Log.i(LOGC, "Node: "+node+" status: "+status);
		if(mListener!=null){
			final NodeStatus temp = new NodeStatus(node, status);
			mListener.onDiscoveryNodeStatus(temp);
		}
	}
}
