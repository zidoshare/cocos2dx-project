#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Entity : public Node
{
public :
	Entity();
	~Entity();
	static const int BALL = 0xffffff;
	virtual bool init();
	/*
		继承此类的类应该实现给定一个position，将Entity设置为这个position
		绑定图案,此函数中已经设置sprite的位置为Entity所在的位置。
		不再在其他的地方设置sprite的位置
	*/
	virtual void bindSprite(Sprite* sprite);
	//获得图案
	virtual Sprite* getSprite();
	virtual void setId(int id){ this->id = id; };
	virtual int getId(){ return id; };
private:
	Sprite* m_sprite;
	//标识符
	int id;
};