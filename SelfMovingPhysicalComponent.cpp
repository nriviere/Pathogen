#include "SelfMovingPhysicalComponent.h"
#include <time.h>

using namespace std;


SelfMovingPhysicalComponent::SelfMovingPhysicalComponent(GameObject *object, PhysicalEngine *engine) : PhysicalComponent(object,engine)
{
	baseSpeed = 1.5;
	
	float x = rand();
	float y = rand(), z = 0;
	speed = Vect4(x, y, z, 0);
	speed.normalize();
	speed = speed*baseSpeed;
	innerForce = Force(speed,1);
	priority = 0;
}

SelfMovingPhysicalComponent::SelfMovingPhysicalComponent(const SelfMovingPhysicalComponent& component) : PhysicalComponent(component)
{
	innerForce = component.innerForce;
	baseSpeed = component.baseSpeed;
	forces = component.forces;
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

void SelfMovingPhysicalComponent::collision(PhysicalComponent *physicalComponent)
{
	if (priority <= physicalComponent->getPriority())
	{
		Vect4 n = position - physicalComponent->getPosition();
		n[3] = 0;
		if (n.norme() == 0){
			float x = (1.*rand() / RAND_MAX), y = (1.*rand() / RAND_MAX), z = 0;
			n = Vect4(x, y, z, 0);
		}
		n.normalize();
		innerForce = innerForce.reflect(n);
		position = physicalComponent->getPosition() + n*(physicalComponent->getRadius() + radius + 0.1);

		float dot = speed.dot(n);
		float nn = speed.norme() * n.norme();
		float orientation = 1;
		float det = speed[0] * n[1] - speed[1] * n[0];
		if (det < 0) orientation = -1;
		rotationSpeed = (dot - nn) * 0.05 * orientation;
		rotationAcceleration = 0.999;
	}
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
	//Vect4 v3 = physicalComponent->getSpeed();
	float dot = speed.dot(n);
	float nn = speed.norme() * n.norme();
	float orientation = 1;
	float det = speed[0] * n[1] - speed[1] * n[0];
	if (det < 0) orientation = -1;
	rotationSpeed = (dot - nn) * 0.05 * orientation;
	rotationAcceleration = 0.999;
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

	Matrx44 translation(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		position[0], position[1], position[2], 1);


	rotationSpeed *= rotationAcceleration;
	currentAngle += rotationSpeed;
	if (currentAngle >= 360) currentAngle = 0;
	if (abs(rotationSpeed) < 0.01) rotationSpeed = 0;

	Matrx44 rotation;
	rotation.rotation(currentAngle, Vect4(0, 0, 1, 1));

	transform = translation * rotation;
	//speed = speed * acceleration;
}

SelfMovingPhysicalComponent *SelfMovingPhysicalComponent::clone()
{
	return new SelfMovingPhysicalComponent(*this);
}

void SelfMovingPhysicalComponent::setHeading(Vect4 v)
{
	v.normalize();
	v = v*baseSpeed;
	innerForce = Force(v, 1);
}