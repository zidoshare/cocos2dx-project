#pragma once
#include "cocos2d.h"
class TouchLayer
	:public cocos2d::Layer
{
public:
	TouchLayer();
	~TouchLayer();
	bool init();
	CREATE_FUNC(TouchLayer);
	void changeC(float c);//改变灵敏度
	void changeListener();
	void Enable(bool );
	int getTouchMethod();
	void changeTouchMeThod();
private:
	float xstart, ystart, xend, yend,w;
	int hasMove;
	float c;//灵敏度
	int touchx;
	cocos2d::EventListenerTouchOneByOne *listener1, *listener2;
	bool enable;
	
};

