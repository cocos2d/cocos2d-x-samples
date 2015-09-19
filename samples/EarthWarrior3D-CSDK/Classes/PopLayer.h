//
//  PopLayer.h
//  HelloCcf
//  reference from http://www.zaojiahua.com/popscene.html
//  thanks to xiaota
//  Created by calf on 14-7-25.
//
//

#ifndef __HelloCcf__PopLayer__
#define __HelloCcf__PopLayer__

#include "cocos2d.h"

using namespace cocos2d;

class PopLayer : public Layer
{
public:
	static Scene * scene();
	bool init();
	CREATE_FUNC(PopLayer);
private:
	void yesButton(Ref *pSender);
	void noButton(Ref *pSender);
	void setTitle();
	void setContent();
	Size m_size;
	Sprite * m_bgSprite;
};

#endif /* defined(__HelloCcf__PopLayer__) */
