#include "BacteriaWaste.h"
#include "BacteriaWastePhysicalComponent.h"
#include "GameEngine.h"
#include "Explosion.h"

BacteriaWaste::BacteriaWaste(GameEngine *engine) : GameObject(engine)
{
	physicalComponent = bacteriaWastePhysicalComponent = new BacteriaWastePhysicalComponent(this, engine->getParentEngine()->getPhysicalEngine());
	model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::BACTERIA_WASTE_MODEL_INDEX];
	objectType = bacteriaWasteType;
}

BacteriaWaste::BacteriaWaste(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent) 
: GameObject(engine, model, physicalComponent)
{
	objectType = bacteriaWasteType;
	bacteriaWastePhysicalComponent = NULL;
}

BacteriaWaste::~BacteriaWaste()
{
}

void BacteriaWaste::hitBy(GameObject *gameObject)
{
	ObjectType objectType = gameObject->getObjectType();
	//bacteriaWastePhysicalComponent->slow(gameObject->getPhysicalComponent());

	engine->getDebriefingState()->updateStatistics(this->objectType, objectType);

	switch (objectType)
	{
	case monocyteType :
		engine->getInGameState()->setScore(engine->getInGameState()->getScore() + 10);
		destroy();
		break;
	default:
		break;
	}
}


void BacteriaWaste::destroy(){
	Explosion *explosion = new Explosion(physicalComponent->getPosition());
	engine->getParentEngine()->getSoundEngine()->playSound(SoundEngine::EXPLOSION_SOUND_ID);
	engine->addParticleSystem(explosion);
	GameObject::destroy();
}