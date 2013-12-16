#include "Hero.h"
#include "Projectile.h"
#include "ProjectilePhysicalComponent.h"
#include "Neutrophile.h"
#include "Monocyte.h"
#include "Lymphocyte.h"
#include "GameEngine.h"

Hero::Hero(GameEngine *engine) : GameObject(engine)
{
	objectType = heroType;
}

Hero::Hero(const Hero &hero) : GameObject(hero)
{
	objectType = heroType;
}

Hero &Hero::operator=(const Hero &hero)
{
	GameObject::operator=(hero);
	objectType = heroType;
	return (*this);
}

Hero::Hero(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent) : GameObject(engine,model, physicalComponent)
{
	objectType = heroType;
	munitions[0] = MUN_MAX;
	munitions[1] = MUN_MAX;
	munitions[2] = MUN_MAX;
	currentMunition = 0;
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
	if (munitions[currentMunition] > 0)
	{
		Projectile *projectile = NULL;
		if (currentMunition == 0)	projectile = new Neutrophile(engine);
		if (currentMunition == 1)	projectile = new Monocyte(engine);
		if (currentMunition == 2)	projectile = new Lymphocyte(engine, type);
		projectile->setHeading(getHeading());
		engine->addObject(projectile);
		munitions[currentMunition]--;	
		engine->getParentEngine()->getSoundEngine()->playSound(SoundEngine::TEST_SOUND_ID);
	}
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
	GameObject::selfRemove();
	if (engine->getHero() == this)
	{
		this->engine->setHero(NULL);
	}
	
}

float Hero::getMunitionType1()
{
	return (munitions[0] / MUN_MAX);
}

float Hero::getMunitionType2()
{
	return (munitions[1] / MUN_MAX);
}

float Hero::getMunitionType3()
{
	return (munitions[2] / MUN_MAX);
}

void Hero::setGenerator(int generator)
{
	if (generator == 1)
	{
		regenerator[0] = 10;
		regenerator[1] = 1;
		regenerator[2] = 1;
	}
	else if (generator == 2)
	{
		regenerator[0] = 1;
		regenerator[1] = 10;
		regenerator[2] = 1;
	}
	else if (generator == 3)
	{
		regenerator[0] = 1;
		regenerator[1] = 1;
		regenerator[2] = 10;
	}
}

void Hero::regenerateMunition(float deltaTime)
{
	regenerationTime += deltaTime;
	if (regenerationTime >= 5)
	{
		for (int i = 0; i < 3; i++)
		{
			munitions[i] += regenerator[i];
			if (munitions[i] > MUN_MAX)
			{	
				munitions[i] = MUN_MAX;
			}
			
		}
		regenerationTime = regenerationTime - 5;
	}
}

void Hero::changeMunitionType(bool up)
{
	if (up)
	{
		currentMunition++;
		if (currentMunition > 2)
		{
			currentMunition = 0;
		}
	}
	else{
		currentMunition--;
		if (currentMunition < 0)
		{
			currentMunition = 2;
		}
	}
}

void Hero::changeMunitionType(int type)
{
	currentMunition = type;
}

void Hero::setLymphocyteTag(ObjectType type)
{
	this->type = type;
}