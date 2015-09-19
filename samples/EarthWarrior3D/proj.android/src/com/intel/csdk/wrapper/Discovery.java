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

import java.util.List;

import android.util.Log;

import com.intel.csdk.wrapper.Initialization.InitilizationStatus;

public class Discovery {
	
	private JNIMediator mJNI;
//	private Initialization mInit;
	private List<Peer> mPeerList;
	public Discovery(Initialization init) {
		if(init == null)
			return;
//		mInit = init;
		mJNI = init.getJNIReference();
	}

	public void startDiscovery(){
		if(mJNI.getInitializationStatus().equals(InitilizationStatus.SUCCESS)){
			long temp = mJNI.nativeRegisterDiscovery();
			Log.i("", "Discovery: "+temp);
		}
		else{
			//Throw exception, Please initialized before calling discovery.
		}
		
	}
	
	public List<Peer> getPeerList(){
		return mPeerList;
	}

	public void connectToNode(String node, boolean visible) {

		if(mJNI!=null){
			mJNI.nativeConnectNode(node, visible);
		}
	}
	
	public int queryCloudStatus(){
		int temp = -1;
		if(mJNI!=null){
			temp = mJNI.nativeQueryCloudStatus();
		}
		return temp;
	}
	
	public void disconnectFromNode(NodeStatus node){
		if(mJNI!=null){
			mJNI.nativeDisconnectNode(node.getNodeName());
		}
	}
}
