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
package com.intel.csdk.listeners;

import com.intel.csdk.wrapper.NodeStatus;
import com.intel.csdk.wrapper.Peer;

public interface JNIListener {

	public enum JNIStatus{
		INITIALIZED(0),
		DISCOVERED(1),
		CONNECTED(2),
		DISCONNECTED(3);
		
		private int i;
		JNIStatus(int i){
			this.i = i;
		}
		
		public int getJNIStatus(){
			return this.i;
		}
	};
	
//	public void onPeerUpdated(UUID peerID, String userName, String deviceName, byte [] avatar, boolean isSelf, boolean isAvailableCloud, boolean isAvailableProximity);
	public void onPeerUpdated(Peer peer);
	public void onP2PConnectionStatus(Peer peer, long value);
	public void receiveP2PMessage(String msg);
	public void onP2PConnectionRequest(Peer peer, long handle);
	public void onJNIStatusUpdate(JNIStatus status);
	public void onDiscoveryNodeStatus(NodeStatus status);
}
