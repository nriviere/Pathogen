#include "HomingPhysicalComponent.h"



HomingPhysicalComponent::HomingPhysicalComponent(GameObject *object, PhysicalEngine *engine, PhysicalComponent *target) : ProjectilePhysicalComponent(object, engine)
{
	this->target = NULL;
	currentState = untargetingState = new UntargetingState(this);
	targetingState = new TagetingState(this);
	if (target != NULL)
	{
		setTarget(target);
	}
	else{
		this->target = target;
	}
}

HomingPhysicalComponent::HomingPhysicalComponent(const HomingPhysicalComponent& component) : ProjectilePhysicalComponent(component)
{
	this->target = component.target;
	currentState = untargetingState = new UntargetingState(this);
	targetingState = new TagetingState(this);
	if (target != NULL)
	{
		currentState = targetingState;
	}
}

HomingPhysicalComponent::~HomingPhysicalComponent()
{
	delete targetingState;
	delete untargetingState;
	if (target != NULL)
	{
		exit(0);
	}
}

void HomingPhysicalComponent::update()
{
	currentState->update();
}

void HomingPhysicalComponent::targetingUpdate()
{
	Vect4 heading = target->getPosition() - position;
	setHeading(heading);
	SelfMovingPhysicalComponent::update();
}

void HomingPhysicalComponent::untargetingUpdate()
{
	SelfMovingPhysicalComponent::update();
}

HomingPhysicalComponent *HomingPhysicalComponent::clone()
{
	return new HomingPhysicalComponent(*this);
}

void HomingPhysicalComponent::setTarget(PhysicalComponent *target)
{
	if (this->target != NULL)
	{
		this->target->setUntargetingComponent(this);
	}
	this->target = target;
	this->target->setTargetingComponent(this);
	currentState = targetingState;
}

void HomingPhysicalComponent::sendDestroyedTarget(PhysicalComponent *component)
{
	currentState = untargetingState;
	target = NULL;
}

void HomingPhysicalComponent::destroy()
{
	if (target != NULL)
	{
		target->setUntargetingComponent(this);
	}
	SelfMovingPhysicalComponent::destroy();
}

PhysicalComponent *HomingPhysicalComponent::getTarget()
{
	return target;
}