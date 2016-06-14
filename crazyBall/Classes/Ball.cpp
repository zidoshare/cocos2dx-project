#include "Ball.h"
Ball::Ball(){

}

Ball::Ball(Vec2 position, Vect velocity)
{
	//this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(position);
	this->velocity = velocity;
}

Ball::~Ball(){

}
bool Ball::init(){
	return true;
}

Ball *Ball::createBall(Vec2 position, Vect velocity){
	auto ball = new Ball(position, velocity);
	if (ball&&ball->init()){
		ball->autorelease();
	}
	else{
		CC_SAFE_DELETE(ball);
	}
	return ball;
}
void Ball::bindSprite(Sprite* sprite){
	Entity::bindSprite(sprite);
	initPhysics();
}
void Ball::initPhysics(){
	PhysicsBody *spriteBody = PhysicsBody::createCircle(this->getSprite()->getBoundingBox().size.width , PHYSICSBODY_MATERIAL_DEFAULT);
	spriteBody->setDynamic(true);
	spriteBody->getShape(0)->setRestitution(1.0f);
	spriteBody->getShape(0)->setFriction(0.0f);
	spriteBody->getShape(0)->setDensity(1.0f);
	spriteBody->getShape(0)->setMass(100);
	spriteBody->setGravityEnable(false);
	spriteBody->setVelocity(this->velocity);
	this->getSprite()->setPhysicsBody(spriteBody);
}
void Ball::setImpulse(Vect velocity)
{
	this->velocity = velocity;
}
