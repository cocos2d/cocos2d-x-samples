package com.cocobox.library.floatwindow;

import android.graphics.PixelFormat;
import android.graphics.Point;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.ViewConfiguration;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;


public class SuspensionWindow implements OnTouchListener {

	private static WindowManager mWm;
	
	protected WindowManager.LayoutParams mLayoutParams;

	protected WindowManager.LayoutParams mHideLayoutParams;
	
	private CustomOnClickListener mCustomOnClickListener;

	private TouchEventListener mTouchEventListener;


	private OnSuspensionWindowShowOrCloseListener mOnSuspensionShowOrCloseListener;

	/**
	 * 嵌入Window中的View
	 */
	protected View mContentView;

	protected int mTop;
	protected int mLeft;
	private int mWidth = WindowManager.LayoutParams.WRAP_CONTENT;
	private int mHeight = WindowManager.LayoutParams.WRAP_CONTENT;

	private float mStartX;
	private float mStartY;
	private float mTouchStartX;
	private float mTouchStartY;
	private float x;
	private float y;
	private int mTouchSlop;

	private boolean mVisible;
	
	private boolean mFocusable;
	private boolean mTouchable;
	private boolean mTouchableOutSide;
	
	private boolean mLongClickable = false;
	private boolean isFullScreen;	
	private boolean mSupportDragable;
	
	private int mGravity;

	static {
		mWm = (WindowManager) JoyFloatInterface.getContext().getSystemService("window");
		
	}

	SuspensionWindow() {
		//
	}

	/**
	 * 支持如下特性：
	 * 1、放置在屏幕左上角
	 * 2、自适应大小
	 * 3、可移动
	 * 4、获取焦点
	 * 5、悬浮窗区域外支持点击
	 * 6、获取touchable
	 * 7、非全屏
	 * 8、支持长按
	 * 
	 * @param view
	 */
	SuspensionWindow(View view) {
		this(view, 0, 0, WindowManager.LayoutParams.WRAP_CONTENT,
				WindowManager.LayoutParams.WRAP_CONTENT, true, true, true, true, false, true );
	}

	/**
	 * 支持如下铁性：
	 * 1、可移动
	 * 2、获取焦点
	 * 3、悬浮窗区域外支持点击
	 * 4、获取touchable
	 * 5、非全屏
	 * 6、支持长按
	 * @param view
	 * @param left
	 * @param top
	 */
	SuspensionWindow( View view, int left, int top ) {
		this(view, left, top, WindowManager.LayoutParams.WRAP_CONTENT,
				WindowManager.LayoutParams.WRAP_CONTENT, true, true, true, true, false, true );
	}
	
	/**
	 * 支持如下铁性：
	 * 1、可移动
	 * 2、获取焦点
	 * 3、悬浮窗区域外支持点击
	 * 4、获取touchable
	 * 5、非全屏
	 * 6、支持长按
	 * @param view
	 * @param left
	 * @param top
	 * @param width
	 * @param height
	 */
	SuspensionWindow( View view, int left, int top, int width, int height ) {
		this(view, left, top, width, height, true, true, true, true, false, true );
	}
	
	/**
	 * 支持如下铁性：
	 * 1、可移动
	 * 2、获取touchable
	 * 3、非全屏
	 * @param view
	 * @param left
	 * @param top
	 * @param width
	 * @param height
	 * @param focusable
	 * @param touchableOutside
	 */
	SuspensionWindow( View view, int left, int top, int width, int height, boolean focusable, boolean touchableOutside ) {
		this(view, left, top, width, height, focusable, true, touchableOutside, true, false, true );
	}
	
	/**
	 * 
	 * @param view
	 * @param left 	悬浮窗左上角x坐标
	 * @param top  	悬浮窗左上角y坐标	
	 * @param width		悬浮窗宽度
	 * @param height	悬浮窗高度		
	 * @param focusable	是否接收focus	true  接受  	false 不接受
	 * @param touchable	是否可触摸		true	可触摸		false 不能触摸
	 * @param touchableOutside	在悬浮窗外是否能接收touch事件 	true 悬浮窗外可接收touch事件	false 不接收
	 * @param moveable	是否可拖动	true	支持拖动	false	不支持拖动
	 * @param isFullScreen	是否全屏	true	支持全屏	false	不支持全屏
	 * @param supportLongClick 是否支持长按	true 支持		false	不支持
	 */
	SuspensionWindow(View view, int left, int top, int width,
			int height, boolean focusable, boolean touchable, boolean touchableOutside, boolean moveable, boolean isFullScreen, boolean supportLongClick ) {

		mContentView = view;
		
		mTop = top;
		mLeft = left;
		mWidth = width;
		mHeight = height;
		
		mFocusable = focusable;
		mTouchable = touchable;
		mTouchableOutSide = touchableOutside;
		
		mSupportDragable = moveable;
		this.isFullScreen = isFullScreen;
		mLongClickable = supportLongClick;
		init();
	}
	
	/**
	 * 显示悬浮船体
	 */
	public void show() {
		try {
			showView();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * 关闭悬浮窗体
	 */
	public void close() {
		try {
			mVisible = false;
			mWm.removeView( mContentView);
			if (mContentView instanceof OnSuspensionWindowShowOrCloseListener) {
				OnSuspensionWindowShowOrCloseListener listener = (OnSuspensionWindowShowOrCloseListener) mContentView;
				listener.onSuspensionWindowClose();
			}
			if (null != mOnSuspensionShowOrCloseListener) {
				mOnSuspensionShowOrCloseListener.onSuspensionWindowClose();
			}
			SuspensionWindowManager.getInstance().remove(this);
//			mContentView = null;
		} catch (Exception e) {
			//
		}
	}
	
	/**
	 * 隐藏悬浮窗体
	 */
	public void hide() {
		try {
			mVisible = false;
			mWm.removeView( mContentView);
			if (mContentView instanceof OnSuspensionWindowShowOrCloseListener) {
				OnSuspensionWindowShowOrCloseListener listener = (OnSuspensionWindowShowOrCloseListener) mContentView;
				listener.onSuspensionWindowClose();
			}
			if (null != mOnSuspensionShowOrCloseListener) {
				mOnSuspensionShowOrCloseListener.onSuspensionWindowClose();
			}
			SuspensionWindowManager.getInstance().remove(this);
		} catch (Exception e) {
			//
		}
	}

	
	public void update( int x, int y ) {
		mLeft = x;
		mTop = y;
		mLayoutParams.x = x;
		mLayoutParams.y = y;
		mWm.updateViewLayout(mContentView, mLayoutParams);
	}
	
	public void update( int x, int y, int nWidth, int nHeight ) {
		mLeft = x;
		mTop = y;
		mLayoutParams.x = x;
		mLayoutParams.y = y;
		mLayoutParams.width = nWidth;
		mLayoutParams.height = nHeight;
		mWidth = nWidth;
		mHeight = nHeight;
		
		mWm.updateViewLayout(mContentView, mLayoutParams);
	}

	public void update( int x, int y, int nWidth, int nHeight, boolean bFocus, boolean bTouchOutSide, boolean bTouchable, boolean bFullScreen ) {
		isFullScreen = bFullScreen;
		mTouchable = bTouchable;
		mFocusable = bFocus;
		mWidth = nWidth;
		mHeight = nHeight;

		mLayoutParams.width = mWidth;
		mLayoutParams.height = mHeight;
		
		if (isFullScreen) {
			mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_FULLSCREEN;
		} else {
			mLayoutParams.flags ^= WindowManager.LayoutParams.FLAG_FULLSCREEN;
		}
		
		if( bFocus ) {
			mLayoutParams.flags ^= LayoutParams.FLAG_NOT_FOCUSABLE;
		} else {
			mLayoutParams.flags |= LayoutParams.FLAG_NOT_FOCUSABLE;
		}
		
		if( bTouchable ) {
			mLayoutParams.flags ^= LayoutParams.FLAG_NOT_TOUCHABLE;
		} else {
			mLayoutParams.flags |= LayoutParams.FLAG_NOT_TOUCHABLE;
		}
		
		mWm.updateViewLayout(mContentView, mLayoutParams);
	}

	public void setCustomOnclickListener(CustomOnClickListener listener) {
		mCustomOnClickListener = listener;
	}

	public void setTouchEventListener(TouchEventListener listener) {
		mTouchEventListener = listener;
	}

	public Point getPosition() {
		Point pt = new Point();
		pt.x = mLayoutParams.x;
		pt.y = mLayoutParams.y;

		return pt;
	}

	/**
	 * 获取窗体中的root view
	 * 
	 * @return
	 */
	public View getRootView() {
		return mContentView;
	}

	public boolean isVisible() {
		return mVisible;
	}

	
	public void setShowOrCloseListener(
			OnSuspensionWindowShowOrCloseListener listener) {
		mOnSuspensionShowOrCloseListener = listener;
	}

	
	private void init() {
		final ViewConfiguration configuration = ViewConfiguration
				.get(JoyFloatInterface.getContext());
		mTouchSlop = configuration.getScaledTouchSlop();
		mGravity = -1;
	}
	
	private void setupParameters() {
		mLayoutParams = new WindowManager.LayoutParams();
		mLayoutParams.type = WindowManager.LayoutParams.TYPE_PHONE;
		
		if (isFullScreen) {
			mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_FULLSCREEN;
		}
		
		int width = mWm.getDefaultDisplay().getWidth();
		int height = mWm.getDefaultDisplay().getHeight();
		if( width > height ) {
			mLayoutParams.screenOrientation =android.content.pm.ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;
		} 
		
		if (!mFocusable) {
			mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;			
		}
		
		if( mTouchableOutSide ) {
			mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL;	
		}
		
		if( !mTouchable ) {
			mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE;
		}
		
		/**
		 * 允许窗体放置在屏幕外面
		 */
		mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS;
		
		if(-1 == mGravity) {
			mLayoutParams.gravity = Gravity.LEFT | Gravity.TOP;
		} else {
			mLayoutParams.gravity = mGravity;
		}
		
		mLayoutParams.x = mLeft;
		mLayoutParams.y = mTop;

		mLayoutParams.width = mWidth;
		mLayoutParams.height = mHeight;
		mLayoutParams.format = PixelFormat.TRANSPARENT;
	}


	@Override
	public boolean onTouch(View v, MotionEvent event) {
		// 获取相对屏幕的坐标，即以屏幕左上角为原点
		x = event.getRawX();
		y = event.getRawY(); // 25是系统状态栏的高�?

		switch (event.getAction()) {
		case MotionEvent.ACTION_DOWN:
			
			// 获取相对View的坐标，即以此View左上角为原点
			mTouchStartX = event.getX();
			mTouchStartY = event.getY();
			mStartX = x;
			mStartY = y;
			if (null != mTouchEventListener) {
				mTouchEventListener.onDown(
						(int) (event.getRawX() - mTouchStartX),
						(int) (event.getRawY() - mTouchStartY));
			}
			break;
		case MotionEvent.ACTION_MOVE:
			if (mSupportDragable && checkSuspendWindowMovable(event)) {
				updateViewPosition();
				if (null != mTouchEventListener) {
					mTouchEventListener.onMove(
							(int) (event.getRawX() - mTouchStartX),
							(int) (event.getRawY() - mTouchStartY));
				}
			}
			break;
		case MotionEvent.ACTION_UP:
			if (null != mTouchEventListener) {
				mTouchEventListener.onUp(
						(int) (event.getRawX() - mTouchStartX),
						(int) (event.getRawY() - mTouchStartY));
			}
			if( !checkSuspendWindowMovable(event) ) {
				if (null != mCustomOnClickListener)
					mCustomOnClickListener.onClick(v);
			}
			mTouchStartX = mTouchStartY = 0;
			mStartX = mStartY = 0;
			break;
		}
		if (mLongClickable) {
			return false;
		}
		return true;
	}
	
	private boolean checkSuspendWindowMovable(MotionEvent event) {
		int xDiff = (int) Math.abs(event.getRawX() - mStartX);
		int yDiff = (int) Math.abs(event.getRawY() - mStartY);
		boolean xMoved = xDiff > mTouchSlop;
		boolean yMoved = yDiff > mTouchSlop;
		return xMoved || yMoved;
	}

	protected void updateViewPosition() {
		try {
			// 更新浮动窗口位置参数
			mLayoutParams.x = (int) (x - mTouchStartX);
			mLayoutParams.y = (int) (y - mTouchStartY);
			mLeft = mLayoutParams.x;
			mTop = mLayoutParams.y;
			mWm.updateViewLayout(mContentView, mLayoutParams);
		} catch (Exception e) {

		}
	}

	private void showView() {
		mVisible = true;
		setupParameters();
		mWm.addView( mContentView, mLayoutParams);
		if (mSupportDragable) {
			mContentView.setOnTouchListener(this);
		}

		if (null != mOnSuspensionShowOrCloseListener) {
			mOnSuspensionShowOrCloseListener.onSuspensionWindowShow();
		}
		
		SuspensionWindowManager.getInstance().add(this);
		SuspensionWindowManager.getInstance().setCurrentSuspensionWindow(this);
	}

	@Override
	public boolean equals(Object o) {
		SuspensionWindow win = (SuspensionWindow) o;
		return mContentView == win.getRootView();
	}

	
	@Override
	public int hashCode() {
		// TODO Auto-generated method stub
		return super.hashCode();
	}
	
	public void setExtraParameters(int nGravity) {
		this.mGravity = nGravity;
	}
	
}
