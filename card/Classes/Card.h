#pragma once

#include "cocos2d.h"
#include "DataManager.h"
#include "FlowWord.h"
#include "Player.h"
#include "OnActionEndListener.h"
#include "ActionCounter.h"
typedef int Dir;
USING_NS_CC;

class Card : public Node
{
public:
	Card();
	~Card();
	virtual bool init();
	CREATE_FUNC(Card);

	//卡牌id为唯一身份标示，可能不同id对应同样参数的一张牌，但是并不是同一张牌
	void setId(int);
	void setHp(int);
	void setAttack(int);
	void setMana(int);
	void setSkillId(int);
	void setRange(int);
	void setDir(int );
	void setBack(bool);
	int getDir();
	void initCardWithDataManager(DataManager* dm,int id);
	int getId();
	int getHp();
	int getAttack();
	int getMana();
	int getSkillId();
	int getRange();
	void setDataManager(DataManager* dm);
	void setActionCounter(ActionCounter*);
	bool getIsDie();

	void setMsg(int hp, int attack, int mana, int range, int skillId); //统一一次性设置

	Sprite* getCardNode(); //得到卡牌的精灵

	//动作是注册的，需要Counter Run一次！！！！
	void showFly(Point p,float time = 0.2f);
	//动作是注册的，需要Counter Run一次！！！！
	void showMove(Point p,float time = 0);
	//动作是注册的，需要Counter Run一次！！！！
	void showDown(Point p,float time = 0.2f);
	//动作是注册的，需要Counter Run一次！！！！
	void showError();
	//动作是注册的，需要Counter Run一次！！！！
	void showAiMove(Point p);
	void showTack(float delay,Point p);
	//在attack中有加入伤害计算，被攻击的卡牌会反击（死亡不反击）
	void showAttack(Card* c,bool attackAble,Player* p);
	void showDefense();
	void showDie();
	void showBack(bool);
	
	void changeHp(int hp);
public :
	static const Dir up = 1,down = -1;
private:
	int m_id;
	int m_hp, m_attack, m_mana,m_range;
	int m_skillId;
	bool isDie,isBack;
	Dir m_dir;
	Sprite* m_sprite;
	DataManager* m_dataManager;
	ActionCounter* m_actionCounter;
	//卡牌上的画面
	Sprite* draw;
	Sprite* back;

	LabelTTF *m_hpLabel, *m_manaLabel, *m_attackLabel, *m_rangeLabel;
};

