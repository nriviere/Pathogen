#include "Monocyte.h"
#include "GameEngine.h"
#include "MyEngine.h"

Monocyte::Monocyte(GameEngine *engine) : Projectile(engine)
{
	this->engine = engine;

	if (engine != NULL){
		this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::MONOCYTE_MODEL_INDEX];
	}
	else
	{
		model = NULL;
	}
	objectType = monocyteType;
}


Monocyte::~Monocyte()
{
}

void Monocyte::hitBy(ObjectType objectType)
{
	switch (objectType){

	case bacteriaType:
		//destroy();
		break;
	//Faire en sorte qu'il retourne vers le hero  pour le virus et le cancer
	case virusType:
		this->engine->getHero()->setLymphocyteTag(lymphocyteTagVirus);
		//destroy();
		break;
	case cancerType:
		this->engine->getHero()->setLymphocyteTag(lymphocyteTagCancer);
		//destroy();
		break;
	default: break;
	}
}
