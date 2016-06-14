#pragma once
#include "GameScene.h"
#include "GameLayer.h"
#include "OptionLayer.h"
#include "TouchLayer.h"
#include "TimerLayer.h"
#include "ErrorLayer.h"
#include "cocos2d.h"
#include <iostream>
class Control
{
public:
	Control();
	~Control();
	
	//控制层或者场景的函数
	void start();//进入游戏函数 加入游戏层、计时器层、按钮层、触摸层
	void restart();//重新开始函数
	void openOption();//打开设置函数
	void gameEnd();//游戏结束时调用此函数函数

	//数据控制的函数
	void readOption();//读取设置函数
	int** createMap();//随机生成二维数组地图
	static int parseint(std::string);
	GameLayer *getGameLayer();
	TouchLayer* getTouchLayer();
	TimerLayer* getTimerLayer();
	OptionLayer* getOptionLayer();
	ErrorLayer* getErrorLayer();
	int x, y, width, height, number;
private:
	GameLayer* gameLayer;
	TouchLayer* touchLayer;
	TimerLayer* timerLayer;
	OptionLayer* optionLayer;
	ErrorLayer* errorLayer;
	GameScene* scene;
};



