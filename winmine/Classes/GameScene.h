#pragma once
#include "cocos2d.h"

class GameScene
	:public cocos2d::Scene
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();

};

