#pragma once 

#include "cocos2d.h"
#include "Player.h"
#include "Card.h"
USING_NS_CC;

class LogicControl : public Node
{
public:
	LogicControl();
	~LogicControl();
	virtual bool init();
	CREATE_FUNC(LogicControl);

	void checkCard(Card* c); //检查出牌是否是符合规则
	void recoveryCard(Card* c); //回收卡牌
	void setPlayer(Player* p);

private:
	Player* m_player;
	
};
