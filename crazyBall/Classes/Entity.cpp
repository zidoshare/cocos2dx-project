#include "Entity.h"
Entity::~Entity()
{

}

Entity::Entity()
{

}

bool Entity::init()
{
	return true;
}

void Entity::bindSprite(Sprite* sprite)
{
	this->m_sprite = sprite;
	this->addChild(m_sprite);
	Size size = m_sprite->getBoundingBox().size;
	m_sprite->setPosition(Point(0,0));
	this->setContentSize(size);
}

Sprite* Entity::getSprite()
{
	return m_sprite;
}
