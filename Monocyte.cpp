#include "Monocyte.h"
#include "GameEngine.h"
#include "MyEngine.h"
#include "HomingPhysicalComponent.h"

Monocyte::Monocyte(GameEngine *engine, GameObject *target)
{
	this->engine = engine;
	PhysicalEngine *physicalEngine = NULL;
	if (engine != NULL)
	{
		physicalEngine = engine->getParentEngine()->getPhysicalEngine();
	}
	this->target = target;
	PhysicalComponent *componentTarget = NULL;
	if (target != NULL)
	{
		componentTarget = target->getPhysicalComponent();
	}
	physicalComponent = new HomingPhysicalComponent(this, physicalEngine, componentTarget);

	if (engine != NULL){
		this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::MONOCYTE_MODEL_INDEX];
	}
	else
	{
		model = NULL;
	}
	
	light->setPosition(this->physicalComponent->getPosition());
	light->setRange(40.);
	light->setAttenuation(0.8);

	objectType = monocyteType;
	target = NULL;
}


Monocyte::~Monocyte()
{
}

void Monocyte::hitBy(ObjectType objectType)
{
	switch (objectType){

	case bacteriaType:
		this->engine->getHero()->setLymphocyteTag(bacteriaType);
		destroy();
		break;
	//Faire en sorte qu'il retourne vers le hero  pour le virus et le cancer
	case virusType:
		this->engine->getHero()->setLymphocyteTag(lymphocyteTagVirus);
		destroy();
		break;
	case cancerType:
		this->engine->getHero()->setLymphocyteTag(lymphocyteTagCancer);
		destroy();
		break;
	default: break;
	}
}

void Monocyte::setTarget(GameObject *target)
{
	this->target = target;
}

GameObject *Monocyte::getTarget()
{
	return target;
}

