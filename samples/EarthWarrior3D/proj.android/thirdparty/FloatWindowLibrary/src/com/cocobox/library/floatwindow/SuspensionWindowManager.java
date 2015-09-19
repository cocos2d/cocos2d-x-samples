package com.cocobox.library.floatwindow;

import java.util.ArrayList;
import java.util.List;

final class SuspensionWindowManager {

	private SuspensionWindow mCurrentSuspendWindow;

	private ArrayList<SuspensionWindow> mListSuspensionWindow;
	
	private static SuspensionWindowManager _instance;
	
	private SuspensionWindowManager() {
		mListSuspensionWindow = new ArrayList<SuspensionWindow>();
	}
	
	static SuspensionWindowManager getInstance() {
		if( null == _instance ) {
			_instance = new SuspensionWindowManager();
		}
		return _instance;
	}
	
	
	/**
	 * 获取悬浮窗体数量
	 * @return
	 */
	public int getCount() {
		return mListSuspensionWindow.size();
	}
	
	public void clear() {
		List<SuspensionWindow> windows = new ArrayList<SuspensionWindow>(mListSuspensionWindow);

		for( SuspensionWindow win : windows ) {
			if( null == win ) continue;
			win.close();
		}
		mListSuspensionWindow.clear();
	}
	
	void add( SuspensionWindow win ) {
		if( null == win ) return;
		if( mListSuspensionWindow.contains( win ) ) return;
		mListSuspensionWindow.add( win );
	}
	
	void remove( SuspensionWindow win ) {
		mListSuspensionWindow.remove( win );
		if( mCurrentSuspendWindow == win ) {
			int cout = mListSuspensionWindow.size();
			if( cout > 0 ) {
				mCurrentSuspendWindow = mListSuspensionWindow.get( cout - 1 );
			} else {
				mCurrentSuspendWindow = null;
			}
		}
	}
	
	void setCurrentSuspensionWindow( SuspensionWindow win ) {
		mCurrentSuspendWindow = win;
	}
	
	void removeLastWindow() {
		if (mCurrentSuspendWindow != null)
		{
			mCurrentSuspendWindow.close();
		}
	}
	
	void showCurSuspendWindow()
	{
		if (mCurrentSuspendWindow != null)
		{
			mCurrentSuspendWindow.show();
		}
	}
}
