#pragma once
#include "ActionCounter.h"
USING_NS_CC;

class OnPlayerBehaviorChangeListener{
public :
	//两个player都会使用，所以需要添加一个判断是否是自己的标志
	virtual void onTackCard(int,bool,int) = 0;
	virtual void onDisCard(int cardId,int location) = 0;
	virtual void onRecoveryCard(int) = 0;
	//计算回合结束后的行为
	virtual void calc(int pId) = 0;
	//得到场上卡牌的数组
	virtual int* getOtherCards() = 0;
	virtual ActionCounter* getActionCounter() = 0;
};