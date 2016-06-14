#pragma once
#include "cocos2d.h"
#include "Apron.h"
#include "Constant.h"
USING_NS_CC;
class ApronManager : public Node
{
public:
	ApronManager();
	~ApronManager();
	virtual bool init(float height = Constant::OBSTACLE_CREATE_HEIGHT, float width = Constant::OBSTACLE_CREATE_WIDTH, 
		float ballWidth = Constant::BALL_WIDTH, float maxDifferenceWidth = Constant::MAX_DIFFERENCE_WIDTH, float maxDifferenceHeight = Constant::MAX_DIFFERENCE_HEIGHT, 
		float pointx = Constant::OBSTACLE_CREATE_BASICS_X, float pointy = Constant::OBSTACLE_CREATE_BASICS_Y);
	//随机生成挡板组，参数为转折点数目
	void generateApron(int pointNum);
	Vector<Apron*>& getAprons();
	static ApronManager* create(float height = Constant::OBSTACLE_CREATE_HEIGHT, float width = Constant::OBSTACLE_CREATE_WIDTH, 
		float ballWidth = Constant::BALL_WIDTH, float maxDifferenceWidth = Constant::MAX_DIFFERENCE_WIDTH, float maxDifferenceHeight = Constant::MAX_DIFFERENCE_HEIGHT, 
		float pointx = Constant::OBSTACLE_CREATE_BASICS_X, float pointy = Constant::OBSTACLE_CREATE_BASICS_Y);
protected:
	
private:
	Vector<Apron*> aprons;
	float height, width, ballWidth, pointx, pointy, maxDifferenceWidth, maxDifferenceHeight;
};