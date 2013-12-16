#include "Virus.h"
#include "Enemy.h"
#include "Renderer.h"
#include "MyEngine.h"
#include "Renderer.h"
#include "GameEngine.h"
#include "CellPhysicalComponent.h"
#include "Explosion.h"
#include <stdlib.h>
#include <time.h>

Virus::Virus(GameEngine *engine) : Enemy(engine)
{
	objectType = virusType;
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::VIRUS_MODEL_INDEX];
	physicalComponent = new CellPhysicalComponent();
	physicalComponent->setGameObject(this);
	physicalComponent->setPriority(1);
	physicalComponent->setRadius(7);
}

Virus::Virus(GameEngine *engine, PhysicalComponent *physicalComponent) : Enemy(engine, NULL, physicalComponent, 3)
{
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::VIRUS_MODEL_INDEX];
	objectType = virusType;
	physicalComponent->setPriority(1);
}

Virus::Virus(const Virus &virus) : Enemy(virus)
{
	objectType = virusType;
}

Virus &Virus::operator=(const Virus &virus)
{
	Virus::Virus(virus);
	objectType = virusType;
	return *this;
}

Virus::~Virus()
{
}

void Virus::replicate()
{
	srand(time(NULL));
	if ((rand() % 100 + 1) > 5)
	{
	}
}

void Virus::destroy()
{
	Explosion *explosion = new Explosion(physicalComponent->getPosition());
	engine->addParticleSystem(explosion);
	Enemy::destroy();
}

void Virus::selfRemove()
{
	Enemy::selfRemove();

}

void Virus::hitBy(ObjectType objectType)
{
	switch (objectType){

	case lymphocyteTagVirus:

		destroy();
		break;

	case cellType:
		replicate();
		break;

	default: break;
	}
}