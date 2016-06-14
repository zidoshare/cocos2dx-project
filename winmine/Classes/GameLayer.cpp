#include "GameLayer.h"
#include "Mine.h"
#include "ErrorLayer.h"
#include <iostream>
#include "MyList.h"
#include "TimerLayer.h"
#include <stdlib.h>
#include <ctime>
#include "TouchLayer.h"
#include "OptionLayer.h"
#define tBoom 0.5/number
#define tFind 0.01
#define propx 13.5 / ((float)width)
#define propy 13.5 / ((float)height)
USING_NS_CC;

GameLayer::GameLayer() :x(0), y(0), width(0), height(0), number(0), isFirst(true)
{
}
GameLayer::GameLayer(int w, int h, int xx, int yy, int n)
:
x(xx),
y(yy),
width(w),
height(h),
number(n),
isFirst(true),
canFindCho(false),
isEnd(false),
now_Number(n),
chooser(1)
{
	dir[0] = 0;
	dir[1] = 1;
	dir[2] = 0;
	dir[3] = -1;
	dir[4] = 1;
	dir[5] = 0;
	dir[6] = -1;
	dir[7] = 0;
}

GameLayer::~GameLayer()
{
}
GameLayer* GameLayer::create(int w, int h, int x, int y, int n){
	GameLayer *pRet = new(std::nothrow) GameLayer(w, h, x, y, n);
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
bool GameLayer::init(){
	if (!Layer::init()){
		return false;
	}

	



	auto size = Director::getInstance()->getVisibleSize();
	auto bgimg = Sprite::create("res/back.jpg");
	bgimg->setPosition(size.width / 2, size.height / 2);
	//bgimg->setScale(0.8f);
	this->addChild(bgimg);

	

	start();

	return true;
}
void GameLayer::start(){
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			auto mine = Mine::create(j, i, 9, width, height);
			this->addChild(mine);
		}
	}
	cho = Sprite::create("res/mouse.png");
	cho->setAnchorPoint(Vec2(0.5, 0.5));
	cho->setScaleX(propx);
	cho->setScaleY(propy);
	cho->setVisible(false);
	cho->setGlobalZOrder(1);
	log("%.2f,%.2f", propx, propy);
	auto m = this->getChildByTag(0);
	cho->setPosition(Vec2(m->getContentSize().width*propx / 2 + m->getPositionX(), m->getContentSize().height*propy / 2 + m->getPositionY()));
	cho->setTag(-2);
	this->addChild(cho);
	now_Number = number;
	cx = cy = 0;
}
void GameLayer::changeCho(){
	canFindCho = canFindCho ? false : true;
	cho->setVisible(canFindCho);
}
void GameLayer::move(int dir){
	switch (dir)
	{
	case 1:
		if (cy + 1 < height){
			cy += 1;
			((Mine *)this->getChildByTag(cy*width + cx))->chooseIn();
		}
		break;
	case 2:
		if (cx + 1 < width){
			cx += 1;
			((Mine *)this->getChildByTag(cy*width + cx))->chooseIn();
		}
		break;
	case 3:
		if (cy - 1 >= 0){
			cy -= 1;
			((Mine *)this->getChildByTag(cy*width + cx))->chooseIn();
		}
		break;
	case 4:
		if (cx - 1 >= 0){
			cx -= 1;
			((Mine *)this->getChildByTag(cy*width + cx))->chooseIn();
		}
		break;
	default:
		break;
	}
}
//随机生成二维数组地图
bool GameLayer::createMap(){

	int dir[] = { 1, 0, -1, 0, 1, 1, -1, -1,
		0, 1, 0, -1, 1, -1, 1, -1 };
	try{
		map = new int*[height];
		for (int i = 0; i < height; i++){
			map[i] = new int[width];
		}
	}
	catch (std::bad_alloc& e)
	{
		((ErrorLayer*)this->getParent()->getChildByTag(4))->mallocError();
	}

	auto li = MyList::create(width * height);
	if (li == NULL){
		return false;
	}

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			map[i][j] = 0;
			if ((i - cy)*(i - cy) + (j - cx)*(j - cx) <= 2){
				continue;
			}

			/*if (i + 1 == cy || i - 1 == cy || j + 1 == cx || j - 1 == cx)
				continue;*/
			li->add(i, j);

		}
	}
	log("%d", li->getLength());
	int Xindex, Yindex;
	for (int i = 0; i < number; i++){
		srand((unsigned int)time(NULL));
		int ss = rand() % li->getLength();
		//log("%d:random = %d li->getLenght():%d", i, ss, li->getLength());
		Yindex = li->getX(ss);
		Xindex = li->getY(ss);
		map[Yindex][Xindex] = 11;
		for (int j = 0; j < 8; j++){
			int wx = Xindex + dir[j];
			int wy = Yindex + dir[j + 8];
			if (wx < 0 || wx >= width || wy < 0 || wy >= height)
				continue;
			if (map[wy][wx] >= 0 && map[wy][wx] < 9)
				map[wy][wx]++;
		}
		li->front(ss);
	}
	s = queue::create();
	que = queue::create();
	return true;
}

void GameLayer::setChooser(int val){
	this->chooser = val;
}

void GameLayer::open(){

	auto m = (Mine *)this->getChildByTag(cy*width + cx);
	if (m->getValue() != 9)
		return;
	if (chooser != 1){
		m->open(chooser);
		if (chooser == 2){
			auto timerLayer = (TimerLayer *)this->getParent()->getChildByTag(1);
			timerLayer->changeMine(--now_Number);
		}
		return;
	}
		
	if (isFirst){
		auto timerLayer = (TimerLayer *)this->getParent()->getChildByTag(1);
		timerLayer->start();
		createMap();
		isFirst = false;
	}
	m->setValue(map[cy][cx]);
	m->open(chooser);

	if (map[cy][cx] == 0){
		find();
	}
	else if (map[cy][cx] == 11){
		auto timerLayer = (TimerLayer *)this->getParent()->getChildByTag(1);
		timerLayer->stop();
		auto touchLayer = (TouchLayer *)this->getParent()->getChildByTag(2);
		touchLayer->Enable(false);
		m->boom();
		findBoom();
	}

}
void GameLayer::setCxCy(int xx, int yy){
	cx = xx;
	cy = yy;
	((Mine *)this->getChildByTag(cy*width + cx))->chooseIn();
}
void GameLayer::find(){

	p = new list_value();
	p->x = cx;
	p->y = cy;
	s->push(p);//第一个元素入队列


	while (1){
		p = s->pop();
		for (int i = 0; i < 4; i++){
			int dx = p->x + dir[i];
			int dy = p->y + dir[i + 4];
			if (dx < 0 || dx >= width || dy < 0 || dy >= height || map[dy][dx] == -1 || map[dy][dx] == 11)
				continue;
			auto qq = new list_value();
			qq->x = dx;
			qq->y = dy;
			qq->value = map[dy][dx];
			
			auto m = (Mine *)this->getChildByTag(dy*width + dx);
			if (m->getFlag() != 1)
				continue;
			m->setValue(qq->value);

			que->push(qq);
			if (map[dy][dx] == 0){
				map[dy][dx] = -1;
				auto q = new list_value();
				q->x = dx;
				q->y = dy;

				s->push(q);
			}

			map[dy][dx] = -1;
		}

		if (s->queueEmpty()){
			s->destroyQueue();
			delete p;
			break;
		}
	}
	schedule(schedule_selector(GameLayer::timerHandler), tFind);
}
int GameLayer::getMapValue(int x, int y){
	return map[x][y];
}
void GameLayer::menuCallback(Ref *pSender){
	MenuItemSprite *item = (MenuItemSprite*)pSender;
	int nTag = item->getTag();

	if (nTag == -3){
		restart();
	}
	else if (nTag == -4){

	}

}
int GameLayer::getWidth(){
	return width;
}
int GameLayer::getHeight(){
	return height;
}
void GameLayer::restartWidthValue(int w,int h,int n){
	isFirst = true;
	//s->clearQueue();
	//que->clearQueue();
	if (this->width == w&&this->height == h){
		restartWidthNumber(n);
		return;
	}
	
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			auto m = ((Mine *)this->getChildByTag(i*width + j));
			m->removeFromParent();
		}
	}
	
	this->height = h;
	this->width = w;
	this->number = n;
	cho->setScaleX(propx);
	cho->setScaleY(propy);
	now_Number = number;
	auto timerLayer = (TimerLayer *)this->getParent()->getChildByTag(1);
	timerLayer->reset(number);
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			auto mine = Mine::create(j, i, 9, width, height);
			this->addChild(mine);
		}
	}
	auto m = this->getChildByTag(0);
	cho->setPosition(Vec2(m->getContentSize().width*propx / 2 + m->getPositionX(), m->getContentSize().height*propy / 2 + m->getPositionY()));

}
void GameLayer::restartWidthNumber(int n){

	this->number = n;
	restart();
}
void GameLayer::restart(){
	isFirst = true;
	unschedule(schedule_selector(GameLayer::timerHandler));
	auto touchLayer = (TouchLayer *)this->getParent()->getChildByTag(2);
	touchLayer->Enable(true);
	log("%d %d", width, height);
	now_Number = number;
	auto timerLayer = (TimerLayer *)this->getParent()->getChildByTag(1);
	timerLayer->reset(number);
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			auto m = ((Mine *)this->getChildByTag(i*width + j));
			m->setValue(9);
			m->resetFlag();
			m->open(1);
		}
	}
}

void GameLayer::timerHandler(float dt){


	auto val = que->pop();
	if (val == NULL)
		return;
	auto m = (Mine *)this->getChildByTag(val->y*width + val->x);
	
	if (isEnd)
		m->boom();
	else
		m->open(1);
	if (que->queueEmpty()){
		que->destroyQueue();
		if (isEnd == true){
			auto op = (OptionLayer *)this->getParent()->getChildByTag(3);
			op->gameEnd();
			isEnd = false;
		}
		unschedule(schedule_selector(GameLayer::timerHandler));
	}


}
void GameLayer::findBoom(){
	p = new list_value();
	p->x = cx;
	p->y = cy;
	s->clearQueue();
	s->push(p);//第一个元素入队列
	que->clearQueue();
	isEnd = true;
	int i = 0;
	/*for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			log("====%d", map[i][j]);
		}
	}*/
	while (1){
		p = s->pop();
		
		for (int i = 0; i < 4; i++){
			int dx = p->x + dir[i];
			int dy = p->y + dir[i + 4];
			if (dx < 0 || dx >= width || dy < 0 || dy >= height || map[dy][dx] == -2)
				continue;
			auto m = (Mine *)this->getChildByTag(dy*width + dx);
			if (m->getFlag() != 1)
				continue;

			if (map[dy][dx] == 11){
				auto qq = new list_value();
				//log("====%d %d", dx, dy);
				qq->x = dx;
				qq->y = dy;
				qq->value = 11;
				que->push(qq);
			}
			map[dy][dx] = -2;
			auto q = new list_value();
			q->x = dx;
			q->y = dy;

			s->push(q);
		}

		if (s->queueEmpty()){
			s->destroyQueue();
			delete p;
			break;
		}
	}
	/*q = queue::create();
	_value = new list_value();
	_value->x = cx;
	_value->y = cy;
	q->push(_value);*/
	schedule(schedule_selector(GameLayer::timerHandler), tBoom);
}