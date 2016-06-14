#pragma once

#include "cocos2d.h"
USING_NS_CC;

class DataManager : public Node
{
public:
	DataManager();
	~DataManager();
	void readData(); 
	virtual bool init();
	CREATE_FUNC(DataManager);
	//通过id 得到牌的四项数据，hp、attack、mana、range，返回一个数组
	int* getCardDataById(int id); 
	//通过id得到hp
	int getCardHpById(int id);
	//通过id得到attack
	int getCardAttackById(int id);
	//通过id得到mana
	int getCardManaById(int id);
	//通过id得到射程
	int getCardRangeById(int id);
private:
	ValueVector hps,attacks,manas,ranges;
};