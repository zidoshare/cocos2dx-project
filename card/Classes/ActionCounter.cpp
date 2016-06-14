#include "ActionCounter.h"

bool ActionCounter::init(){
	time = 0;
	index = 0;
	isAddToDelay = false;
	maxLog = 10;
	this->setZOrder(50);
	return true;
}
void ActionCounter::closeToDelay(){
	if (!delayVec.empty()){
		auto vec = delayVec;
		Spawn* sps;
		if (tVec.size() > index){
			auto action = tVec.at(index);
			
			sps = Spawn::create(action, Sequence::create(vec), NULL);

			time -= tVec.at(index)->getDuration();
			tVec.erase(index);
		}else
			sps = Spawn::create(vec);
		time += sps->getDuration();
		tVec.insert(index, sps);
	}
	delayVec.clear();
	isAddToDelay = false;
}
//注册动作
void ActionCounter::registAction(Node* node, FiniteTimeAction* f){
	registAction(TargetedAction::create(node, f));
	
}
void ActionCounter::registAction(FiniteTimeAction* t){
	if (isAddToDelay){
		delayVec.pushBack(t);
		return;
	}
	tVec.pushBack(t);
	time += t->getDuration();
	min_delay = -time;
}
//执行动作序列
void ActionCounter::run(int msg){
	tVec.pushBack(CallFunc::create([&,msg](){
		m_onActionEndListener->onActionEnd(msg);
	}));
	auto s = Sequence::create(tVec);
	tVec.clear();
	this->runAction(s);
}
//清空动作序列
void ActionCounter::clear(){
	tVec.clear();
}
float ActionCounter::getTime(){
	return time;
}
void ActionCounter::setOnActionEndListener(OnActionEndListener* o){
	m_onActionEndListener = o;
}
void ActionCounter::showLog(std::string s){
	auto fw = FlowWord::create();
	fw->setTime(3.0f);
	maxLog--;
	if (maxLog == 0){
		maxLog = 10;
	}
	this->addChild(fw);
	this->runAction(fw->setWord(s, Color3B::BLUE, Point(320, maxLog * 80)));
}