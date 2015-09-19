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

import java.util.UUID;

public class Peer  implements Comparable<Peer>{
	private String _sessionName;
	private byte[] _avatar;
	private String _sessionId;
	private UUID[] _appList;
	private boolean _availability;
	private boolean _availability_cloud;
	private boolean _availability_proximity;
	
	Peer(String sessionName, byte[] avatar, String sessionId, UUID[] appList, boolean availability, boolean isAvailableCloud, boolean isAvailableProximity) {
		_sessionName = sessionName;
		_avatar = avatar;
		_sessionId = sessionId;
		_appList = appList;
		_availability = availability;
		_availability_cloud = isAvailableCloud;
		_availability_proximity = isAvailableProximity;
	}
	
	Peer(String sessionName, String sessionId, boolean availability, boolean isAvailableCloud, boolean isAvailableProximity) {
		_sessionName = sessionName;
		_avatar = null;
		_sessionId = sessionId;
		_appList = null;
		_availability = availability;
		_availability_cloud = isAvailableCloud;
		_availability_proximity = isAvailableProximity;
	}
	
	public String getName() {
		return _sessionName;
	}
	public byte[] getAvatar() {
		return _avatar;
	}
	public String getSessionId() {
		return _sessionId;
	}
	public UUID[] getAppList() {
		return _appList;
	}
	@Override
	public int compareTo(Peer o) {
		return getSessionId().compareTo(o.getSessionId());
	}
	public boolean getAvailability() {
		return _availability;
	}
	public boolean isAvailableCloud(){
		return _availability_cloud;
	}
	public boolean isAvailableProximity(){
		return _availability_proximity;
	}
}
