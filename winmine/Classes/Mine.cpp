#include "Mine.h"
#include <iostream>
#include <string>
#include <stdio.h>
using namespace cocos2d;
using std::string;
using std::cout;
using std::endl;
#define boomTime 0.2
Mine::Mine() :x(0), y(0), value(0)
{
	
}
Mine::Mine(int a, int b, int c, int w, int h) : x(a), y(b), value(c), width(w), height(h), bb(1), flag(1)
{
	propx = (13.5 / ((float)w));
	propy = (13.5 / ((float)h));
}

Mine::~Mine()
{
}
Mine* Mine::create(int x, int y, int value,int width,int height){
	Mine *pRet = new(std::nothrow) Mine(x,y,value,width,height);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool Mine::init(){
	if (!Sprite::init()){
		return false;
	}
	
	

	open(1);

	//log("before:%.2f %.2f",this->getContentSize().width,this->getContentSize().width);
	
	//this->setContentSize(Size(this->getContentSize().width*prop,this->getContentSize().height*prop));
	//log("after:%.2f %.2f", this->getContentSize().width, this->getContentSize().width);
	//this->setAnchorPoint(Vec2(0,0));

	initPosition();

	//char str[20];
	this->setTag(y*width+x);
	/*sprintf(str, "%d*%d", x,y);
	
	auto label = LabelTTF::create(str,"Consolas",20);
	label->setAnchorPoint(Vec2(0,0));
	this->addChild(label);*/

	//scheduleUpdate();
	//this->boom();
	return true;
}
void Mine::setValue(int val){
	value = val;
}
void Mine::open(int val){
	if (!_enabel && val != 3)
		return;
	if (val == 1){
		char str[20];
		sprintf(str, "res/%d.jpg", value);
		this->initWithFile(str);
	}
	else if (val == 2){
		if (flag != 2){
			this->initWithFile("res/13.jpg");
			flag = 2;
		}
		else{
			flag = 1;
			this->initWithFile("res/9.jpg");
		}
		
	}
	else if (val == 3){
		if (flag != 3){
			this->initWithFile("res/14.jpg");
			flag = 3;
		}
		else{
			flag = 1;
			this->initWithFile("res/9.jpg");
		}
	}
		
	
	this->setScaleX(propx);
	this->setScaleY(propy);
	this->setAnchorPoint(Vec2(0,0));
	//initPosition();

}
void Mine::setEnable(bool enable){
	this->_enabel = enable;
}
void Mine::initWithMyNode(SpriteBatchNode *node){
	this->initWithTexture(node->getTexture());
	this->setScaleX(propx);
	this->setScaleY(propy);
	this->setAnchorPoint(Vec2(0, 0));
	initPosition();
}
int Mine::getValue(){
	
	return value;
}
void Mine::chooseIn(){
	((Sprite*)this->getParent()->getChildByTag(-2))->setPosition(
		Vec2(this->getContentSize().width*propx / 2 + this->getPositionX(), 
		this->getContentSize().height*propy / 2 + this->getPositionY()));
}
void Mine::update(float dt){
	bb += 0.01f;
	this->setScale(bb);
}
void Mine::initPosition(){

	auto size = Director::getInstance()->getVisibleSize();
	auto o = Director::getInstance()->getVisibleOrigin();

	float vx = size.width / 2;
	float vy = size.height / 2;

	float sx = this->getContentSize().width * propx * (float)width / 2;
	float sy = this->getContentSize().height * propy * (float)height / 2;
	this->setPosition(Vec2(vx - sx + x*this->getContentSize().width*propx, vy - sy + y * this->getContentSize().height*propy));

	/*float vy = size.height / 2;
	vy = vy - (this->getContentSize().height * height / 2);
	float vx = size.width / 2;
	vx = vx - (this->getContentSize().width * width / 2);
	this->setPosition(Vec2(x*this->getContentSize().width*(prop) + o.x + vx,this->getContentSize().height*y*(prop) + o.y +vy));*/
	if (x == 0 && y == 0)
		log("%f %f", this->getPositionX(), this->getPositionY());
}
void Mine::boom(){
	Vector<SpriteFrame*> vec;
	char name[15];
	memset(name, 0, 15);
	for (int i = 0; i < 11; i++){
		sprintf(name, "Boom%04d", i);
		vec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	Animation* animation = Animation::createWithSpriteFrames(vec, 0.05f);
	animate = Animate::create(animation);
	this->runAction(animate);
}
float Mine::getPropx(){
	return propx;
}
float Mine::getPropy(){
	return propy;
}
void Mine::timerHandler(float dt){

}
int Mine::getFlag(){
	return this->flag;
}
void Mine::resetFlag(){
	flag = 1;
}