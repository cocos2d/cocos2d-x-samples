package com.cocobox.library.floatwindow;

/**
 * 
 * <br></br>
 * @author bofeng_song
 * @date 2013-2-22 下午4:56:36
 * @version 1.0
 */
public interface TouchEventListener {
	public void onMove(int x, int y);
	public void onDown( int x, int y);
	public void onUp(int x, int y);
}
