#include "HomingPhysicalComponent.h"



HomingPhysicalComponent::HomingPhysicalComponent(GameObject *object, PhysicalEngine *engine, PhysicalComponent *target) : ProjectilePhysicalComponent(object, engine)
{
	this->target = target;
}

HomingPhysicalComponent::HomingPhysicalComponent(const HomingPhysicalComponent& component) : ProjectilePhysicalComponent(component)
{
	this->target = component.target;
}

HomingPhysicalComponent::~HomingPhysicalComponent()
{

}

void HomingPhysicalComponent::update()
{
	Vect4 heading = target->getPosition() - position;
	setHeading(heading);
	SelfMovingPhysicalComponent::update();
}
HomingPhysicalComponent *HomingPhysicalComponent::clone()
{
	return new HomingPhysicalComponent(*this);
}

void HomingPhysicalComponent::setTarget(PhysicalComponent *target)
{
	this->target = target;
}

PhysicalComponent *HomingPhysicalComponent::getTarget()
{
	return target;
}