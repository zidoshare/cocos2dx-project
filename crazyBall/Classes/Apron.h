#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "math.h"
#define PI 3.141592653
USING_NS_CC;
using namespace cocos2d::ui;
class Apron : public Entity
{
public:
	Apron();
	//默认宽度
	static const int DEFULT_WIDTH = 10.0f;
	//宽度，长度，位置，方向
	Apron(Point p, Vec2 dir, float length, float width,Point origin,Point destination);
	~Apron();
	static Apron* createApron(Point origin, Vec2 dir, float length, float width = Apron::DEFULT_WIDTH);
	static Apron* createApron(Point origin, Point destination, float width = Apron::DEFULT_WIDTH);
	virtual bool init();
	//衔接下一个apron.传入两个点
	void connect(Apron* ap);
	CREATE_FUNC(Apron);

	Point getDestination() const { return destination; }
	Point getOrigin() const { return origin; }
	cocos2d::Vec2 getDirection() const { return direction; }
	Point getMidPointPosition() const { return midPointPosition; }
	float getLength() const { return length; }
	float getWidth() const { return width; }
	void setVelocity(Vect velocity);
	
protected:
	virtual void initPhysics();
	void setDestination(Point val) { destination = val; }
	void setOrigin(Point val) { origin = val; }
	void setDirection(cocos2d::Vec2 val) { direction = val; }
	void setMidPointPosition(Point val) { midPointPosition = val; }
	void setLength(float val) { length = val; }
	void setWidth(float val) { width = val; }

private:
	Vec2* getContentPoints();
	DrawNode* _node;
	float width, length;
	Point midPointPosition;
	Vec2 direction;
	Point origin, destination;//起点终点
	Scale9Sprite* m_sprite;
};