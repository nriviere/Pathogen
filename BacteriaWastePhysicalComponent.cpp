#include "BacteriaWastePhysicalComponent.h"


BacteriaWastePhysicalComponent::BacteriaWastePhysicalComponent(GameObject *gameObject, PhysicalEngine *engine)
:PhysicalComponent(gameObject,engine)
{
	radius = 15;
	priority = -1;
	float x = 2.*rand() / RAND_MAX - 1;
	float y = 2.*rand() / RAND_MAX - 1;
	float z = 2.*rand() / RAND_MAX - 1;
	rotationAxis = Vect4(x,y,z,0);
	rotationAxis.normalize();
	angle = 0;
}
BacteriaWastePhysicalComponent::BacteriaWastePhysicalComponent(const BacteriaWastePhysicalComponent &physicalComponent)
: PhysicalComponent(physicalComponent)
{
	radius = 15;
	priority = -1;
	float x = 2.*rand() / RAND_MAX - 1;
	float y = 2.*rand() / RAND_MAX - 1;
	float z = 2.*rand() / RAND_MAX - 1;
	rotationAxis = Vect4(x, y, z, 0);
	rotationAxis.normalize();
	angle = 0;
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

	Matrx44 rotation,translation;
	angle += 0.02;
	if (angle >= 360) angle = 0;
	rotation.rotation(angle, rotationAxis);
	translation.setPos(position);
	transform = translation * rotation;
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