#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}
bool Player::init(){
	this->setContentSize(Size(122,122));
	isPlaying = false;
	this->setAnchorPoint(Vec2(0.5, 0.5));
	cardOnGround_id = new int[6];
	for (int i = 0; i < 6; i++){
		cardOnGround_id[i] = -1;
	}
	return true;
}
void Player::setTouchEnable(bool t){
	m_touchLayer->setTouchEnable(t);
}
void Player::groundStart(){
	//isPlaying = true;
	tackCard();
}
void Player::groundEnd(){
	if (getIsMine()){
		setTouchEnable(false);
	}
	m_actionCounter->run(ActionCounter::ongroundend);
	
}
int Player::getDir(){
	return dir;
}
int Player::getId(){
	return m_id;
}
void Player::onActionEnd(){

}
void Player::execute(int method, int cid, int location){
	if (method == 1){
		recoveryCard(cid);
	}
	else{
		disCard(cid, location + 6);
	}
}
void Player::openAiControl(){
	//决定
	//方法 1为回收，2为出牌
	int targetMethod = 1; 
	// 牌的id
	int targetId = -1;
	// 出牌位置
	int targetLocation = -1;

	//得到对面场上的卡牌id以及对应的位置
	int *c = m_onPlayerBehaviorChangeListener->getOtherCards();

	int cards[3];
	for (int i = 0; i < 3; i++){
		cards[i] = cardsOnHand.at(i).asInt();
	}
	for (int i = 0; i < 3; i++){
		int idValue = cards[i];
		targetMethod = 1;
		targetId = idValue;
		targetLocation = 0;
		if (m_dataManager->getCardManaById(idValue) <= m_mana){
			for (int i = 0; i < 6; i++){
				if (cardOnGround_id[i] == -1){
					
					targetMethod = 2;
					targetId = idValue;
					targetLocation = i;
					break;
				}
			}
			
		}
		else{
			targetMethod = 1;
			targetId = idValue;
			targetLocation = 0;
		}
		execute(targetMethod, targetId, targetLocation);
	}
	/*
	m_mana //角色的mana
	int* cardOnGround_id; //角色场上的卡牌
	ValueVector cardsOnHand; //角色手上的卡牌
	*/

	/*log("openAi!");
	recoveryCard(cardsOnHand.at(0).asInt());
	disCard(cardsOnHand.at(0).asInt(), 9);
	disCard(cardsOnHand.at(0).asInt(), 11);
	m_actionCounter->run(0);*/

	/*Vector<FiniteTimeAction*> vec;
	auto dtaction = DelayTime::create(tttime);
	vec.pushBack(CallFunc::create(CC_CALLBACK_0(Player::recoveryCard, this, cardsOnHand.at(0).asInt())));
	vec.pushBack(dtaction->clone());
	vec.pushBack(CallFunc::create(CC_CALLBACK_0(Player::disCardHand, this, cardsOnHand.at(1).asInt(), 9)));
	vec.pushBack(dtaction->clone());
	vec.pushBack(CallFunc::create(CC_CALLBACK_0(Player::disCardHand, this, cardsOnHand.at(2).asInt(), 11)));



	this->runAction(Sequence::create(vec));*/
	/*recoveryCard(cardsOnHand.at(0).asInt());
	disCard(cardsOnHand.at(0).asInt(), 9);
	disCard(cardsOnHand.at(0).asInt(), 11);
	log("AIAIAIAI!");*/
}
void Player::disCardHand(int cardId, int location){
	disCard(cardId, location);
}
//出牌
bool Player::disCard(int cardId,int location){
	if (location > maxLocation || location < minLocation){
		return false;
	}
	if (m_mana < m_dataManager->getCardManaById(cardId)){
		return false;
	}

	m_mana -= m_dataManager->getCardManaById(cardId);
	cardOnGround_id[location >= 6 ? location - 6 : location] = cardId;

	/*cardsOnGround_id.push_back(Value(cardId));
	cardsOnGround_location.push_back(Value(location));*/
	for (int i = 0; i < cardsOnHand.size(); i++){
		if (cardsOnHand.at(i).asInt() == cardId){
			cardsOnHand.erase(cardsOnHand.begin() + i);
			break;
		}
	}
	if (!getIsMine()){
		
		m_onPlayerBehaviorChangeListener->onDisCard(cardId, location);
	}
	return true;

}
//回收卡牌
void Player::recoveryCard(int cardId){
	m_mana++;
	for (int i = 0; i < cardsOnHand.size(); i++){
		if (cardsOnHand.at(i).asInt() == cardId){
			cardsOnHand.erase(cardsOnHand.begin() + i);
			break;
		}
	}
	cards.push_back(Value(cardId));
	if (!getIsMine()){
		m_onPlayerBehaviorChangeListener->onRecoveryCard(cardId);
	}
}
//抽牌
void Player::tackCard(){
	for (int i = 0; i < 3; i++){
		int x = Value(CCRANDOM_0_1() * cards.size()).asInt();
		cardsOnHand.push_back(cards.at(x));
		m_onPlayerBehaviorChangeListener->onTackCard(cards.at(x).asInt(),this->getIsMine(),i);
		m_actionCounter->closeToDelay();
		cards.erase(cards.begin() + x);
		
	}
	m_actionCounter->run(ActionCounter::ontackcardend);
	
}
void Player::setOnPlayerBehaviorChangeListener(OnPlayerBehaviorChangeListener* o){
	m_onPlayerBehaviorChangeListener = o;
	m_actionCounter = m_onPlayerBehaviorChangeListener->getActionCounter();
}

//说话
void Player::say(std::string s){

	lb = LabelTTF::create(s, "fonts/arial.ttf", 20.0f, Size(200, 50));
	lb->setColor(Color3B::BLACK);
	lb->setFontFillColor(Color3B::WHITE);
	
	m_isMine ? lb->setPosition(Vec2(0, 172)) : lb->setPosition(Vec2(122, 788));

	this->addChild(lb,1);

	scheduleOnce(schedule_selector(Player::closeLabel), 3.0f);
}
//设置是否是玩家自己
void Player::setIsMine(bool isMine){
	m_isMine = isMine;
	if (m_isMine){
		this->setPosition(Vec2(579,61));
		minLocation = 0;
		maxLocation = 5;
		dir = 1;

		m_touchLayer = TouchLayer::create();
		m_touchLayer->registeTouchEvent();
		m_touchLayer->setTouchEnable(false);
		m_touchLayer->setPosition(Vec2::ZERO);
		this->addChild(m_touchLayer,0);
	}
	else{
		this->setPosition(Vec2(61, 899));
		dir =-1;
		minLocation = 6;
		maxLocation = 11;
	}
}
void Player::changeLocationCard(int from, int to){
	cardOnGround_id[to] = cardOnGround_id[from];
	cardOnGround_id[from] = -1;
}
void Player::closeLabel(float dt){
	lb->removeFromParent();
	lb = NULL;
}
void Player::readCards(){
	for (int i = 0; i < 10; i++){
		cards.push_back(Value(i));
	}
}
void Player::writeCards(){

}
void Player::initPlayer(){

	m_photo = Sprite::create(StringUtils::format("image/photo%d.png",m_id));
	m_photo->setPosition(this->getContentSize() / 2);
	this->addChild(m_photo,0);

	readCards();
}
void Player::addToCards(int id){
	cards.push_back(Value(id));
}

void Player::setId(int id){
	m_id = id;
	initPlayer();
}
bool Player::getIsMine(){
	return m_isMine;
}
void Player::setDataManager(DataManager* d){
	m_dataManager = d;
}
void Player::setOnTouchListener(OnTouchListener* ot){
	m_touchLayer->setOnTouchListener(ot);
}
void Player::setMana(int mana){
	m_mana = mana;
}
bool Player::getIsPlaying(){
	return isPlaying;
}
//得到场上卡牌的数组
int* Player::getCardsOnGround(){
	return cardOnGround_id;
}
void Player::setHp(int hp){
	m_hp = hp;

	std::string s = Value(hp).asString();
	
	m_hpLabel = LabelTTF::create(s, "fonts/arial.ttf", 30.0f);
	Point p = getIsMine() ? Point(15,107) :Point(107,15);
	m_hpLabel->setPosition(p);
	m_hpLabel->setColor(Color3B::RED);
	this->addChild(m_hpLabel,1);
}
void Player::changeHp(int hp){
	auto fw = FlowWord::create();
	this->addChild(fw, 2);

	std::string s = hp > 0 ? "+" : "" + Value(hp).asString();
	m_actionCounter->registAction(fw, fw->setWord(s, hp > 0 ? Color3B::GREEN : Color3B::RED, m_hpLabel->getPosition()));

	m_hp += hp;
	int x = m_hp;

	auto cf = CallFunc::create([&,x](){
		m_hpLabel->setString(Value(x).asString());
	});
	m_actionCounter->registAction(this, cf);

	if (m_hp <= 0){
		this->isDie = true;
		this->showDie();
	}

	/*auto fw = FlowWord::create();
	this->addChild(fw,2);
	bool flag = true;
	flag = hp > 0 ? true : false;
	auto s = flag?"+":"-"  +  Value(hp).asString();
	fw->setWord(s, flag ? Color3B::GREEN : Color3B::RED, m_hpLabel->getPosition());
	
	m_hp += hp;
	m_hpLabel->setString(Value(m_hp).asString());
	return m_hp <= 0;*/
}
void Player::setIsDie(bool d){
	isDie = d;
}
bool Player::getIsDie(){
	return isDie;
}
void Player::setIsPlaying(bool p){
	isPlaying = p;
}
void Player::showDie(){
	auto cf = CallFunc::create([&](){
		/*this->removeFromParent();*/
		log("die!!");
	});
	m_actionCounter->registAction(this, cf);
}
void Player::removeGroundCardsById(int id){
	for (int i = 0; i < 6; i++){
		if (cardOnGround_id[i] == id){
			cardOnGround_id[i] = -1;
		}
	}
	/*for (int i = 0; i < cardsOnGround_id.size(); i++){
		if (cardsOnGround_id.at(i).asInt() == id){
			cardsOnGround_id.erase(cardsOnGround_id.begin() + i);
			cardsOnGround_location.erase(cardsOnGround_location.begin() + i);
		}
	}*/
}