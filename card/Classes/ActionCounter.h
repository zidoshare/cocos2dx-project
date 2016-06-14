#pragma once
#include "cocos2d.h"
#include "OnActionEndListener.h"
#include "FlowWord.h"
USING_NS_CC;

class ActionCounter :public Node{
public :
	static const int ontouch1 = 1, ontouch2 = 2, ontouch3 = 3, ontackcardend = 4, ongroundend = 5,oncalcend = 6,onaicontrolend = 7;
	virtual bool init();
	CREATE_FUNC(ActionCounter);
	void setOnActionEndListener(OnActionEndListener*);
	//注册动作
	void registAction(Node*, FiniteTimeAction*);
	//只能传入Target类型
	void registAction(FiniteTimeAction*);
	//执行动作序列
	void run(int msg);
	void closeToDelay();
	float getTime();
	void showLog(std::string s);
	//清空动作序列
	void clear();
private :
	Vector<FiniteTimeAction*> tVec;
	OnActionEndListener* m_onActionEndListener;
	Vector<FiniteTimeAction*> delayVec;

	float time;
	int index;
	float min_delay;
	bool isAddToDelay;
	int maxLog;
};