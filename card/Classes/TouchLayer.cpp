#include "TouchLayer.h"

TouchLayer::TouchLayer()
{
}

TouchLayer::~TouchLayer()
{
}
bool TouchLayer::init(){
	
	return true;
}
void TouchLayer::registeTouchEvent(){
	log("regisetTouch");
	if (_listener == NULL){
		return;
	}
	_listener = EventListenerTouchOneByOne::create();
	_listener->setEnabled(true);

	_listener->onTouchBegan = [&](Touch* touch,Event* event){
		return m_onTouchListener->onTouchBeganPoint(touch->getLocation());
	};
	_listener->onTouchMoved = [&](Touch* touch, Event* event){
		m_onTouchListener->onTouchMovePoint(touch->getLocation());
	};
	_listener->onTouchEnded = [&](Touch* touch, Event* event){
		m_onTouchListener->onTouchEndedPoint(touch->getLocation());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}
void TouchLayer::setOnTouchListener(OnTouchListener* ot){
	m_onTouchListener = ot;
}
void TouchLayer::setTouchEnable(bool enable){
	_listener->setEnabled(enable);
}