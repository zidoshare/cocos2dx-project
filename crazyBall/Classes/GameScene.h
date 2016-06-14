#pragma once
#include "cocos2d.h"
#include "Ball.h"
#include "Apron.h"
#include "ApronManager.h"
USING_NS_CC;

class GameScene : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameScene); 
	static Scene* createScene();
	void update(float ft);
	void pause();
	void start();
	void stop();
protected:
	void moveSlidePlate(float x,float y);
private:
	void initBall();
	void initBoundEdge();
	void initSlidePlate();
	void initTouchListener();
	void initTopAprons();
	bool checkGameIsOver();
	bool checkGameIsFinish();
	Ball *ball;
	Apron *slidePlate;
	Vec2 movePostion;
	ApronManager *apronManager;
	Vector<Apron*> aprons;
};