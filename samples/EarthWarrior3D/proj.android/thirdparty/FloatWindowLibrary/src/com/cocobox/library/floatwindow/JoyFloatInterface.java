package com.cocobox.library.floatwindow;

import android.content.Context;
import android.util.Log;
import android.view.View;


public final class JoyFloatInterface {
	
	private static JoyFloatInterface _instance;
	private Context mContext;
	
	private JoyFloatInterface() {
		
	}
	
	public static JoyFloatInterface instance() {
		if( null == _instance ) {
			_instance = new JoyFloatInterface();
		}
		return _instance;
	}
	
	public static void initialize( Context context ) {
		JoyFloatInterface instance = instance();
		instance.mContext = context;
	}
	
	public static SuspensionWindow newSuspensionWindow( View view ) {
		SuspensionWindow win = new SuspensionWindow( view );
		return win;
	}
	
	public static SuspensionWindow newSuspensionWindow( View view, int x, int y ) {
		SuspensionWindow win = new SuspensionWindow( view, x, y );
		return win;
	}
	
	public static SuspensionWindow newSuspensionWindow( View view, int x, int y, int width, int height ) {
		SuspensionWindow win = new SuspensionWindow( view, x, y, width, height );
		return win;
	}
	
	public static SuspensionWindow newSuspensionWindow( View view, int x, int y, int width, int height, boolean focusable, boolean touchableOutSide ) {
		SuspensionWindow win = new SuspensionWindow( view, x, y, width, height, focusable, touchableOutSide );
		return win;
	}
	
	public static SuspensionWindow newSuspensionWindow( View view, int x, int y, int width, int height, boolean focusable, boolean touchableOutSide, boolean touchable, boolean moveable, boolean isFullScreen, boolean supportLongClick ) {
		SuspensionWindow win = new SuspensionWindow( view, x, y, width, height, focusable,touchable, touchableOutSide, moveable, isFullScreen, supportLongClick );
		return win;
	}

	public static void back()
	{
		SuspensionWindowManager.getInstance().removeLastWindow();
		SuspensionWindowManager.getInstance().showCurSuspendWindow();
	}
	
	/**
	 * 关闭所有悬浮窗
	 */
	public static void closeAll() {
		SuspensionWindowManager.getInstance().clear();
	}
	
	/**
	 * 获取悬浮窗的个数
	 * @return
	 */
	public static int getCount() {
		return SuspensionWindowManager.getInstance().getCount();
	}
	
	public static Context getContext() {
		return instance().mContext;
	}
}
