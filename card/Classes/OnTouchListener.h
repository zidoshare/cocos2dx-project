#pragma once
#include "cocos2d.h"
USING_NS_CC;
class OnTouchListener
{
public:
	virtual bool onTouchBeganPoint(Point p) = 0;
	virtual void onTouchMovePoint(Point p) = 0;
	virtual void onTouchEndedPoint(Point p) = 0;

private:

};