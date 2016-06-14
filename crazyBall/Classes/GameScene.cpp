#include "GameScene.h"


Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GameScene::create();

	scene->addChild(layer);
	return scene;
}
bool GameScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->initBall();
	this->initBoundEdge();
	this->initSlidePlate();
	this->initTouchListener();
	this->initTopAprons();
	this->scheduleUpdate();
	return true;
}

void GameScene::initBall() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->ball = Ball::createBall(Vec2(visibleSize.width / 2, visibleSize.height / 2), Vec2(0.0, -300.0));
	auto ballSprite = Sprite::create("ball.png");
	ballSprite->setScale(0.4);
	this->ball->bindSprite(ballSprite);
	this->addChild(this->ball);
}

void GameScene::initBoundEdge() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* edgeSpace = Sprite::create();
	PhysicsBody *boundBody = PhysicsBody::createEdgeSegment(Vec2(-visibleSize.width/2, -visibleSize.height/2), Vec2(-visibleSize.width/2, visibleSize.height/2), PHYSICSBODY_MATERIAL_DEFAULT, 5.0f);
	boundBody->addShape(PhysicsShapeEdgeSegment::create(Vec2(-visibleSize.width/2, visibleSize.height/2), Vec2(visibleSize.width/2, visibleSize.height/2), PHYSICSBODY_MATERIAL_DEFAULT, 5.0f));
	boundBody->addShape(PhysicsShapeEdgeSegment::create(Vec2(visibleSize.width/2, visibleSize.height/2), Vec2(visibleSize.width/2, -visibleSize.height/2), PHYSICSBODY_MATERIAL_DEFAULT, 5.0f));
	for (auto shape:boundBody->getShapes())
	{
		shape->setRestitution(1.0f);
		shape->setFriction(0.0f);
	}
	edgeSpace->setPhysicsBody(boundBody);
	edgeSpace->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(edgeSpace);
}

void GameScene::initSlidePlate() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->slidePlate = Apron::createApron(Vec2(visibleSize.width / 2 - 50, 50), Vec2(visibleSize.width / 2 + 50, 50));
	this->addChild(slidePlate);
}
void GameScene::initTouchListener() {
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch *touch, Event *event) {
		log("Touch begin");
		movePostion = touch->getLocation();
		log("Location : %f %f", movePostion.x, movePostion.y);
		return true;
	};
	listener->onTouchMoved = [&](Touch *touch, Event *event) {
		log("Touch move");
		auto postion = touch->getLocation();
		this->moveSlidePlate(postion.x - movePostion.x, postion.y - movePostion.y);
		movePostion = postion;
		log("Location : %f %f", movePostion.x, movePostion.y);
	};
	listener->onTouchEnded = [&](Touch *touch, Event *event) {
		log("Touch end");
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::initTopAprons()
{
	apronManager = ApronManager::create();
	this->addChild(apronManager);

	apronManager->generateApron(5);
	aprons = apronManager->getAprons();
	for (auto apron : aprons)
	{
		this->addChild(apron);
	}
}

void GameScene::moveSlidePlate(float x, float y) {
	log("Move ball %f %f", x, y);
	auto visiableSize = Director::getInstance()->getVisibleSize();
	auto width = this->slidePlate->getBoundingBox().size.width / 2.0f;
	auto currentPostion = this->slidePlate->getPosition();
	auto movedPostion = Vec2(std::max(width, std::min(currentPostion.x + x, visiableSize.width-width)), currentPostion.y);
	this->slidePlate->setVelocity(Vect(x * 10, 0));
	this->slidePlate->setPosition(movedPostion);
}

void GameScene::update(float ft) {
	if (checkGameIsOver()) {
		log("Game is lost");
		pause();
	}

}
bool GameScene::checkGameIsOver() {
	auto visiableSize = Director::getInstance()->getVisibleSize();
	return this->ball->getSprite()->getPositionY() < -visiableSize.height / 2-this->ball->getSprite()->getContentSize().width;
}
bool GameScene::checkGameIsFinish() {
	return false;
}
void GameScene::pause() {
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
}
void GameScene::start() {
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1);
}
void GameScene::stop() {
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
}