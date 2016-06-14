#include "OptionLayer.h"
#include "TouchLayer.h"
#include "GameLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;
#define actionTime 0.5

OptionLayer::OptionLayer() :isOpen(false)
{
}
OptionLayer::OptionLayer(int w, int h, int n, int csV)
: isOpen(false), width(w), height(h), number(n), csValue(csV), isChanged(false)
{
}

OptionLayer* OptionLayer::create(int w,int h,int n,int csV)
{
	OptionLayer *pRet = new(std::nothrow) OptionLayer(w,h,n,csV);
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

OptionLayer::~OptionLayer()
{
}
bool OptionLayer::init(){
	size = Director::getInstance()->getVisibleSize();
	this->setGlobalZOrder(3);


	cs = ControlSlider::create(Sprite::create("res/slider-back.png"), Sprite::create("res/slider-progress.png"), Sprite::create("res/slider-thumb.png"));
	cs->setMaximumValue(30.0f);
	cs->setMinimumValue(0.0f);
	cs->setValue(15.0f);
	cs->setAnchorPoint(Vec2(0, 0));
	cs->setPosition(Vec2(size.width, size.height * 0.7));
	cs->setScale(2.0f);
	cs->setTag(12);
	cs->addTargetWithActionForControlEvents(this, cccontrol_selector(OptionLayer::change), Control::EventType::VALUE_CHANGED);
	this->addChild(cs);

	auto widthSlider = ControlSlider::create(Sprite::create("res/slider-back.png"), Sprite::create("res/slider-progress.png"), Sprite::create("res/slider-thumb.png"));
	widthSlider->setMaximumValue(24.0f);
	widthSlider->setMinimumValue(9.0f);
	widthSlider->setValue(width);
	widthSlider->setScale(2.0f);
	widthSlider->setTag(13);
	widthSlider->setAnchorPoint(Vec2(0, 0));
	widthSlider->setPosition(Vec2(size.width *1.1, size.height * 0.6));
	widthSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(OptionLayer::change), Control::EventType::VALUE_CHANGED);
	this->addChild(widthSlider);

	auto heightSlider = ControlSlider::create(Sprite::create("res/slider-back.png"), Sprite::create("res/slider-progress.png"), Sprite::create("res/slider-thumb.png"));
	heightSlider->setMaximumValue(30.0f);
	heightSlider->setMinimumValue(9.0f);
	heightSlider->setValue(height);
	heightSlider->setScale(2.0f);
	heightSlider->setTag(14);
	heightSlider->setAnchorPoint(Vec2(0, 0));
	heightSlider->setPosition(Vec2(size.width *1.1, size.height*0.5));
	heightSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(OptionLayer::change), Control::EventType::VALUE_CHANGED);
	this->addChild(heightSlider);

	auto numberSlider = ControlSlider::create(Sprite::create("res/slider-back.png"), Sprite::create("res/slider-progress.png"), Sprite::create("res/slider-thumb.png"));
	numberSlider->setMaximumValue(width * height - 52.0f);
	numberSlider->setMinimumValue(10.0f);
	numberSlider->setValue(number);
	numberSlider->setScale(2.0f);
	numberSlider->setTag(15);
	numberSlider->setAnchorPoint(Vec2(0, 0));
	numberSlider->setPosition(Vec2(size.width * 1.1, size.height*0.4));
	numberSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(OptionLayer::change), Control::EventType::VALUE_CHANGED);
	this->addChild(numberSlider);

	heightLabel = LabelTTF::create("", "Consolas", 40);
	heightLabel->setAnchorPoint(Vec2(0, 0));
	heightLabel->setPosition(Vec2(size.width, size.height * 0.46));
	heightLabel->setString(String::createWithFormat("height:%0.f", heightSlider->getValue())->getCString());
	heightLabel->setTag(16);
	this->addChild(heightLabel);

	widthLabel = LabelTTF::create("", "Consolas", 40);
	widthLabel->setAnchorPoint(Vec2(0, 0));
	widthLabel->setPosition(Vec2(size.width, size.height * 0.56));
	widthLabel->setString(String::createWithFormat("width:%0.f", widthSlider->getValue())->getCString());
	widthLabel->setTag(17);
	this->addChild(widthLabel);

	numberLabel = LabelTTF::create("", "Consolas", 40);
	numberLabel->setAnchorPoint(Vec2(0, 0));
	numberLabel->setPosition(Vec2(size.width, size.height*0.35));
	numberLabel->setString(String::createWithFormat("Mine:%.0f", numberSlider->getValue())->getCString());
	numberLabel->setTag(18);
	this->addChild(numberLabel);

	label = LabelTTF::create("", "Consolas", 40);
	label->setAnchorPoint(Vec2(0, 0));
	label->setPosition(Vec2(size.width, size.height * 0.65));
	label->setString(String::createWithFormat("%0.f", cs->getValue())->getCString());
	this->addChild(label);


	//this->addChild(restartItem);
	auto optionItem = MenuItemFont::create("option", CC_CALLBACK_1(OptionLayer::menuCallback, this));
	optionItem->setAnchorPoint(Vec2(1, 1));
	optionItem->setPosition(Vec2(size.width * 0.9, size.height));
	//this->addChild(optionItem);

	optionItem->setTag(2);

	lb = LabelTTF::create("slider", "Consolas", 30);
	opraterItem = MenuItemLabel::create(lb, CC_CALLBACK_1(OptionLayer::menuCallback, this));
	//auto opraterItem = MenuItemFont::create("point", CC_CALLBACK_1(OptionLayer::menuCallback, this));
	opraterItem->setAnchorPoint(Vec2(0, 0));
	opraterItem->setPosition(size.width, size.height * 0.85);
	opraterItem->setTag(3);

	auto label3 = LabelBMFont::create("chooser:", "fonts/futura-48.fnt", 30.0f);
	label3->setAnchorPoint(Vec2(0, 0));
	label3->setPosition(Vec2(size.width * 0.1, size.height *0.85));
	this->addChild(label3);

	chooserItem1 = MenuItemSprite::create(Sprite::create("res/13_normal.png"), Sprite::create("res/13_selector.png"), CC_CALLBACK_1(OptionLayer::menuCallback, this));
	chooserItem1->setAnchorPoint(Vec2(0, 0));
	chooserItem1->setPosition(Vec2(label3->getPositionX() + label3->getContentSize().width, size.height * 0.85));

	chooserItem1->setTag(4);

	chooserItem2 = MenuItemSprite::create(Sprite::create("res/14_normal.png"), Sprite::create("res/14_selector.png"), CC_CALLBACK_1(OptionLayer::menuCallback, this));
	chooserItem2->setAnchorPoint(Vec2(0, 0));
	chooserItem2->setPosition(Vec2(chooserItem1->getPositionX() + chooserItem1->getContentSize().width, size.height * 0.85));

	chooserItem2->setTag(5);
	chooserItem3 = MenuItemSprite::create(Sprite::create("res/mouse_normal.png"), Sprite::create("res/mouse.png"), CC_CALLBACK_1(OptionLayer::menuCallback, this));
	chooserItem3->setAnchorPoint(Vec2(0, 0));
	chooserItem3->setPosition(Vec2(chooserItem2->getPositionX() + chooserItem2->getContentSize().width, size.height * 0.86));
	chooserItem3->setTag(6);

	chooserItem3->selected();
	//chooserItem3->setEnabled(false);

	auto Menu1 = Menu::create(chooserItem1, chooserItem2, chooserItem3, optionItem, opraterItem, NULL);
	Menu1->setPosition(Vec2::ZERO);
	addChild(Menu1);


	auto backImg = Sprite::create("res/liter-back.png");
	backImg->setPosition(Vec2(size.width / 2, size.height / 2));
	backImg->setTag(9);
	backImg->setVisible(false);
	this->addChild(backImg);


	auto menuImg = Sprite::create("res/liter.png");
	menuImg->setPosition(Vec2(size.width * 0.5, size.height*0.6));
	menuImg->setTag(10);
	menuImg->setVisible(false);
	this->addChild(menuImg);


	auto restartItem = MenuItemImage::create("res/restart.png", "res/restart_s.png", CC_CALLBACK_1(OptionLayer::menuCallback, this));
	restartItem->setAnchorPoint(Vec2(0, 1));
	restartItem->setScale(0.8f);
	restartItem->setPosition(Vec2(size.width / 9, size.height * 0.6));
	restartItem->setTag(1);

	auto endItem = MenuItemImage::create("res/end.png", "res/end_s.png", CC_CALLBACK_1(OptionLayer::menuCallback, this));
	endItem->setAnchorPoint(Vec2(0, 1));
	endItem->setScale(0.8f);
	endItem->setPosition(Vec2(size.width * 0.7, size.height*0.6));
	endItem->setTag(11);

	Menu *menu = Menu::create(restartItem, endItem, NULL);
	menu->setPosition(Vec2(size.width, 0));
	menu->setTag(8);
	this->addChild(menu);

	return true;
}
void OptionLayer::change(Ref * sender, Control::EventType controlEvent){
	auto cs = (ControlSlider*)sender;
	int nTag = cs->getTag();
	if (nTag == 12){
		label->setString(String::createWithFormat("%0.f", cs->getValue())->getCString());

		((TouchLayer *)this->getParent()->getChildByTag(2))->changeC((15.0 - cs->getValue()) * 0.1 + 2);
	}
	else if (nTag == 13){
		widthLabel->setString(String::createWithFormat("width:%0.f", cs->getValue())->getCString());
		width = cs->getValue();
		isChanged = true;
		//((GameLayer *)this->getParent()->getChildByTag(0))->restartWidthValue(width, height, number);
		((ControlSlider *)this->getChildByTag(15))->setMaximumValue(width * height - 52.0f);
	}else if (nTag == 14){
		heightLabel->setString(String::createWithFormat("height:%0.f", cs->getValue())->getCString());
		height = cs->getValue();
		isChanged = true;

		//((GameLayer *)this->getParent()->getChildByTag(0))->restartWidthValue(width, height, number);
		((ControlSlider *)this->getChildByTag(15))->setMaximumValue(width * height - 52.0f);
	}
	else if (nTag == 15){
		number = cs->getValue();
		numberLabel->setString(String::createWithFormat("Mine:%0.f", cs->getValue())->getCString());
		isChanged = true;
		/*((GameLayer *)this->getParent()->getChildByTag(0))->restartWidthValue(width, height, number);*/
	}
}

void OptionLayer::open(){
	std::string s;
	auto t = (TouchLayer*)this->getParent()->getChildByTag(2);
	switch (t->getTouchMethod())
	{
	case 1:
		s = "slider";
		break;
	case 2:
		s = "point";
		break;
	default:
		break;
	}
	lb->setString(s);
	opraterItem->runAction(MoveBy::create(actionTime, Vec2(-opraterItem->getContentSize().width, 0)));
	cs->runAction(MoveBy::create(actionTime, Vec2(-cs->getContentSize().width * 2, 0)));
	label->runAction(MoveBy::create(actionTime, Vec2(-cs->getContentSize().width, 0)));

	this->getChildByTag(13)->runAction(MoveBy::create(actionTime, Vec2(-size.width / 2, 0)));
	this->getChildByTag(14)->runAction(MoveBy::create(actionTime, Vec2(-size.width / 2, 0)));
	this->getChildByTag(15)->runAction(MoveBy::create(actionTime, Vec2(-size.width / 2, 0)));
	this->getChildByTag(16)->runAction(MoveBy::create(actionTime, Vec2(-size.width / 2, 0)));
	this->getChildByTag(17)->runAction(MoveBy::create(actionTime, Vec2(-size.width / 2, 0)));
	this->getChildByTag(18)->runAction(MoveBy::create(actionTime, Vec2(-size.width / 2, 0)));

	((TouchLayer *)this->getParent()->getChildByTag(2))->Enable(false);
	isOpen = true;
}
void OptionLayer::close(){
	opraterItem->runAction(MoveBy::create(actionTime, Vec2(opraterItem->getContentSize().width, 0)));
	cs->runAction(MoveBy::create(actionTime, Vec2(cs->getContentSize().width * 2, 0)));
	label->runAction(MoveBy::create(actionTime, Vec2(cs->getContentSize().width, 0)));
	this->getChildByTag(13)->runAction(MoveBy::create(actionTime, Vec2(size.width / 2, 0)));
	this->getChildByTag(14)->runAction(MoveBy::create(actionTime, Vec2(size.width / 2, 0)));
	this->getChildByTag(15)->runAction(MoveBy::create(actionTime, Vec2(size.width / 2, 0)));
	this->getChildByTag(16)->runAction(MoveBy::create(actionTime, Vec2(size.width / 2, 0)));
	this->getChildByTag(17)->runAction(MoveBy::create(actionTime, Vec2(size.width / 2, 0)));
	this->getChildByTag(18)->runAction(MoveBy::create(actionTime, Vec2(size.width / 2, 0)));
	((TouchLayer *)this->getParent()->getChildByTag(2))->Enable(true);
	isOpen = false;
	if (isChanged){
		((GameLayer *)this->getParent()->getChildByTag(0))->restartWidthValue(width, height, number);
		isChanged = false;
	}
}
void OptionLayer::menuCallback(Ref* pSender){
	MenuItemSprite *item = (MenuItemSprite*)pSender;
	int nTag = item->getTag();
	if (nTag == 1){
		auto g = (GameLayer *)this->getParent()->getChildByTag(0);
		g->restart();
		this->gameRestart();
	}
	else if (nTag == 2){
		if (isOpen)
			this->close();
		else
			this->open();
	}
	else if (nTag == 3){
		auto m = ((MenuItemFont *)this->getChildByTag(3));
		lb->setString(((TouchLayer*)this->getParent()->getChildByTag(2))->getTouchMethod() == 1 ? "point" : "slider");
		auto t = (TouchLayer*)this->getParent()->getChildByTag(2);
		t->changeTouchMeThod();
	}
	else if (nTag == 4){
		auto g = (GameLayer*)this->getParent()->getChildByTag(0);
		g->setChooser(2);
		chooserItem1->selected();
		chooserItem2->unselected();
		chooserItem3->unselected();
	}
	else if (nTag == 5){
		auto g = (GameLayer*)this->getParent()->getChildByTag(0);
		g->setChooser(3);
		chooserItem2->selected();
		chooserItem1->unselected();
		chooserItem3->unselected();
	}
	else if (nTag == 6){
		auto g = (GameLayer*)this->getParent()->getChildByTag(0);
		g->setChooser(1);
		chooserItem3->selected();

		chooserItem1->unselected();
		chooserItem2->unselected();
	}
	else if (nTag == 11){
		gameExit();
	}
}
void OptionLayer::timerHandler(float dt){

}
void OptionLayer::gameEnd(){
	this->getChildByTag(9)->setVisible(true);
	this->getChildByTag(10)->setVisible(true);
	this->getChildByTag(8)->runAction(Sequence::create(
		MoveTo::create(0.5f, Vec2::ZERO),
		MoveBy::create(0.1f, Vec2(-20.0, 0)),
		MoveBy::create(0.1f, Vec2(20.0, 0)), NULL));

}
void OptionLayer::gameRestart(){
	this->getChildByTag(9)->setVisible(false);
	this->getChildByTag(10)->setVisible(false);
	this->getChildByTag(8)->setPosition(Vec2(size.width, 0));
}
void OptionLayer::gameExit(){
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}