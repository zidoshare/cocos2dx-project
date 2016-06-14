#include "TimerLayer.h"
USING_NS_CC;

TimerLayer::TimerLayer()
:t(1)
{
}


TimerLayer::~TimerLayer()
{
}
bool TimerLayer::init(){
	auto size = Director::getInstance()->getVisibleSize();

	auto label = LabelBMFont::create("time:0", "fonts/futura-48.fnt", 30.0f);
	label->setPosition(Vec2(size.width * 0.1, size.height * 0.1));
	addChild(label);
	label->setAnchorPoint(Vec2(0, 0));
	label->setTag(1);

	auto label1 = LabelBMFont::create("mine:0", "fonts/futura-48.fnt", 30.0f);
	label1->setAnchorPoint(Vec2(0, 0));
	label1->setPosition(Vec2(size.width * 0.7, size.height * 0.1));
	addChild(label1);
	label1->setTag(2);
	


	return true;
}
void TimerLayer::timerHandler(float dt){
	char str[20];
	sprintf(str, "time:%d", ++t);
	auto m = (LabelBMFont *)this->getChildByTag(1);
	m->setString(str);
}
void TimerLayer::stop(){
	unschedule(schedule_selector(TimerLayer::timerHandler));
}
void TimerLayer::changeMine(int number){
	char str[20];
	sprintf(str, "mine:%d",number);
	log("number = %d", number);
	auto m = (LabelBMFont *)this->getChildByTag(2);
	m->setString(str);
}
void TimerLayer::reset(int number){
	stop();
	changeMine(number);
	t = 1;
	auto m = (LabelBMFont *)this->getChildByTag(1);
	m->setString("time:0");
}
void TimerLayer::start(){
	auto m = (LabelBMFont *)this->getChildByTag(1);
	m->setString("time:1");
	schedule(schedule_selector(TimerLayer::timerHandler), 1.0f);
}