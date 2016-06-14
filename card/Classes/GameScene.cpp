#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}
Scene* GameScene::createScene(){
	auto s = Scene::create();
	auto l = GameScene::create();

	s->addChild(l);

	return s;
}
void GameScene::pause(bool isPause){

}
bool GameScene::init(){
	m_numForMine = 0;
	m_numForOther = 0;
	m_dataManager = DataManager::create();
	this->addChild(m_dataManager);
	
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::pause, this));
	closeItem->setPosition(Vec2(600,480));

	btn = Menu::create(closeItem, NULL);
	btn->setPosition(Vec2::ZERO);
	this->addChild(btn,10);
	

	Size s = Director::getInstance()->getVisibleSize();
	/*---背景---*/
	auto bg = Sprite::create("image/bg.png");
	bg->setPosition(s / 2);
	this->addChild(bg);

	/*---生成中部分隔线---*/
	float xpos = 0.0f;
	float ypos = s.height / 2;
	float xwidth = 32.0f;
	while (xpos < s.width){
		auto dot = Sprite::create("image/dot.png");
		dot->setAnchorPoint(Vec2(0, 0.5));
		dot->setPosition(xpos, ypos);
		xpos += xwidth;
		this->addChild(dot);
	}
	/*---生成牌组画面---*/
	back1 = Sprite::create("image/back.png");
	back1->setAnchorPoint(Vec2(0.5, 0.5));
	back1->setPosition(Vec2(45, 61));
	this->addChild(back1);

	back2 = Sprite::create("image/back.png");
	back2->setAnchorPoint(Vec2(0.5, 0.5));
	back2->setPosition(Vec2(595, 899));
	this->addChild(back2);

	/*---生成格子---*/

	//float x1 = 80, x2 = 291, x3 = 516;
	//float y1 = 714, y2 = 553;
	//float x[3] = { 80, 291, 516 };
	//float y[4] = { 714, 553, 403, 245 };

	Point point1[9] = { Point(220, 61), Point(320, 61), Point(420, 61),
		Point(80, 245), Point(291, 245), Point(516, 245),
		Point(80, 403), Point(291, 403), Point(516, 403), };
	Point point2[9] = { Point(220, 899), Point(320, 899), Point(420, 899),
		Point(80, 557), Point(291, 557), Point(516, 557),
		Point(80, 715), Point(291, 715), Point(516, 715)
	};
	myPoint = new Point[9];
	otherPoint = new Point[9];
	for (int i = 0; i < 9; i++){
		myPoint[i] = point1[i];
		otherPoint[i] = point2[i];
	}

	for (int i = 0; i < 6; i++){
		lattice[i] = Sprite::create("image/lattice.png");
		lattice[i]->setAnchorPoint(Vec2(0.5, 0.5));
		lattice[i]->setPosition(myPoint[i + 3]);
		this->addChild(lattice[i]);
		/*auto num = LabelTTF::create(Value(i).asString(), "Arial", 50.0f);
		num->setPosition(Point(0,0));
		lattice[i]->addChild(num);*/
	}
	for (int i = 6; i < 12; i++){
		lattice[i] = Sprite::create("image/lattice.png");
		lattice[i]->setAnchorPoint(Vec2(0.5, 0.5));
		lattice[i]->setPosition(otherPoint[i - 3]);
		this->addChild(lattice[i]);
		/*auto num = LabelTTF::create(Value(i).asString(), "Arial", 50.0f);
		num->setPosition(Point(0,0));
		lattice[i]->addChild(num);*/
	}
	//动作计数器初始化~
	m_actionCounter = ActionCounter::create();
	this->addChild(m_actionCounter);
	m_actionCounter->setOnActionEndListener(this);
	isOnTack = true;

	p1 = Player::create();
	p1->setId(1);
	p2 = Player::create();
	p2->setId(2);

	this->addChild(p1);
	p1->setIsMine(true);
	p1->setMana(1);
	p1->setHp(30);
	p1->setOnPlayerBehaviorChangeListener(this);
	p1->setOnTouchListener(this);
	p1->setDataManager(m_dataManager);
	this->addChild(p2);
	p2->setIsMine(false);
	p2->setMana(1);
	p2->setHp(30);
	p2->setOnPlayerBehaviorChangeListener(this);
	p2->setDataManager(m_dataManager);

	gameStart();
	
	return true;
}
void GameScene::onGround(bool isOne){
	
}
void GameScene::gameStart(){
	p1->setIsPlaying(true);
	p1->groundStart();
}
bool GameScene::onTouchBeganPoint(Point p){
	
	for (auto c : m_p1cards){
		if (c->getBoundingBox().containsPoint(p)){
			
			c->showFly(p);
			m_actionCounter->run(ActionCounter::ontouch1);
			beginPoint = c->getPosition();
			onTouchCard = c;
			return true;
		}
	}
	return false;
}
void GameScene::onTouchMovePoint(Point p){
	onTouchCard->showMove(p);
	m_actionCounter->run(ActionCounter::ontouch2);
}
void GameScene::onTouchEndedPoint(Point p){
	if (back1->getBoundingBox().containsPoint(p)){
		p1->recoveryCard(onTouchCard->getId());
		onTouchCard->removeFromParent();
		m_p1cards.eraseObject(onTouchCard);
		if (m_p1cards.empty()){
			auto cf = CallFunc::create([&](){
				p1->groundEnd();
			});
			
			m_actionCounter->registAction(p1, cf);
			m_actionCounter->run(ActionCounter::ontouch3);
		}
		return;
	}
	for (int i = 0; i < 6; i++){
		if (lattice[i]->getBoundingBox().containsPoint(p)){
			
			if (p1->disCard(onTouchCard->getId(), i)){
				
				m_p1deskCards.pushBack(onTouchCard);
				m_p1cards.eraseObject(onTouchCard);

				onTouchCard->showDown(lattice[i]->getPosition());
				onTouchCard->setTag(i);	
				if (m_p1cards.empty()){
					auto cf = CallFunc::create([&](){
						p1->groundEnd();
					});
					m_actionCounter->registAction(p1, cf);
				}
				m_actionCounter->run(ActionCounter::ontouch3);
				return;
			}
		}
	}
	onTouchCard->showDown(beginPoint);
	m_actionCounter->run(ActionCounter::ontouch3);
}

void GameScene::onTackCard(int id,bool isMine,int f){
	if (isMine){
		auto c = Card::create();
		c->setDir(1);
		c->setActionCounter(m_actionCounter);
		c->initCardWithDataManager(m_dataManager, id);
		c->setPosition(back1->getPosition());
		c->setBack(true);
		this->addChild(c);
		c->showAiMove(myPoint[m_p1cards.size()]);
		c->showBack(false);
		m_p1cards.pushBack(c);
	}
	else{
		auto c = Card::create();
		c->setDir(-1);
		c->setActionCounter(m_actionCounter);
		c->initCardWithDataManager(m_dataManager, id);
		c->setPosition(back2->getPosition());
		c->setBack(true);
		this->addChild(c);

		c->showAiMove(otherPoint[m_p2cards.size()]);
		
		m_p2cards.pushBack(c);
	}
}
void GameScene::onDisCard(int cardId, int location){

	for (auto c : m_p2cards){
		if (c->getId() == cardId){
			
			c->showAiMove(lattice[location]->getPosition());
			c->showBack(false);
			c->setTag(location);
			
			m_p2deskcards.pushBack(c);
			m_p2cards.eraseObject(c);
			if (m_p2cards.empty()){
				p2->groundEnd();
			}
			return;
		}
	}
}
void GameScene::onRecoveryCard(int cardId){
	for (auto c : m_p2cards){
		if (c->getId() == cardId){
			
			c->showAiMove(back2->getPosition());
			
			auto cf = CallFunc::create([c](){
				c->removeFromParent();
			});
			m_actionCounter->registAction(this, cf);
			m_p2cards.eraseObject(c);
			if (m_p2cards.empty()){
				p2->groundEnd();
			}
			return;
		}
	}
}
ActionCounter* GameScene::getActionCounter(){
	return m_actionCounter;
}
void GameScene::call(float dt){
	removeCardNeedDelay->removeFromParent();
}
Card* GameScene::getCardByLocation(int l){
	return (Card*)(this->getChildByTag(l));
}
Vector<Card*>& GameScene::getCardsByPlayer(Player* p){
	return p->getId() == p1->getId() ? m_p1cards : m_p2cards;
}
Vector<Card*>& GameScene::getDeskCardsByPlayer(Player* p){
	return p->getId() == p1->getId() ? m_p1deskCards : m_p2deskcards;
}
Player* GameScene::getReversePlayer(Player *p){
	return p == p1 ? p2 : p1;
}
Player* GameScene::getPlayerById(int id){
	return p1->getId() == id ? p1 : p2;
}
void GameScene::onDie(Card* c){
	if (c->getDir() == 1){

	}
}
void GameScene::onActionEnd(int msg){
	auto pl1 = p1->getIsPlaying() ? p1 : p2;
	auto pl2 = getReversePlayer(pl1);

	switch (msg){
	case ActionCounter::oncalcend:
		

		pl1->setIsPlaying(false);
		pl2->setIsPlaying(true);
		log(StringUtils::format("--------------p%d start------------",pl2->getId()).c_str());
		pl2->groundStart();

		break;
	case ActionCounter::ongroundend:
		log(StringUtils::format("--------------p%d end------------", pl1->getId()).c_str());
		calc(pl1->getId());
		break;
	case ActionCounter::ontackcardend:
		if (p1->getIsPlaying()){
			log("--------------p1 startTouch------------");
			p1->setTouchEnable(true);
		}
		else if (p2->getIsPlaying()){
			log("--------------p2 startAi------------");
			p2->openAiControl();
		}

		break;
	default:
		break;
	}
}
void GameScene::eraseObjectByPlayerAndCard(Player* p, Card* c){
	if (p == p1){
		m_p1deskCards.eraseObject(c);
	}else if (p == p2){
		m_p2deskcards.eraseObject(c);
	}
}
void GameScene::calc(int pId){
	log("-------------------------calc--------------------");
	auto player1 = getPlayerById(pId);
	auto player2 = getReversePlayer(player1);

	auto Player2DeskCards = getCardsByPlayer(player2);
	auto player1DeskCards = getDeskCardsByPlayer(player1);

	for (auto c : player1DeskCards){
		int r = c->getTag() + c->getRange() * player1->getDir() * 3;
		//如果攻击距离不能达到对面的单位，不做任何攻击处理
		if (r >= player1->minLocation && r <= player1->maxLocation){
			continue;
		}
		auto c2 = (Card*)this->getChildByTag(c->getTag() + player1->getDir() * 3);
		if (c2 == nullptr){
			c2 = (Card*)this->getChildByTag(r);
		}

		c->showAttack(c2, true, player2);

		auto cf = [](){

		};
	}




	//for (auto c : player1DeskCards){
	//	int r = c->getTag() + c->getRange() * player1->getDir() * 3;
	//	//如果攻击距离不能达到对面的单位，不做任何攻击处理
	//	if (r >= player1->minLocation && r <= player1->maxLocation){
	//		break;
	//	}

	//	auto c2 = (Card*)this->getChildByTag(r);
	//	
	//	c->showAttack(c2,true,player2);
	//	if (c2 != nullptr && c2->getIsDie()){
	//		Player2DeskCards.eraseObject(c2);
	//		eraseObjectByPlayerAndCard(player2, c2);
	//		player2->removeGroundCardsById(c2->getId());
	//	}else if (c2 == nullptr){
	//		//如果没有攻击对象卡牌。。。。。有待补充
	//	}
	//}
	//再次循环是为了遍历己方卡牌是否死亡,从场上消除,以及替补空位
	auto cf = CallFunc::create([=](){
		for (auto c : player1DeskCards){
			if (c->getIsDie()){
				player1->removeGroundCardsById(c->getId());
				eraseObjectByPlayerAndCard(player1, c);
				continue;
			}
			int loc = c->getTag() + 3 * player1->getDir();
			if (loc < player1->minLocation || loc > player1->maxLocation){
				break;
			}
			if (this->getChildByTag(loc) == NULL){
				player1->changeLocationCard(c->getTag(), loc);
				c->showAiMove(lattice[loc]->getPosition());
				c->setTag(loc);
			}
		}
		for (auto c : Player2DeskCards){
			if (c->getIsDie()){
				player2->removeGroundCardsById(c->getId());
				eraseObjectByPlayerAndCard(player2, c);
			}
		}
	});
	m_actionCounter->registAction(this, cf);
	/*player1->setIsPlaying(false);
	player2->setIsPlaying(true);*/
	m_actionCounter->run(ActionCounter::oncalcend);
}
//得到场上卡牌的数组,下标为位置，参数为卡牌Id
int* GameScene::getOtherCards(){
	return p1->getCardsOnGround();
}