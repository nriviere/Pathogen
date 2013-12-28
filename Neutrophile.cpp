#include "Neutrophile.h"
#include "GameEngine.h"
#include "MyEngine.h"
#include "SelfMovingPhysicalComponent.h"

Neutrophile::Neutrophile(GameEngine *engine) : Projectile(engine)
{
	PhysicalEngine *physicalEngine = NULL;
	if (engine != NULL)
	{
		physicalEngine = engine->getParentEngine()->getPhysicalEngine();
	}
	
	if (engine != NULL){
		this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::NEUTROPHILE_MODEL_INDEX];
	}
	else
	{
		model = NULL;
	}
	objectType = neutrophileType;
}


Neutrophile::~Neutrophile()
{
}

void Neutrophile::hitBy(ObjectType objectType)
{
	switch (objectType){

	case bacteriaType:
		destroy();
		break;

	case virusType:
		destroy();
		break;

	case cancerType:
		destroy();
		break;

	default: break;
	}
}

