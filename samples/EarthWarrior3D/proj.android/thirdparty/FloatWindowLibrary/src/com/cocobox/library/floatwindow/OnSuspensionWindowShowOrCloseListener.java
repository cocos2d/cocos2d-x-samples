package com.cocobox.library.floatwindow;


/**
 * 
 * <br>悬浮窗显示和关闭事件监听器</br>
 * @author zhangjunfei
 * @date 2013-11-19 下午3:38:42
 * @version 1.0
 */
public interface OnSuspensionWindowShowOrCloseListener {

	/**
	 * 悬浮窗显示时的回调
	 */
	public void onSuspensionWindowShow();

	/**
	 * 悬浮窗关闭时的回调
	 */
	public void onSuspensionWindowClose();
}
