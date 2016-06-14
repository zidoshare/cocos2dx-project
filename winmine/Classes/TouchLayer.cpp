#include "TouchLayer.h"
#include "GameLayer.h"
#include "Mine.h"
USING_NS_CC;

TouchLayer::TouchLayer() :hasMove(0), c(2), enable(true), touchx(2)
{
}


TouchLayer::~TouchLayer()
{
}
bool TouchLayer::init(){
	/*auto size = this->getContentSize();
	
	this->setContentSize(Size(size.width,size.width));
	this->setPosition(Vec2(size.width/2,size.height / 2));
	this->setColor(Color3B::RED);*/
	auto size = Director::getInstance()->getVisibleSize();

	listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = [this,size](Touch *t, Event *e){
		if (!enable)
			return false;
		

		return true;
	};
	listener2->onTouchEnded = [=](Touch *t, Event* e){
		this->xstart = t->getLocation().x;
		this->ystart = t->getLocation().y;
		if (this->ystart >size.height / 10 * 9)
			return;
		if (this->ystart < size.height / 10)
			return;
		auto pos = this->getParent()->getChildByTag(0)->getChildByTag(0)->getPosition();
		auto m = (Mine *)this->getParent()->getChildByTag(0)->getChildByTag(0);
		auto csize = Size(m->getContentSize().width * m->getPropx(), m->getContentSize().height*m->getPropy());
		auto g = (GameLayer *)this->getParent()->getChildByTag(0);
		int xx = ((int)(this->xstart - pos.x)) / (int)csize.width;
		int yy = ((int)(this->ystart - pos.y)) / (int)csize.height;
		if (xx > g->getWidth() - 1 || yy > g->getHeight() - 1 || xx < 0 || yy < 0)
			return;
		g->setCxCy(xx, yy);
		g->open();
	};


	listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [this,size](Touch* t,Event* e){
		if (!enable)
			return false;
		this->xstart = t->getLocation().x;
		this->ystart = t->getLocation().y;
		if (this->ystart > size.height / 10 * 9 )
			return false;
		if (this->ystart < size.height / 10)
			return false;
		this->w = ((Mine *)((GameLayer *)this->getParent()->getChildByTag(0))->getChildByTag(0))->getContentSize().width * c;

		log("%.0f", c);

		return true;
	};
	listener1->onTouchMoved = [this](Touch *t, Event *e){
		this->xend = t->getLocation().x;
		this->yend = t->getLocation().y;

		float xline = xend - xstart;
		float yline = yend - ystart;
		if (xline < this->w / 4 && xline > this->w/ 4){
			xline = 0;
		}
		if (yline < this->w / 4 && yline >this->w / 4){
			yline = 0;
		}
		//log("hasMove");
		
		int wy = (int)yline / (int)this->w;
		int wx = (int)xline / (int)this->w;
		//log("%d  %d===== %d", (int)this->w, (int)yline,wy);
		if (yline > 0 && (yline / xline >= 0.5 || yline / xline <= -0.5)){
			if ( wy + 1 > hasMove){
				((GameLayer*)this->getParent()->getChildByTag(0))->move(1);
				hasMove += 1;
			}
			
		}
		else if (xline > 0 && yline / xline < 0.5 && yline / xline > -0.5){
			if ( wx + 1 > hasMove){
				((GameLayer*)this->getParent()->getChildByTag(0))->move(2);
				hasMove += 1;
			}
			
		}
		else if (yline < 0 && (yline / xline >= 0.5 || yline / xline <= -0.5)){
			if (-wy + 1 > hasMove){
				((GameLayer*)this->getParent()->getChildByTag(0))->move(3);
				hasMove += 1;
			}
			
		}
		else if (xline < 0 && yline / xline < 0.5 && yline / xline > -0.5){
			if (-wx + 1 > hasMove){
				((GameLayer*)this->getParent()->getChildByTag(0))->move(4);
				hasMove += 1;
			}
		}

	};
	listener1->onTouchEnded = [this](Touch* t, Event* e){
		this->xend = t->getLocation().x;
		this->yend = t->getLocation().y;

		float xline = xend - xstart;
		float yline = yend - ystart;
		if (xline < this->w / 4 && xline > this->w / 4){
			xline = 0;
		}
		if (yline < this->w / 4 && yline >this->w / 4){
			yline = 0;
		}
		if (yline == 0 && xline == 0){
			((GameLayer *)this->getParent()->getChildByTag(0))->open();
			return;
		}
		hasMove = 0;
	};
	listener1->setEnabled(false);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, this);
	touchx = 2;
	return true;
}
void TouchLayer::changeC(float c){
	this->c = c;
	
}
void TouchLayer::changeListener(){
	switch (touchx)
	{
	case 1:
		listener2->setEnabled(false);
		listener1->setEnabled(true);
		/*Director::getInstance()->getEventDispatcher()->removeEventListener(listener2);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);*/
		break;
	case 2:
		listener2->setEnabled(true);
		listener1->setEnabled(false);
		/*Director::getInstance()->getEventDispatcher()->removeEventListener(listener1);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, this);*/
		break;
	default:
		break;
	}
}
void TouchLayer::Enable(bool e){
	
	enable = e;
}
int TouchLayer::getTouchMethod(){
	return touchx;
}
void TouchLayer::changeTouchMeThod(){
	this->touchx = (this->touchx == 1 ? 2 : 1);
	((GameLayer*)this->getParent()->getChildByTag(0))->changeCho();
	changeListener();

}