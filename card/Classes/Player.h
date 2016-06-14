#pragma once

#include "cocos2d.h"
#include "TouchLayer.h"
#include "DataManager.h"
#include "OnPlayerBehaviorChangeListener.h"
#include "FlowWord.h"
#include "ActionCounter.h"
#include "OnActionEndListener.h"

USING_NS_CC;

#define tttime 2.0f

class Player : public Node,public OnActionEndListener
{
public:
	Player();
	~Player();
	virtual bool init();
	CREATE_FUNC(Player);

	virtual void onActionEnd();

	//读取牌组
	void readCards(); 
	//写入牌组
	void writeCards(); 
	//牌组中加入新牌
	void addToCards(int id); 
	//初始化角色
	void initPlayer(); 
	//当设置id时，会初始化角色头像以及读取牌组
	void setId(int);
	void setDataManager(DataManager* d);
	void setOnPlayerBehaviorChangeListener(OnPlayerBehaviorChangeListener* opb);
	void setOnTouchListener(OnTouchListener* ot);
	void setMana(int mana);
	void groundEnd();
	void openAiControl();
	void setHp(int hp);
	//如果是己方，dir为1，否则为-1
	int getDir();
	int getId();
	void setIsDie(bool);
	bool getIsDie();
	void setTouchEnable(bool touch);
	void changeLocationCard(int from,int to);

	void groundStart();
	//抽牌
	void tackCard(); 
	//出牌
	bool disCard(int cardId,int location); 
	//无返回值的出牌函数
	void disCardHand(int cardId, int location);
	//回收卡牌
	void recoveryCard(int cardId); 
	void removeGroundCardsById(int id);
	
	//说话
	void say(std::string s);
	//设置是否是玩家自己
	void setIsMine(bool isMine);
	bool getIsMine();
	bool getIsPlaying();
	void setIsPlaying(bool );
	//执行决定 参数为 方法，牌id，位置
	void execute(int, int, int);

	//得到场上卡牌的数组
	int* getCardsOnGround();

	//改变血量
	void changeHp(int hp);
	void showDie();
	int minLocation, maxLocation;
private:
	Sprite* m_photo;
	int m_mana;
	int m_id;
	int m_hp;
	bool m_isMine;//是否是玩家自己
	bool isDie;
	
	bool isPlaying;
	int dir;

	ValueVector cards; //角色拥有的牌组

	ValueVector cardsOnHand; //角色手上的卡牌
	
	//ValueVector cardsOnGround_location;//角色场上的卡牌位置
	//ValueVector cardsOnGround_id; //角色场上卡牌位置对应卡牌
	int* cardOnGround_id; //角色场上的卡牌

	LabelTTF* lb;
	LabelTTF* m_hpLabel;

	TouchLayer* m_touchLayer;
	DataManager* m_dataManager;
	OnPlayerBehaviorChangeListener* m_onPlayerBehaviorChangeListener;

	ActionCounter* m_actionCounter;
	void closeLabel(float dt);
};