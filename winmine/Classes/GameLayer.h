#pragma once
#include "cocos2d.h"
#include "stack.h"
#include "queue.h"
class GameLayer
	:public cocos2d::Layer
{
public:
	GameLayer();
	GameLayer(int w, int h, int xx, int yy, int n);
	~GameLayer();
	virtual bool init();
	static GameLayer* create(int w,int h,int x,int y,int n);
	bool createMap();
	void move(int i);
	void open();
	void find();
	int getMapValue(int x,int y);
	void menuCallback(cocos2d::Ref *pSender);
	void restart();
	void start();
	void timerHandler(float dt);
	void setCxCy(int x, int y);
	int getWidth();
	int getHeight();
	void changeCho();
	void findBoom();
	void setChooser(int val);
	void restartWidthValue(int,int,int);
	void restartWidthNumber(int);
private:
	int **map;
	int width, height, x, y, number,now_Number;
	int cx, cy,chooser;//chooser 打开方式 1：打开 2：插旗 3：问号
	bool isFirst,canFindCho,isEnd;
	//float propx,propy;//雷大小比例
	cocos2d::Sprite *cho;
	
	queue *s,*que;
	list_value* p;
	int dir[8];
};

