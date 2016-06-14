#include "Apron.h"
#include "ui\UIScale9Sprite.h"

Apron::Apron()
{
}

Apron::Apron(Point midPointPosition, Vec2 direction, float length, float width, Point origin, Point destination)
{
	this->midPointPosition = midPointPosition;
	this->direction = direction;
	length += 10;
	this->length = length;
	this->width = width;
	this->origin = origin;
	this->destination = destination;
	log("midPoint=(%.2f,%.2f),length=%.2f,width=%.2f,origin=(%.2f,%.2f),destination=(%.2f,%.2f)",midPointPosition.x,midPointPosition.y,
		length,width,origin.x,origin.y,destination.x,destination.y);
}

Apron::~Apron()
{

}

Apron* Apron::createApron(Point origin, Vec2 dir, float length, float width /*= DEFULT_WIDTH*/)
{
	float tan = dir.y / dir.x;
	float w = length * sqrt(1 / (tan *tan + 1));
	float h = sqrt(length * length - w * w);

	Point o, d;
	o = origin;
	//方向的正负需要判定
	if (dir.x > 0)
		d.x = o.x + w;
	else
		d.x = o.x - w;
	if (dir.y > 0)
		d.y = o.y + h;
	else
		d.y = o.y - h;

	Point p;
	p = Point((d.x - o.x) / 2 + o.x,(d.y - o.y) / 2 + o.y);

	Apron* ap = new Apron(p,dir,length,width,o,d);
	if (ap && ap->init()){
		ap->autorelease();
		return ap;
	}
	else{
		delete ap;
		ap = nullptr;
		return nullptr;
	}
}

Apron* Apron::createApron(Point origin, Point destination, float width /*= DEFULT_WIDTH*/)
{
	Point midPointPosition;
	Vec2 direction;
	float length;
	length = sqrt((destination.y - origin.y)*(destination.y - origin.y) + (destination.x - origin.x)*(destination.x - origin.x));
	midPointPosition.x = (destination.x - origin.x) / 2 + origin.x;
	midPointPosition.y = (destination.y - origin.y) / 2 + origin.y;
	direction.x = midPointPosition.x;
	direction.y = midPointPosition.y;
	Apron* ap = new Apron(midPointPosition, direction, length, width, origin, destination);
	if (ap && ap->init()){
		ap->autorelease();
		return ap;
	}
	else{
		delete ap;
		ap = nullptr;
		return nullptr;
	}
}

bool Apron::init()
{
	this->setPosition(midPointPosition);
	m_sprite = Scale9Sprite::create("test.png");
	m_sprite->setCapInsets(Rect(5, 1, 290, 8));
	m_sprite->setPreferredSize(Size(length, width));
	m_sprite->getSprite()->getTexture()->setAntiAliasTexParameters();
	float r = atan((direction.y - origin.y) / (direction.x-origin.x));
	m_sprite->setRotation(180 - r * 180 / PI);
	bindSprite((Sprite*)m_sprite);
	log("Here!!!!!!!! %f %f %f %f", this->getPositionX(), this->getPositionY(), this->getSprite()->getPositionX(), this->getSprite()->getPositionY());
	this->initPhysics();
	return true;
}

void Apron::initPhysics(){
	//PhysicsBody *spriteBody = PhysicsBody::createBox(this->getSprite()->getBoundingBox().size, PHYSICSBODY_MATERIAL_DEFAULT);
	Point* points=this->getContentPoints();
	Point points1[4] = { Point(0,0),Point(0,10),Point(10,10),Point(10,0) };
	for (int i = 0; i < 4; i++)
		log("Points %d %f %f", i, points[i].x, points[i].y);
	//PhysicsBody *spriteBody = PhysicsBody::createEdgeBox(this->getSprite()->getBoundingBox().size, PHYSICSBODY_MATERIAL_DEFAULT);
	PhysicsBody *spriteBody = PhysicsBody::createPolygon(points,4);
	spriteBody->setDynamic(false);
	spriteBody->getShape(0)->setRestitution(1.0f);
	spriteBody->getShape(0)->setFriction(0.0f);
	spriteBody->getShape(0)->setDensity(1.0f);
	spriteBody->getShape(0)->setMass(0);
	spriteBody->setGravityEnable(false);
	this->getSprite()->setPhysicsBody(spriteBody);
}
Vec2 * Apron::getContentPoints()
{
	float rotationAngle =PI- atan((direction.y - origin.y) / (direction.x - origin.x));
	log("Rotate: %f %f %f", rotationAngle, this->width / 2,this->width);
	Vect relativeOrigin = Vec2(0.0f - this->length / 2 * cos(rotationAngle), 0.0f - this->length / 2 * sin(rotationAngle));
	Vect relativeDesination = Vec2(0.0f + this->length / 2 * cos(rotationAngle), 0.0f + this->length / 2 * sin(rotationAngle));
	Vect *points = new Vec2[4];
	points[0] = Vec2(relativeOrigin.x + this->width / 2 * sin(rotationAngle), relativeOrigin.y - this->width / 2 * cos(rotationAngle));
	points[1] = Vec2(relativeOrigin.x - this->width / 2 * sin(rotationAngle), relativeOrigin.y + this->width / 2 * cos(rotationAngle));
	points[2] = Vec2(relativeDesination.x - this->width / 2 * sin(rotationAngle), relativeDesination.y + this->width / 2 * cos(rotationAngle));
	points[3] = Vec2(relativeDesination.x + this->width / 2 * sin(rotationAngle), relativeDesination.y - this->width / 2 * cos(rotationAngle));
	return points;
}
void Apron::connect(Apron* ap)
{

}

void Apron::setVelocity(Vect velocity) {
	log("Set velocity %f %f", velocity.x, velocity.y);
	auto physicsBody=this->getSprite()->getPhysicsBody();
	physicsBody->setVelocity(Vec2(velocity));
}