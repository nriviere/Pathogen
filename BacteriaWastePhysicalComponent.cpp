#include "BacteriaWastePhysicalComponent.h"


BacteriaWastePhysicalComponent::BacteriaWastePhysicalComponent(GameObject *gameObject, PhysicalEngine *engine)
:PhysicalComponent(gameObject,engine)
{
	radius = 15;
	priority = -1;
}
BacteriaWastePhysicalComponent::BacteriaWastePhysicalComponent(const BacteriaWastePhysicalComponent &physicalComponent)
: PhysicalComponent(physicalComponent)
{
	radius = 15;
	priority = -1;
}



void BacteriaWastePhysicalComponent::update()
{
	for (std::list<PhysicalComponent*>::iterator c = slowedList.begin(); c != slowedList.end();)
	{
		if (((*c)->getPosition() - position).norme() - (*c)->getRadius() > radius)
		{
			(*c)->unslow();
			(*c) = NULL;
			c = slowedList.erase(c);
		}
		else
		{
			++c;
		}
	}
}

void BacteriaWastePhysicalComponent::collision(Vect4 axis)
{

}

void BacteriaWastePhysicalComponent::collision(PhysicalComponent *physicalComponent)
{
	slow(physicalComponent);
}

void BacteriaWastePhysicalComponent::slow(PhysicalComponent *physicalComponent)
{
	if (!physicalComponent->isSlowed())
	{
		physicalComponent->slow(0.5, this);
		slowedList.push_back(physicalComponent);
	}
}

void BacteriaWastePhysicalComponent::destroy()
{
	for (std::list<PhysicalComponent*>::iterator c = slowedList.begin(); c != slowedList.end();)
	{
		(*c)->unslow();
		++c;
	}
	PhysicalComponent::destroy();
}

void BacteriaWastePhysicalComponent::sendDestroyed(PhysicalComponent *component)
{
	for (std::list<PhysicalComponent*>::iterator c = slowedList.begin(); c != slowedList.end();)
	{
		if ((*c)->getEngineIndex() == component->getEngineIndex())
		{
			(*c)->unslow();
			(*c) = NULL;
			c = slowedList.erase(c);
		}
		else
		{
			++c;
		}
	}
}