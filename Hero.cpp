#include "Hero.h"


Hero::Hero()
{

}

Hero::Hero(const Hero &hero) : GameObject(hero)
{

}

Hero &Hero::operator=(const Hero &hero)
{
	GameObject::operator=(hero);
	return (*this);
}

Hero::Hero(RenderableComponent *model, PhysicalComponent *physicalComponent) : GameObject(model, physicalComponent)
{

}

Hero::~Hero()
{

}

void Hero::moveUp()
{
	physicalComponent->moveUp();
}

void Hero::moveDown()
{
	physicalComponent->moveDown();
}

void Hero::moveRight()
{
	physicalComponent->moveRight();
}

void Hero::moveLeft()
{
	physicalComponent->moveLeft();
}

void Hero::stopMoveUp()
{
	physicalComponent->stopMoveUp();
}
void Hero::stopMoveDown()
{
	physicalComponent->stopMoveDown();
}
void Hero::stopMoveRight()
{
	physicalComponent->stopMoveRight();
}
void Hero::stopMoveLeft()
{
	physicalComponent->stopMoveLeft();
}
