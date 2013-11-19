#include "SelfMovingPhysicalComponent.h"
#include <time.h>

using namespace std;


SelfMovingPhysicalComponent::SelfMovingPhysicalComponent() : PhysicalComponent()
{
	baseSpeed = 2;
	
	float x = rand();
	float y = rand(), z = 0;
	speed = Vect4(x, y, z, 0);
	speed.normalize();
	speed = speed*baseSpeed;
	innerForce = Force(speed,1);
}


SelfMovingPhysicalComponent::~SelfMovingPhysicalComponent()
{
}

Force SelfMovingPhysicalComponent::getInnerForce()
{
	return innerForce;
}

void SelfMovingPhysicalComponent::setInnerForce(Force f)
{
	innerForce = f;
}

void SelfMovingPhysicalComponent::collision(Vect4 axis)
{
	Vect4 n;
	if (axis[0] != 0)
	{
		if (axis[0] > 0)
		{
			n = Vect4(-1, 0, 0, 0);
			
			position[0] = axis[0] - radius -1;
		}
		else if (axis[0] < 0)
		{
			n = Vect4(1, 0, 0, 0);
			position[0] = axis[0] + radius + 1;
		}
	}
	else
	if (axis[1] != 0)
	{
		if (axis[1]  > 0)
		{
			n = Vect4(0, -1, 0, 0);
			position[1] = axis[1] - radius - 1;
		}
		else if (axis[1] < 0)
		{
			n = Vect4(0, 1, 0, 0);
			position[1] = axis[1] + radius + 1;
		}
	}

	innerForce = innerForce.reflect(n);
}


void SelfMovingPhysicalComponent::update()
{
	speed = Vect4(0, 0, 0, 1);
	for (list<Force>::iterator ite = forces.begin(); ite != forces.end();)
	{
		(*ite).update();
		speed = speed + (*ite);
		++ite;
	}
	innerForce.update();
	speed = speed + innerForce;
	position = position + speed;
	Matrx44 m(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		position[0], position[1], position[2], 1);
	transform = m;
}