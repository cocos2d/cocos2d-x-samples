package com.cocos2dx.moon3d;

import com.cocos2dx.moon3d.R;
import com.cocobox.library.floatwindow.JoyFloatInterface;
import com.cocobox.library.floatwindow.SuspensionWindow;

import android.view.LayoutInflater;
import android.view.View;
import android.widget.ListView;
import android.widget.LinearLayout.LayoutParams;

public class FriendViewByCCF {
    private static FriendViewByCCF _instance = null;	
	ApplicationService applicationService;
    private SuspensionWindow mSuspensionWindow = null;
	
    public static FriendViewByCCF getInstance() {
    	if(null == _instance) {
    		_instance = new FriendViewByCCF();
    	}
    	
    	return _instance;
    }
    
    public void initInstance(AppActivity activity, ApplicationService service) {
    	
    	if(mSuspensionWindow != null) return;
    	
		JoyFloatInterface.initialize(activity);

		applicationService = service;

    	View view = LayoutInflater.from(activity).inflate(R.layout.select, null);

    	ListView lview = (ListView) view.findViewById(R.id.sessionListView);

		lview.setAdapter(service.getPeerAdapter());
				
		mSuspensionWindow = JoyFloatInterface.newSuspensionWindow(view, 0, 0, LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
	}    

	public void sessionListChanged() {	
		
		if (applicationService != null)
		{
			applicationService.getPeerAdapter().notifyDataSetChanged();
		}		
	}	
	
	public void showWindow() {
		if (null != mSuspensionWindow && mSuspensionWindow.isVisible())
			return;

		if (null != mSuspensionWindow && !mSuspensionWindow.isVisible())
		{
			mSuspensionWindow.show();
			return;		
		}		
	}

	public void hideWindow() {
		if (null == mSuspensionWindow || !mSuspensionWindow.isVisible())
			return;

		mSuspensionWindow.hide();;
	} 	
	
	public boolean isWindowVisible() {
    	if(null == mSuspensionWindow) {
    		return false;
    	}
    	
    	return mSuspensionWindow.isVisible();
    }	 	
}
