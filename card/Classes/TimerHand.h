#pragma once

#include "cocos2d.h"

USING_NS_CC;

class TimerHand : public Node{
public:
	CREATE_FUNC(TimerHand);
	virtual bool init();
	virtual void update(float dt);
	void setTimer(bool func(int , int ), int x1, int x2,float delay);
	void setTimer(void func(int ), int,float delay);
	void setTimer(void func(),float delay);
private :
	int timeNow;
};