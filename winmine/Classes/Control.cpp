#include "Control.h"

#include "MyList.h"
#include <stdio.h>
using namespace std;
USING_NS_CC;

Control::Control() :x(0), y(0), width(0), height(0), number(0)
{
}


Control::~Control()
{
}
//控制层或者场景的函数

//进入游戏函数 加入游戏层、计时器层、按钮层、触摸层
void Control::start(){

	readOption();

	/*auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/boom.plist");
	char str[20];
	for (int i = 0; i < 23; i++){
		sprintf(str, "res/%d.jpg", i);
		cache->addSpriteFramesWithFile(str);
	}
	cache->addSpriteFramesWithFile("res/14_normal.png");
	cache->addSpriteFramesWithFile("res/14_selector.png");
	cache->addSpriteFramesWithFile("res/end.png");
	cache->addSpriteFramesWithFile("res/end_s.png");
	cache->addSpriteFramesWithFile("res/back.jpg");
	cache->addSpriteFramesWithFile("res/liter.png");
	cache->addSpriteFramesWithFile("res/liter_back.png");
	cache->addSpriteFramesWithFile("res/restart.png");
	cache->addSpriteFramesWithFile("res/restart_s.png");*/

	

	auto s = Director::getInstance()->getVisibleSize();
	scene = GameScene::create();

	
	gameLayer = GameLayer::create(width, height, x, y, number);
	touchLayer = TouchLayer::create();
	timerLayer = TimerLayer::create();
	
	optionLayer = OptionLayer::create(width,height,number,15);//在最上面区域，不遮挡touchLayer
	errorLayer = ErrorLayer::create();//在屏幕外面，有需要时进来

	
	
	scene->addChild(gameLayer);
	gameLayer->setTag(0);
	
	scene->addChild(timerLayer);
	timerLayer->setTag(1);
	timerLayer->changeMine(number);

	scene->addChild(touchLayer);
	touchLayer->setTag(2);

	scene->addChild(optionLayer);
	optionLayer->setTag(3);
	scene->addChild(errorLayer);
	errorLayer->setTag(4);

	
	Director::getInstance()->runWithScene(scene);
}

//重新开始函数
void Control::restart(){
}

//打开设置函数
void Control::openOption(){

	


}

//游戏结束时调用此函数函数
void Control::gameEnd(){
}

//数据控制的函数
//读取设置函数
void Control::readOption(){
	auto w = UserDefault::getInstance()->getStringForKey("width", "10");
	auto h = UserDefault::getInstance()->getStringForKey("height", "10");
	auto n = UserDefault::getInstance()->getStringForKey("number", "25");

	width = parseint(w.c_str());
	height = parseint(h.c_str());
	number = parseint(n.c_str());
	//调试代码
	/*width = 10;
	height =10;
	number = 50;*/
	x = 5;
	y = 5;

}

GameLayer* Control::getGameLayer(){
	return gameLayer;
}
TouchLayer* Control::getTouchLayer(){
	return touchLayer;
}
TimerLayer* Control::getTimerLayer(){
	return timerLayer;
}
OptionLayer* Control::getOptionLayer(){
	return optionLayer;
}
ErrorLayer* Control::getErrorLayer(){
	return errorLayer;
}
int Control::parseint(string s){
	int w = 0;
	for (int i = 0; i < s.length(); i++){
		w = w * 10 + s.at(i) - '0';
		log("%d", w);
	}
	return w;
}



