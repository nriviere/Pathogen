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
	//Que se passe-t-il lorsque le target est detruit alors que des monocytes le seek ?
	//list de references sur le physical component ?
	physicalComponent = homingPhysicalComponent = new HomingPhysicalComponent(this, physicalEngine, componentTarget);

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
	seekNStrikeState = new SeekNStrike(this);
	comebackState = new Comeback(this);
	currentState = seekNStrikeState;
}


Monocyte::~Monocyte()
{
	delete seekNStrikeState;
	delete comebackState;
}

void Monocyte::hitBy(ObjectType objectType)
{
	currentState->hitBy(objectType);
}

void Monocyte::setTarget(GameObject *target)
{
	this->target = target;
	homingPhysicalComponent->setTarget(target->getPhysicalComponent());
}

GameObject *Monocyte::getTarget()
{
	return target;
}

void SeekNStrike::hitBy(ObjectType objectType)
{
	switch (objectType){
	case bacteriaType:
		monocyte->comeback(bacteriaType);
		break;
		//Faire en sorte qu'il retourne vers le hero  pour le virus et le cancer
	case virusType:
		monocyte->comeback(lymphocyteTagVirus);
		break;
	case cancerType:
		monocyte->comeback(lymphocyteTagCancer);
		break;
	default: break;
	}
	
}

void Comeback::hitBy(ObjectType objectType)
{
	switch (objectType){
	case heroType:
		monocyte->getGameEngine()->getHero()->setLymphocyteTag(lymphocyteTag);
		monocyte->destroy();
		break;
	default: break;
	}
}

void Monocyte::setCurrentState(MonocyteState *state)
{
	this->currentState = state;
}
Comeback *Monocyte::getComebackState()
{
	return comebackState;
}

void Monocyte::comeback(ObjectType lymphocyteTag)
{
	comebackState->setLymphocyteTag(lymphocyteTag);
	setTarget(engine->getHero());
	currentState = comebackState;
}