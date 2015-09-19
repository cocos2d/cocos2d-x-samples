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
package com.intel.csdk.adapter;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.graphics.BitmapFactory;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.cocos2dx.moon3d.ApplicationService;
import com.cocos2dx.moon3d.R;
import com.intel.csdk.wrapper.Peer;

/***
 * Manages the data from the service to show the session list.
 * <p>
 * This code shows use of the StcSession. How to get the name. How to get the avatar.
 * How to get the list of applications that the session has. c3 specific content is 
 * concentrated in the two methods getView and setNewSessionList.
 */
public class PeerAdapter extends BaseAdapter {

	public List<Peer> mPeerList = new ArrayList<Peer>();
	ApplicationService mService;

	public PeerAdapter(ApplicationService service) {
		mService = service;
	}
	
	/***
	 * Creates the view for one item in the list.
	 */
	@Override
	public View getView(int position, View convertView, ViewGroup parent) 
	{
		if (convertView == null) {
			
			LayoutInflater inflater = (LayoutInflater)parent.getContext()
					.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			convertView = inflater.inflate(R.layout.session_row, null);
		} else
			convertView.setVisibility(View.VISIBLE);

		Peer curSession = null;
		synchronized (mPeerList) {
			if (position >= 0 && position < mPeerList.size()) 
				curSession = (Peer)getItem(position);
		}
		
		if( curSession == null ) {
			convertView.setVisibility(View.GONE);
			return convertView;
		}

		// get the avatar from the session and put it into the image view
		ImageView avatar = (ImageView)convertView.findViewById(R.id.row_userAvatar);
		byte [] data = curSession.getAvatar();
		avatar.setImageBitmap(BitmapFactory.decodeByteArray(data, 0, data.length));

		// get the name from the session and put it into the text view
		TextView userName = (TextView)convertView.findViewById(R.id.row_userName);
		userName.setText(curSession.getName());
		
		ImageView cloudIcon = (ImageView)convertView.findViewById(R.id.row_userCloud);
		// Attach the cloud image,if user is discovered over the cloud.
		if(cloudIcon != null && curSession.isAvailableCloud()) {
			cloudIcon.setVisibility(View.VISIBLE);
		}
		else if(cloudIcon != null) {
			cloudIcon.setVisibility(View.GONE);
		}

		// setup a click handler to pass invites up to the service.
		final Peer session = curSession;
		convertView.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				mService.invitePeer(session);
			}
		});

		return convertView;
	}

	@Override
	public int getCount() 
	{
		synchronized(mPeerList) {
			return mPeerList.size();
		}
	}

	@Override
	public Object getItem(int position) 
	{
		synchronized(mPeerList) {
			if (mPeerList != null && position < mPeerList.size() && position >= 0)
				return mPeerList.get(position);
			else
				return null;
		}
	}

	@Override
	public long getItemId(int position) 
	{
		return position;
	}
	
	public void add(Peer peer) {
		synchronized (mPeerList) {
			for(int i=0; i<mPeerList.size(); i++) {
				if(mPeerList.get(i).compareTo(peer) == 0) {
					mPeerList.set(i, peer);
					return;
				}
			}
			mPeerList.add(peer);
		}
	}
	
	public void remove(Peer peer) {
		synchronized (mPeerList){
			for(int i=0; i<mPeerList.size(); i++) {
				if(mPeerList.get(i).compareTo(peer) == 0) {
					mPeerList.remove(i);
					break;
				}
			}
		}
	}

}