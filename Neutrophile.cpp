#include "Neutrophile.h"
#include "GameEngine.h"
#include "MyEngine.h"

Neutrophile::Neutrophile(GameEngine *engine) : Projectile(engine)
{
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

	default: break;
	}
}