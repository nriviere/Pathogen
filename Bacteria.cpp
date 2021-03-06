#include "Bacteria.h"
#include "Enemy.h"
#include "Renderer.h"
#include "MyEngine.h"
#include "Renderer.h"
#include "GameEngine.h"
#include "CellPhysicalComponent.h"
#include "Explosion.h"
#include "BacteriaWaste.h"

Bacteria::Bacteria(GameEngine *engine) : Enemy(engine,10)
{
	objectType = bacteriaType;
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::BACTERIA_MODEL_INDEX];
	physicalComponent = new CellPhysicalComponent();
	physicalComponent->setGameObject(this);
	physicalComponent->setPriority(1);
	physicalComponent->setRadius(7);
	//replicateTime = 10;
}

Bacteria::Bacteria(GameEngine *engine, SelfMovingPhysicalComponent *physicalComponent) : Enemy(engine,NULL, physicalComponent, 10)
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
	Bacteria *bacteria = new Bacteria(engine);
	bacteria->getPhysicalComponent()->setPosition(physicalComponent->getPosition());
	engine->addObject(bacteria);
}

void Bacteria::destroy()
{
	Explosion *explosion = new Explosion(physicalComponent->getPosition());
	engine->getParentEngine()->getSoundEngine()->playSound(SoundEngine::EXPLOSION_SOUND_ID);
	engine->addParticleSystem(explosion);
	BacteriaWaste *waste = new BacteriaWaste(engine);
	waste->getPhysicalComponent()->setPosition(physicalComponent->getPosition());
	engine->addObject(waste);
	Enemy::destroy();
}

void Bacteria::selfRemove()
{
	Enemy::selfRemove();
	
}

void Bacteria::hitBy(ObjectType objectType)
{

	engine->getDebriefingState()->updateStatistics(this->objectType, objectType);

	switch (objectType){
		
	case neutrophileType: 
		engine->getInGameState()->setScore(engine->getInGameState()->getScore() + 10);
		destroy();
		break;

	default: break;


	}
}