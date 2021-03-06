#include "Lymphocyte.h"
#include "GameEngine.h"
#include "MyEngine.h"
#include "SelfMovingPhysicalComponent.h"

Lymphocyte::Lymphocyte(GameEngine *engine, ObjectType type) : Projectile(engine)
{
	if (engine != NULL){
		this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::LYMPHOCYTE_MODEL_INDEX];
	}
	else
	{
		model = NULL;
	}
	objectType = type;
}


Lymphocyte::~Lymphocyte()
{
}

void Lymphocyte::hitBy(ObjectType objectType)
{
	switch (objectType){
	case virusType:
		destroy();
		break;

	case cancerTypeDeclared:
		destroy();
		break;

	case bacteriaType:
		destroy();

	default: break;
	}
}

