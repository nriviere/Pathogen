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
#include "AttachablePhysicalComponent.h"
#include "VirusPhysicalComponent.h"

Virus::Virus(GameEngine *engine) : AttachableEnemy(engine, NULL, new VirusPhysicalComponent(NULL,this,engine->getParentEngine()->getPhysicalEngine()) ,8)
{
	objectType = virusType;
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::VIRUS_MODEL_INDEX];
	//physicalComponent = new AttachablePhysicalComponent();
	physicalComponent->setGameObject(this);
	physicalComponent->setPriority(1);
	physicalComponent->setRadius(7);
	attachmentProbability = 0.25;
}

Virus::Virus(GameEngine *engine, VirusPhysicalComponent *physicalComponent) : AttachableEnemy(engine, NULL, physicalComponent, 8)
{
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::VIRUS_MODEL_INDEX];
	objectType = virusType;
	physicalComponent->setPriority(1);
	attachmentProbability = 0.25;
}

Virus::Virus(const Virus &virus) : AttachableEnemy(virus.engine, NULL, new VirusPhysicalComponent(NULL, this, virus.engine->getParentEngine()->getPhysicalEngine()), 8)
{
	objectType = virusType;
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::VIRUS_MODEL_INDEX];
	//physicalComponent = new AttachablePhysicalComponent();
	physicalComponent->setGameObject(this);
	physicalComponent->setPriority(1);
	physicalComponent->setRadius(7);
	attachmentProbability = 0.25;
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

void Virus::destroy()
{
	Explosion *explosion = new Explosion(physicalComponent->getPosition());
	engine->addParticleSystem(explosion);
	engine->getParentEngine()->getSoundEngine()->playSound(SoundEngine::EXPLOSION_SOUND_ID);
	Enemy::destroy();
}

void Virus::attachedReplicate()
{
	Virus *virus = new Virus(*this);
	virus->getPhysicalComponent()->setPosition(physicalComponent->getPosition());
	engine->addObject(virus);
}

void Virus::attachedHitBy(GameObject *object)
{
	ObjectType objectType = object->getObjectType();

	engine->getDebriefingState()->updateStatistics(this->objectType, objectType);

	switch (objectType){

	case lymphocyteTagVirus:
		engine->getInGameState()->setScore(engine->getInGameState()->getScore() + 10);
		attachablePhysicalComponent->getAttachedPhysicalComponent()->getGameObject()->destroy();
		destroy();

		break;

	case cellType:
		replicate();
		break;

	default: break;
	}
}

void Virus::unattachedReplicate()
{

}

void Virus::unattachedHitBy(GameObject *object)
{
	ObjectType objectType = object->getObjectType();

	engine->getDebriefingState()->updateStatistics(this->objectType, objectType);

	switch (objectType){

	case lymphocyteTagVirus:
		engine->getInGameState()->setScore(engine->getInGameState()->getScore() + 10);
		destroy();
		
		break;

	case cellType:
		if (object->getPhysicalComponent()->getAttachment() == NULL && 1.* rand() / RAND_MAX < attachmentProbability)
		{
			attachablePhysicalComponent->attach(object->getPhysicalComponent());
			currentState = attachedState;
		}
		break;

	default: break;
	}
}

void Virus::attachedSelfRemove()
{
	Enemy::selfRemove();
	//attachablePhysicalComponent->getAttachment()->setAttachment(NULL);
	//engine->setToRemove(attachablePhysicalComponent->getAttachment()->getGameObject());
}

void Virus::unattachedSelfRemove()
{
	Enemy::selfRemove();
}