#pragma once

#include "cocos2d.h"

USING_NS_CC;

class GameControl : public Node
{
public:
	GameControl();
	~GameControl();
	virtual bool init(); 
	CREATE_FUNC(GameControl);
private:

};