#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
class OptionLayer
	:public cocos2d::Layer
{
public:
	OptionLayer();
	~OptionLayer();
	OptionLayer(int width,int height,int number,int csValue);
	bool init();
	
	void open();
	void close();
	void change(cocos2d::Ref * sender,cocos2d::extension::Control::EventType controlevent);
	void menuCallback(cocos2d::Ref *sender);
	void timerHandler(float dt);
	void gameEnd();
	void gameRestart();
	void gameExit();
	static OptionLayer *create(int,int,int,int);
	CREATE_FUNC(OptionLayer);
private:
	int width,isChanged;
	int height;
	int number;
	int csValue;
	cocos2d::LabelTTF* label,*numberLabel,*heightLabel,*widthLabel;
	int touchMethod;
	cocos2d::Size size;
	cocos2d::LabelTTF *lb;
	cocos2d::MenuItemLabel *opraterItem;
	cocos2d::extension::ControlSlider* cs;
	cocos2d::MenuItemSprite *chooserItem1, *chooserItem2, *chooserItem3;
	//cocos2d::MoveBy *opMove, *csMove;
	bool isOpen;
};

