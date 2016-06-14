#pragma once
#include "cocos2d.h"
class ErrorLayer
	:public cocos2d::Layer
{
public:
	ErrorLayer();
	~ErrorLayer();
	void mallocError();
	CREATE_FUNC(ErrorLayer);
private:
	virtual bool init();
	

};

