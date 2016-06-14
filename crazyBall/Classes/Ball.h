#ifndef __BALL_H__
#define __BALL_H__
#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;
class Ball :public Entity{
public:
	Ball();
	Ball(Vec2 position, Vect impulse);
	~Ball();
	virtual bool init();
	CREATE_FUNC(Ball);
	static Ball* createBall(Vec2 position, Vect velocity);
	void setImpulse(Vect impulse);
	void bindSprite(Sprite* sprite);
protected:
	virtual void initPhysics();
private:
	Vec2 position;
	float radius;
	Vect velocity;
};
#endif