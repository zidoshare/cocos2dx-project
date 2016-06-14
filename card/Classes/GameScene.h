#pragma once

#include "cocos2d.h"
#include "Card.h"
#include "OnTouchListener.h"
#include "Player.h"
#include "OnPlayerBehaviorChangeListener.h"
#include "DataManager.h"
#include "ActionCounter.h"
#include "OnActionEndListener.h"
#include "OnCardChangeListener.h"
USING_NS_CC;

class GameScene : public Layer,public OnTouchListener,public OnPlayerBehaviorChangeListener,public OnActionEndListener,public OnCardChangeListener
{
public:
	GameScene();
	~GameScene();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	void onGround(bool isOne);
	void gameStart();
	void call(float dt);
	Player* getPlayerById(int id);
	//通过位置得到卡牌。只能得到场上卡牌对象
	Card* getCardByLocation(int location);
	virtual bool onTouchBeganPoint(Point p);
	virtual void onTouchMovePoint(Point p);
	virtual void onTouchEndedPoint(Point p);

	virtual void onTackCard(int,bool,int);
	virtual void onDisCard(int cardId, int location);
	virtual void onRecoveryCard(int);
	virtual void calc(int pId);
	virtual int* getOtherCards();
	virtual ActionCounter* getActionCounter();

	virtual void onDie(Card* c);

	Vector<Card*>& getCardsByPlayer(Player*);
	Vector<Card*>& getDeskCardsByPlayer(Player*);
	void eraseObjectByPlayerAndCard(Player*, Card*);
	Player* getReversePlayer(Player *);

	void pause(bool isPause);

	virtual void onActionEnd(int msg);
private:
	Point* myPoint;
	Point* otherPoint;
	int m_numForMine, m_numForOther;
	int counter;

	Vector<Card*> m_p1cards,m_p2cards;
	Vector<Card*> m_p1deskCards,m_p2deskcards;
	Card* onTouchCard;
	Point beginPoint;
	Card* removeCardNeedDelay;
	Card* needToListenCard;
	bool isOnTack;
	
	Sprite* lattice[12];
	DataManager* m_dataManager;

	Sprite* back1, *back2;
	ActionCounter* m_actionCounter;

	Player *p1, *p2;
	Menu* btn;
};

