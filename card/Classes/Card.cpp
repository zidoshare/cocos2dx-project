#include "Card.h"
Card::Card()
{
}

Card::~Card()
{
}
bool Card::init(){
	if (!Node::init()){
		return false;
	}

	m_hpLabel = nullptr;
	m_manaLabel = nullptr;
	m_attackLabel = nullptr;
	m_rangeLabel = nullptr;
	draw = nullptr;
	back = nullptr;
	
	isDie = false;
	isBack = false;
	m_sprite = Sprite::create("image/card_mini.png");
	m_id = -1;
	this->setContentSize(Size(90, 122));
	this->setAnchorPoint(Vec2(0.5, 0.5));
	m_sprite->setPosition(this->getContentSize() / 2);
	m_sprite->setScaleX(0);
	this->addChild(m_sprite, 1);

	back = Sprite::create("image/back.png");
	//back->setScaleX(1);
	back->setPosition(this->getContentSize() / 2);
	this->addChild(back, 2);

	return true;
}
bool Card::getIsDie(){
	return isDie;
}
void Card::setId(int id){
	m_id = id;
	//Sprite* draw = Sprite::create(StringUtils::format("image/draw%d.png", m_id));
	if (draw != nullptr){
		draw->initWithFile("image/draw0.png");
		draw->setZOrder(1);
		return;
	}
	draw = Sprite::create("image/draw0.png");
	draw->setPosition(m_sprite->getContentSize() / 2);

	m_sprite->addChild(draw,1);
}
void Card::setHp(int hp){
	m_hp = hp;
	
	if (m_hpLabel != nullptr){
		m_hpLabel->setString(Value(m_hp).asString());
		m_hpLabel->setZOrder(1);
		return;
	}

	m_hpLabel = LabelTTF::create(Value(m_hp).asString(), "fonts/arial.ttf", 20.0f);
	m_hpLabel->setColor(Color3B::RED);
	m_hpLabel->setName("hp");
	m_hpLabel->setPosition(Vec2(60, 10));
	m_sprite->addChild(m_hpLabel, 1);
}
void Card::setAttack(int attack){
	m_attack = attack;

	if (m_attackLabel != nullptr){
		m_attackLabel->setString(Value(m_attack).asString());
		m_attackLabel->setZOrder(1);
		return;
	}

	m_attackLabel = LabelTTF::create(Value(m_attack).asString(), "fonts/arial.ttf", 20.0f);
	m_attackLabel->setColor(Color3B::RED);
	m_attackLabel->setPosition(Vec2(30, 10));
	m_sprite->addChild(m_attackLabel, 1);
}
void Card::setMana(int mana){
	m_mana = mana;

	if (m_manaLabel != nullptr){
		m_manaLabel->setString(Value(m_mana).asString());
		m_manaLabel->setZOrder(1);
		return;
	}
	m_manaLabel = LabelTTF::create(Value(m_mana).asString(), "fonts/arial.ttf", 20.0f);
	m_manaLabel->setColor(Color3B::RED);
	m_manaLabel->setPosition(Vec2(30, 112));
	m_sprite->addChild(m_manaLabel, 1);
}
void Card::setSkillId(int skillId){
	m_skillId = skillId;

}
void Card::setRange(int range){
	m_range = range;
	if (m_rangeLabel != nullptr){
		m_rangeLabel->setString(Value(m_range).asString());
		m_rangeLabel->setZOrder(1);
		return;
	}

	m_rangeLabel = LabelTTF::create(Value(m_range).asString(), "fonts/arial.ttf", 20.0f);
	m_rangeLabel->setColor(Color3B::RED);
	m_rangeLabel->setPosition(Vec2(60, 112));
	m_sprite->addChild(m_rangeLabel, 1);
}
void Card::setMsg(int hp, int attack, int mana, int range, int skillId = 0){
	setHp(hp);
	setAttack(attack);
	setMana(mana);
	setSkillId(skillId);
	setRange(range);
}

int Card::getId(){
	return m_id;
}
int Card::getHp(){
	return m_hp;
}
int Card::getAttack(){
	return m_attack;
}
int Card::getMana(){
	return m_mana;
}
int Card::getSkillId(){
	return m_skillId;
}

int Card::getRange(){
	return m_range;
}
Sprite* Card::getCardNode(){
	return m_sprite;
}
void Card::setActionCounter(ActionCounter* ac){
	m_actionCounter = ac;
}
void Card::showFly(Point p,float time){
	auto mt = MoveTo::create(time, p);
	auto cf = CallFunc::create([&](){
		auto shadow = Sprite::create("image/shadow.png");
		shadow->setAnchorPoint(Vec2(0, 1));
		shadow->setPosition(Vec2(0, 122));
		shadow->setTag(0);
		this->addChild(shadow, 0);
	});
	auto seq = Sequence::create(mt, cf, nullptr);
	m_actionCounter->registAction(this, seq);
	//this->runAction(seq);
}
void Card::showMove(Point p,float time){
	if (time == 0){
		auto cf = CallFunc::create([this,p](){
			this->setPosition(p);
		});
		m_actionCounter->registAction(this, cf);
		return;
	}
	auto m = MoveTo::create(time, p);
	m_actionCounter->registAction(this, m);
}
void Card::showDown(Point p,float time){
	auto mt = MoveTo::create(time, Point(p.x - 10, p.y + 10));
	auto mt2 = MoveTo::create(time, p);
	CallFunc* cf = CallFunc::create([this](){
		this->removeChildByTag(0);
	});
	Sequence* seq = Sequence::create(mt, mt2, cf, nullptr);
	m_actionCounter->registAction(this, seq);
}
void Card::showError(){
	auto m1 = MoveBy::create(0.1f, Vec2(-5, 0));
	auto m2 = m1->reverse();
	auto m3 = MoveBy::create(0.1f, Vec2(5, 0));
	auto m4 = m3->reverse();
	auto seq = Sequence::create(m1, m2, m3, m4, nullptr);
	m_actionCounter->registAction(this, seq);
}
void Card::setDataManager(DataManager* dm){
	m_dataManager = dm;
}
void Card::initCardWithDataManager(DataManager* dm, int id){
	this->setId(id);
	this->setMsg(dm->getCardHpById(id), dm->getCardAttackById(id), dm->getCardManaById(id),dm->getCardRangeById(id));
}
void Card::showAiMove(Point p){

	showFly(this->getPosition(),0.2f);
	for (int i = 1; i <= 5; i++){
		showMove(this->getPosition() + (p - this->getPosition()) * i / 5, 0.1f);
	}
	showDown(p, 0.2f);


	/*Vector<FiniteTimeAction*> vec;
	vec.pushBack(CallFunc::create(CC_CALLBACK_0(Card::showFly, this, this->getPosition(),0.2f)));
	vec.pushBack(DelayTime::create(0.2f));
	for (int i = 1; i <= 5; i++){
		vec.pushBack(CallFunc::create(CC_CALLBACK_0(Card::showMove, this, this->getPosition() + (p - this->getPosition()) * i / 5, 0.3f)));
		vec.pushBack(DelayTime::create(0.3f));
	}
	vec.pushBack(CallFunc::create(CC_CALLBACK_0(Card::showDown, this, p,0.2f)));
	

	this->runAction(Sequence::create(vec));*/
}

void Card::showAttack(Card *c,bool attackAble,Player* p){
	float x = m_dir * 10;
	auto m1 = MoveBy::create(0.3f, Vec2(0, x));
	auto delay = DelayTime::create(0.3f);
	auto m2 = m1->reverse();
	m_actionCounter->showLog(StringUtils::format("id = %d showAttack", this->getId()));
	log("id = %d showAttack", this->getId());

	m_actionCounter->registAction(this, Sequence::create(m1, delay, m2, NULL));
	
	if (c != nullptr){

		c->showDefense();
		c->changeHp(-this->getAttack());

		if (!c->getIsDie() && attackAble == true){
			c->showAttack(this, false, nullptr);
		}
	}
	else{
		if (p != nullptr)
			p->changeHp(-m_attack);
	}

	
}
void Card::showDie(){
	auto cf = CallFunc::create([this](){
		m_actionCounter->showLog(StringUtils::format("id = %d showDie", this->getId()));
		log("id = %d showDie", this->getId());
		this->removeFromParent();
	});
	m_actionCounter->registAction(this, cf);
}
void Card::showDefense(){
	m_actionCounter->showLog(StringUtils::format("id = %d showDefense", this->getId()));
	log("id = %d showDefense", this->getId());
	auto m1 = MoveBy::create(0.1f, Vec2(-5, 0));
	auto m2 = m1->reverse();
	auto m3 = MoveBy::create(0.1f, Vec2(5, 0));
	auto m4 = m3->reverse();
	auto seq = Sequence::create(m1, m2, m3, m4, nullptr);
	m_actionCounter->registAction(this, seq);
	//this->runAction(seq);
}
void Card::changeHp(int hp){
	/*int hp = -c->getAttack();*/
	m_actionCounter->showLog(StringUtils::format("id = %d changeHp", this->getId()));
	log("id = %d changeHp", this->getId());
	auto fw = FlowWord::create();
	this->addChild(fw,10);
	
	std::string s = hp > 0 ? "+" : "" + Value(hp).asString();
	m_actionCounter->registAction(fw, fw->setWord(s, hp > 0 ? Color3B::GREEN : Color3B::RED, m_hpLabel->getPosition()));

	m_hp += hp;
	int x = m_hp;
	auto cf = CallFunc::create([&, x](){
		m_hpLabel->setString(Value(x).asString());
	});
	m_actionCounter->registAction(this, cf);
	
	if (m_hp <= 0){
		this->isDie = true;
		this->showDie();
	}
	/*return m_hp <= 0 ? true : false;*/
}
void Card::setDir(Dir dir){
	m_dir = dir;
}
int Card::getDir(){
	return m_dir;
}
void Card::showTack(float delay, Point p){
	
}
void Card::showBack(bool isB){
	auto reverse = ScaleTo::create(0.3f, 0, 1);
	auto rere = ScaleTo::create(0.3f, 1, 1);

	if (isB){
		m_actionCounter->registAction(TargetedAction::create(m_sprite, reverse));
		m_actionCounter->registAction(TargetedAction::create(back, rere));
	}
	else{
		m_actionCounter->registAction(TargetedAction::create(back, reverse));
		m_actionCounter->registAction(TargetedAction::create(m_sprite, rere));
	}
	isBack = isB;
}
void Card::setBack(bool isb){
	isBack = isb;
	if (isb){
		m_sprite->setScaleX(0);
		back->setScaleX(1);
	}
	else{
		back->setScaleX(0);
		m_sprite->setScaleX(1);
	}
		
}