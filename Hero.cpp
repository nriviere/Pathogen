#include "Hero.h"
#include "Projectile.h"
#include "ProjectilePhysicalComponent.h"
#include "GameEngine.h"

Hero::Hero(GameEngine *engine) : GameObject(engine)
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

Hero::Hero(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent) : GameObject(engine,model, physicalComponent)
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

void Hero::shoot()
{
	Projectile *projectile = new Projectile(engine);
	projectile->setHeading(getHeading());
	engine->addObject(projectile);
}

Vect4 Hero::getHeading()
{
	Vect4 heading = engine->getCursor()->getPhysicalComponent()->getPosition() - physicalComponent->getPosition();
	return heading;
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

void Hero::selfAdd()
{
	this->engine->setHero(this);
}
void Hero::selfRemove()
{
	if (engine->getHero() == this)
	{
		this->engine->setHero(NULL);
	}
	
}