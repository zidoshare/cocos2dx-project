#pragma once
#include "cocos2d.h"
class TimerLayer
	:public cocos2d::Layer
{
public:
	TimerLayer();
	~TimerLayer();
	bool init();
	void timerHandler(float dt);
	void changeMine(int number);
	void stop();
	CREATE_FUNC(TimerLayer);
	void reset(int number);
	void start();
private:
	int t;
};

