#pragma once

#include "cocos2d.h"
#include "OnTouchListener.h"
USING_NS_CC;

class TouchLayer : public Layer
{
public:
	TouchLayer();
	~TouchLayer();
	virtual bool init();
	CREATE_FUNC(TouchLayer);
	void registeTouchEvent();
	void setOnTouchListener(OnTouchListener* ot);
	void setTouchEnable(bool enable);
private:
	EventListenerTouchOneByOne* _listener;
	OnTouchListener* m_onTouchListener;
};
