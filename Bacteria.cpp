#include "Bacteria.h"
#include "Enemy.h"
#include "Renderer.h"
#include "MyEngine.h"
#include "Renderer.h"
#include "GameEngine.h"
#include "CellPhysicalComponent.h"
#include "Explosion.h"


Bacteria::Bacteria(GameEngine *engine) : Enemy(engine)
{
	objectType = bacteriaType;
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::BACTERIA_MODEL_INDEX];
	physicalComponent = new CellPhysicalComponent();
	physicalComponent->setGameObject(this);
	physicalComponent->setPriority(1);
	physicalComponent->setRadius(7);
}

Bacteria::Bacteria(GameEngine *engine, PhysicalComponent *physicalComponent) : Enemy(engine,NULL, physicalComponent, 3)
{
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::BACTERIA_MODEL_INDEX];
	objectType = bacteriaType;
	physicalComponent->setPriority(1);
}

Bacteria::Bacteria(const Bacteria &bacteria) : Enemy(bacteria)
{
	objectType = bacteriaType;
}

Bacteria &Bacteria::operator=(const Bacteria &bacteria)
{
	Bacteria::Bacteria(bacteria);
	objectType = bacteriaType;
	return *this;
}

Bacteria::~Bacteria()
{
}

void Bacteria::replicate()
{

}

void Bacteria::destroy()
{
	Explosion *explosion = new Explosion(physicalComponent->getPosition());
	engine->getParentEngine()->getSoundEngine()->playSound(SoundEngine::EXPLOSION_SOUND_ID);
	engine->addParticleSystem(explosion);
	Enemy::destroy();
}

void Bacteria::selfRemove()
{
	Enemy::selfRemove();
	
}

void Bacteria::hitBy(ObjectType objectType)
{
	switch (objectType){
		
	case neutrophileType: 
		
		destroy();
		break;

	default: break;


	}
}