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
package org.cocos2dx.cpp;

import java.util.UUID;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Binder;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.util.Base64;
import android.util.Log;

import com.intel.csdk.listeners.P2PEventListener;
import com.intel.csdk.listeners.JNIListener;
import com.intel.csdk.wrapper.Connection;
import com.intel.csdk.wrapper.Initialization;
import com.intel.csdk.wrapper.Peer;

/**
 * This is a service class which will listen to wrapper classes like Initialization, Discovery,
 * and Connection module.
 * This service is responsible for following functionalities:
 * <P> Initializing the application.
 * <P> To register the discovery process and will discover other sessions.
 * <P> To register the connection process to communicate with other sessions.
 * <P>sending and receiving Invitation.
 * <P>Sending and receiving messages.
 * <p>
 * 
 */
public class ApplicationService extends Service implements JNIListener{

	private LocalBinder mBinder = new LocalBinder();
	private Handler mHandler;
	private static final String LOGC = "Helloccf";
	private Initialization mInitialize = null;
	SharedPreferences mPreference;
	private Connection mConnect = null;
	/**
	 * Binder class used to bind the service with Activity.
	 *
	 */
	public class LocalBinder extends Binder {
		ApplicationService getService() {
			// Return this instance of LocalService so clients can call public methods
			return ApplicationService.this;
		}
	}
	
	/*Service life cycle callback, on binding the service.*/
	@Override
	public IBinder onBind(Intent intent) {
		
		return mBinder;
	}
	
	/*This method will set the Hanlder passed through Activity.*/
	public void setHandler(Handler handle){
		mHandler = handle;
	}

	//To validate the user details saved in preference file.
	private boolean validatePreferences(){
		if(mPreference.contains("UserName") && mPreference.contains("DeviceName")){
		return true;
		}
		return false;
	}
	
	/**
	 * This method will pass the user details to Initialization wrapper.
	 */
	public void setUserDetails(){
		String userName = mPreference.getString("UserName", "No Data available");
		String deviceName = mPreference.getString("DeviceName", "No Data available");
		String temp = mPreference.getString("Avatar", "No Data available");
		byte[] avatar = Base64.decode(temp, Base64.DEFAULT);
		mInitialize.initialize("7A1B397B-B576-44C4-943F-1BEF4F490C07", "WqODOHahg3xw6WVB0BbTMi9yazTkBoQH", "i8wP2TGxoVjINdX7", userName, deviceName, avatar);
	}
	
	//To receive identity details from user by passing the event to activity,
	private void receiveInputFromUser(Initialization init){
		mPreference = getSharedPreferences(LOGC, Context.MODE_PRIVATE);
		
		if(validatePreferences()){
			setUserDetails();
		}else{
			Message msg = Message.obtain();
			msg.what = 0;
			mHandler.sendMessage(msg);
			Log.i(LOGC, "Showing dialog to receive input from user.");
		}
	}
	
	/**
	 * This method is used to initialize the Initialization wrapper
	 */
	public void intializeJNIPlatform(){
		if(mInitialize == null){
			mInitialize = new Initialization(getApplicationContext(),ApplicationService.this);
			receiveInputFromUser(mInitialize);
		}
	}

	@Override
	public void onPeerUpdated(Peer peer) {
		
		Log.i(LOGC, "onPeerUpdated: "+peer.getName());
		final UUID app_id = UUID.fromString("7A1B397B-B576-44C4-943F-1BEF4F490C07");
		for(UUID hasapp : peer.getAppList()){
			if(hasapp.compareTo(app_id)==0){
				if(peer.getAvailability()){
					//mPeerAdapter.add(peer);
				}else{
					//mPeerAdapter.remove(peer);
				}
				break;
			}
		}
		Message msg = Message.obtain();
		msg.what = 4;
		mHandler.sendMessage(msg);
	}
	
	public void invitePeer(Peer peer){
		Log.i(LOGC, "Inviting Peer: "+peer.getName());
		mConnect.requestP2PConnection(peer.getSessionId());
		Message msg = Message.obtain();
		msg.what = 2;
		mHandler.sendMessage(msg);
		mInviteHandler = new InviteHandler(peer, -1);
	}

	@Override
	public void onP2PConnectionStatus(Peer peer, long value) {
		
		if(peer!=null)
		Log.i(LOGC, "peer: "+peer.getName()+" Connection status: "+value);
		
		switch((int)value){
		
		case 10:
			//Invitation timeout
			Message msg10 = Message.obtain();
			msg10.what = 5;
			msg10.arg1 = 0;
			mHandler.sendMessage(msg10);
			break;
		case 12:
			//Invitation accepted.
			Message msg12 = Message.obtain();
			msg12.what = 3;
			mHandler.sendMessage(msg12);
			break;
		case 13:
			//Invitation rejected
			Message msg13 = Message.obtain();
			msg13.what = 5;
			msg13.arg1 = 1;
			mHandler.sendMessage(msg13);
			break;
		case 14:
			//Invitation completed.
			Message msg14 = Message.obtain();
			msg14.what = 3;
			mHandler.sendMessage(msg14);
			break;
		case 25:
			//Invitation disconnected
			if(mP2PListener!=null){
				mP2PListener.disconnectP2P();
			}
			break;
		
		}
		
	}

	@Override
	public void receiveP2PMessage(String msg) {
		Log.i(LOGC, "peer Msg: "+ msg);
		if(mP2PListener!=null){
			mP2PListener.P2PMessageUpdate(msg);
		}
	}

	@Override
	public void onP2PConnectionRequest(Peer peer, long handle) {
		mInviteHandler = new InviteHandler(peer, handle);
	}
	
	private InviteHandler mInviteHandler;
	private class InviteHandler{
		private Peer mPeer;
		private long mHandle;
		public InviteHandler(Peer peer, long handle) {
			mPeer = peer;
			mHandle = handle;
		}
		public long getConnectionHandle(){
			return mHandle;
		}
		public Peer getPeer(){
			return mPeer;
		}
	}
	
	public String getInviterDetails(){
		return mInviteHandler.getPeer().getName();
	}
	
	public void sendInviteResponse(boolean value){
		mConnect.notifyP2PRequestACK(mInviteHandler.getPeer(), mInviteHandler.getConnectionHandle(), value);
	}

	@Override
	public void onJNIStatusUpdate(JNIStatus status) {
		
		if(status.equals(JNIStatus.INITIALIZED)){
			mConnect = new Connection(mInitialize);
			mConnect.notifyRegisterCommunication();
			mConnect.notifyRegisterDiscovery();
		}
		
	}
	
	private P2PEventListener mP2PListener;
	public void setChatListener(P2PEventListener listener){
		mP2PListener = listener;
	}
	
	public void sendMsg2JNI(String msg){
		if(mConnect!=null){
			mConnect.sendP2PMessage(msg);
		}
	}
	
	public void disconnectConnection(){
		if(mConnect!=null && mInviteHandler!=null){
			mConnect.disconnectP2PConnection(mInviteHandler.getPeer());
		}
	}
}
