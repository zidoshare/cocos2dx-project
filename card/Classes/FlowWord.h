#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
USING_NS_CC;

class FlowWord : public Node
{
public:
	FlowWord();
	~FlowWord();
	virtual bool init();
	CREATE_FUNC(FlowWord);
	void close();
	void setTime(float t);
	TargetedAction* setWord(std::string, Color3B,Point);
private:
	ui::Text* text;
	MoveBy* flow;
	FadeOut* disappear;
	float time;
};

