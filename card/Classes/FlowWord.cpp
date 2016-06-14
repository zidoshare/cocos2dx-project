#include "FlowWord.h"

FlowWord::FlowWord()
{
}

FlowWord::~FlowWord()
{
}
bool FlowWord::init(){
	this->setVisible(false);
	time = 0.5f;
	return true;
}
void FlowWord::close(){
	this->removeFromParent();
}
void FlowWord::setTime(float t){
	time = t;
}
TargetedAction* FlowWord::setWord(std::string s, Color3B color,Point p){
	auto cf0 = CallFunc::create([this](){
		setVisible(true);
	});
	flow = MoveBy::create(time, Vec2(-30, 50));
	disappear = FadeOut::create(time);
	auto cf = CallFunc::create([this](){
		this->removeFromParent();
	});
	Spawn* sp = Spawn::create(cf0, flow, disappear, NULL);

	text = ui::Text::create();
	text->setFontName("fonts/arial.ttf");
	text->setFontSize(30.0f);
	text->setVisible(true);
	text->setText(s);
	text->setColor(color);
	text->setPosition(p);

	this->addChild(text);

	auto seq = Sequence::create(sp, cf, NULL);
	return TargetedAction::create(text, seq);
	//text->runAction(seq);
}