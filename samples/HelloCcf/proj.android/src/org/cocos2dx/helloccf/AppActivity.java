/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.helloccf;

import java.io.ByteArrayOutputStream;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Bitmap.CompressFormat;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.util.Base64;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import com.cocos2dx.helloccf.R;
import com.intel.csdk.listeners.P2PEventListener;
import com.intel.csdk.wrapper.Peer;

@SuppressLint("HandlerLeak")
public class AppActivity extends Cocos2dxActivity implements P2PEventListener {
	private String mServiceIntent = "org.cocos2dx.cpp.ApplicationService";
	private Handler mHandler = new MyHandler();
	private boolean isBound;
	private static final String LOGC = "Helloccf";
	private ApplicationServiceConnection mConnection = new ApplicationServiceConnection();
	private ApplicationService mService;
	private SharedPreferences mPreference;
	public static AppActivity sAppActivity = null;
	private Dialog inviteDialog	= null;

    @Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);		
		mPreference = getSharedPreferences(LOGC, Context.MODE_PRIVATE);
		startService(new Intent(mServiceIntent));		
		
		mPreference = getSharedPreferences("Helloccf", Context.MODE_PRIVATE);
		sAppActivity = this;
	}

    public Cocos2dxGLSurfaceView onCreateView() { 
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this); 
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8); 
    	return glSurfaceView; 
    	}

	@Override
	protected void onResume() {
		Log.i(LOGC, "resuming");
		doBindService();		
		super.onResume();
	}


	@Override
	protected void onPause() {
		Log.i(LOGC, "pausing");
		doUnbindService();		
		super.onPause();
	}
	
	/* private method to do the binding */
	private void doBindService() {
		if(!isBound)
		{
			Log.i(LOGC, "binding service");
			Intent servIntent = new Intent(mServiceIntent);
			isBound = bindService(servIntent, mConnection, 0);
			if( !isBound )
				Log.i(LOGC, "service did not bind.");
		}
	}

	/* private method to do the unbinding */
	private void doUnbindService() {
		if(isBound)
		{
			Log.i(LOGC, "unbinding service ");
			isBound = false;
			unbindService(mConnection);
		}
	}
	
	/***
	 * Must be called by the 'starting activity'. Can be called more than once, but
	 * should not be called anytime after 'shutdown' has been called.
	 */
	protected void doStartService() {
		Log.i(LOGC, "starting service");
		Intent servIntent = new Intent(mServiceIntent);
		startService(servIntent);		
	}
	
	/*** 
	 * Called to indicate that the application is finally existing.
	 */
	protected void doStopService() {
		Log.i(LOGC, "shutting down");
		Intent servIntent = new Intent(mServiceIntent);
		
		mConnection.serviceExited();
		doUnbindService();		
		stopService(servIntent);
	}
	
	@Override
	public void onBackPressed()
	{
		Log.i(LOGC, "back pressed");
		/*if(discoveryNodeFrag!=null){
			discoveryNodeFrag.removeAllDiscoveryNode();
		}*/
		finish();
		doStopService();
		super.onBackPressed();
	}
	
	//To save the users details in preference file.
	private void setPreferences(String userName, String deviceName, String avatar){
		Editor edit = mPreference.edit();
		edit.putString("UserName", userName);
		edit.putString("DeviceName", deviceName);
		edit.putString("Avatar", avatar);
		edit.commit();
		mService.setUserDetails();
		Log.i(LOGC, "Shared preference saved ");
	}	
	
	//Display dialog to input userName and Device Name from local user to complete unboxing process.
	private void completeUnboxing(){
		Log.i(LOGC, "Identity set up started ");
		
		final AlertDialog.Builder alert = new AlertDialog.Builder(this);
		alert.setTitle("Input your details:");
		alert.setCancelable(false);

		LayoutInflater inflater = (LayoutInflater)this.getApplicationContext()
				.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View parent = inflater.inflate(R.layout.unbox_layout, null);
		final EditText userName = (EditText)parent.findViewById(R.id.userName);
		userName.setText(android.os.Build.MANUFACTURER+" "+android.os.Build.MODEL);
		final EditText deviceName = (EditText)parent.findViewById(R.id.deviceName);
		deviceName.setText("Android "+ (isTablet(this)?"Tablet" : "Phone"));
		alert.setView(parent);
		
        alert.setPositiveButton("Save", new DialogInterface.OnClickListener() {
        public void onClick(DialogInterface dialog, int whichButton) {
        	String user = userName.getText().toString().trim();
        	String device = deviceName.getText().toString().trim();
        	
        	Bitmap bitmap = BitmapFactory.decodeResource(AppActivity.this.getResources(), R.drawable.generic_avatar50x50);
        	ByteArrayOutputStream bos = new ByteArrayOutputStream();
            bitmap.compress(CompressFormat.PNG, 0, bos);
            byte [] avatar = bos.toByteArray();
            String saveAvatar = Base64.encodeToString(avatar, Base64.DEFAULT);
            
            Log.i(LOGC, "User Input completed -----> ");
            
            setPreferences(user!=null && !user.equals("")?user:android.os.Build.MANUFACTURER+android.os.Build.MODEL,device!=null && !device.equals("")?device:"Android",saveAvatar);
          }
        });
        alert.show();
	}	
	
	//Validating device is a Tablet or Phone.
	private boolean isTablet(Context context) {  
        return (context.getResources().getConfiguration().screenLayout   
                & Configuration.SCREENLAYOUT_SIZE_MASK)    
                >= Configuration.SCREENLAYOUT_SIZE_LARGE; 
    }	
    
	/* ServiceConnection implementation to bind Service and Activity class*/
	public class ApplicationServiceConnection implements ServiceConnection
	{
		boolean serviceStopped = false;
		
		public void onServiceConnected(ComponentName className, IBinder binder) 
		{
			synchronized(this) {
				Log.i(LOGC, "service connected.");
				if(mService == null){
					mService = (ApplicationService)((ApplicationService.LocalBinder)binder).getService();
					mService.setHandler(mHandler);
					mService.intializeJNIPlatform();
					
					//FriendViewByCCF.getInstance().initInstance(AppActivity.this, mService);
					mService.setChatListener(AppActivity.this);
				}
			}
		}
	
		public void onServiceDisconnected(ComponentName className) 
		{
			Log.i(LOGC, "service disconnected.");
			mService.stopSelf();
		}
		
		public void serviceExited()
		{
			synchronized(this) {
				serviceStopped = true;
			}
		}
	}
	
	/**
	 * This handler class is used to handle Activity events.
	 *
	 */
	private class MyHandler extends Handler{
		@Override
		public void handleMessage(Message msg) {
			//if(msg.what !=4)	FriendViewByCCF.getInstance().hideWindow();
		
			super.handleMessage(msg);
		
			switch(msg.what){
			
			case 0:
				//Set your identity.
				completeUnboxing();
				break;
			case 1:
				//Invite received
				inviteAlert();
				break;
			case 2:
				//Send invitation
				inviteDialog = ProgressDialog.show(AppActivity.this, "", "Waiting for connection");
				break;
			case 3:
				//Sent invitation acknowledgment.
				if(inviteDialog!=null && inviteDialog.isShowing()){
					inviteDialog.dismiss();
				}
				
				break;
			case 5:
				//Invitation rejected or timeout
				if(inviteDialog!=null && inviteDialog.isShowing()){
					inviteDialog.dismiss();
					if(msg.arg1 == 0){
						Toast.makeText(AppActivity.this, "Invitation timeout!!", Toast.LENGTH_SHORT).show();
					}else{
						Toast.makeText(AppActivity.this, "Invitation rejected!!", Toast.LENGTH_SHORT).show();
					}
				}
				break;
			}			

		}
	}	
    
	//Invitation dialog to receive input from user
	private void inviteAlert(){
	final AlertDialog.Builder builder = new AlertDialog.Builder(this);
			
			mHandler.post(new Runnable() {
				
				public void run() {
					
					builder.setPositiveButton("Accept", new DialogInterface.OnClickListener() {
					           public void onClick(DialogInterface dialog, int id) {
					        	   mService.sendInviteResponse(true);
					           }
					       });
					builder.setNegativeButton("Ignore", new DialogInterface.OnClickListener() {
					           public void onClick(DialogInterface dialog, int id) {
					        	   mService.sendInviteResponse(false);
					           }
					       });
					
					builder.setTitle("Earth Warrior invite");
					builder.setMessage("Accept connection from "+mService.getInviterDetails()+" ?");
					builder.setCancelable(false);
					builder.show();
				}
			});
	}

	@Override
	public void P2PMessageUpdate(String msg) {
	}

	@Override
	public void disconnectP2P() {
	} 
	
    public static void invitePeer(Peer peer) {
		Log.i(LOGC, "invitePeer in AppActivity");
    	AppActivity.sAppActivity.mService.invitePeer(peer);
	}
	
    public static void sendInviteResponse(boolean value) {
		Log.i(LOGC, "invitePeer in sendInviteResponse");    	
		AppActivity.sAppActivity.mService.sendInviteResponse(value);		
	}
   
    public static void remoteDisconnectJni() {
		Log.i(LOGC, "invitePeer in remoteDisconnectJni");    	
		AppActivity.sAppActivity.mService.disconnectConnection();
	}  
    
    public static void sendMessage(String msg) {
		AppActivity.sAppActivity.mService.sendMsg2JNI(msg);
    }    
    
 
}
