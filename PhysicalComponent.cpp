#include "PhysicalComponent.h"
#include <time.h>

PhysicalComponent::PhysicalComponent()
{
	transform = Matrx44(	Vect4(1,0,0,0),
							Vect4(0,1,0,0),
							Vect4(0,0,1,0),
							Vect4(0,0,0,1));
	speed = verticalSpeed = horizontalSpeed = Vect4(0, 0, 0, 0);
	acceleration = verticalAcceleration = horizontalAcceleration = 0;
	baseAcceleration = 1.1;
	baseDeceleration = 0.97;
	maxSpeed = 3;
	radius = 3.2; //faire une classe pour chaque type
	position = Vect4(0,0,0,1);
}

PhysicalComponent::PhysicalComponent(const PhysicalComponent &physicalComponent)
{
	transform = physicalComponent.transform;
	speed = physicalComponent.speed;
	verticalSpeed = physicalComponent.verticalSpeed;
	horizontalSpeed = physicalComponent.horizontalSpeed;
	acceleration = physicalComponent.acceleration;
	verticalAcceleration = physicalComponent.verticalAcceleration;
	horizontalAcceleration = physicalComponent.verticalAcceleration;
}

PhysicalComponent &PhysicalComponent::operator=(const PhysicalComponent &physicalComponent)
{
	transform = physicalComponent.transform;
	speed = physicalComponent.speed;
	verticalSpeed = physicalComponent.verticalSpeed;
	horizontalSpeed = physicalComponent.horizontalSpeed;
	acceleration = physicalComponent.acceleration;
	verticalAcceleration = physicalComponent.verticalAcceleration;
	horizontalAcceleration = physicalComponent.verticalAcceleration;
	return (*this);
}

PhysicalComponent::~PhysicalComponent()
{

}

Matrx44 PhysicalComponent::getTransform()
{
	return transform;
}
Vect4 PhysicalComponent::getSpeed()
{
	return speed;
}

Vect4 PhysicalComponent::getPosition()
{
	return position;
}

float PhysicalComponent::getAcceleration()
{
	return acceleration;
}

float PhysicalComponent::getRadius()
{
	return radius;
}

void PhysicalComponent::setTransform(Matrx44 transform)
{
	this->transform = transform;
}
void PhysicalComponent::setSpeed(Vect4 speed)
{
	this->speed = speed;
}

void PhysicalComponent::setPosition(Vect4 position)
{
	this->position = position;
}

void PhysicalComponent::setAcceleration(float acceleration)
{
	this->acceleration = acceleration;
}


void PhysicalComponent::collision(Vect4 axis)
{

}
void PhysicalComponent::collision(PhysicalComponent *physicalComponent)
{
	Vect4 v(position - physicalComponent->position);
	acceleration = 0;
	if (v.norme() != 0){
		v.normalize();
		speed = v;
	}else{
		srand(time(NULL));
		float x = (1.*rand() / RAND_MAX), y = (1.*rand() / RAND_MAX), z = 0;
		speed = Vect4(x,y,z,0);
		speed.normalize();
	}
	Vect4 v2 = speed;
	v2.normalize();
	position = physicalComponent->position + v2*(radius + physicalComponent->getRadius());
	
	
}

void PhysicalComponent::update()
{
	position = position + speed;
	Matrx44 m(	1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				position[0], position[1], position[2], 1);
	transform = m;
	speed = speed * acceleration;
}

void PhysicalComponent::moveUp()
{
	verticalSpeed = Vect4(0, 1, 0, 1);
	verticalAcceleration = baseAcceleration;
}
void PhysicalComponent::moveDown()
{
	verticalSpeed = Vect4(0, -1, 0, 1);
	verticalAcceleration = baseAcceleration;
}
void PhysicalComponent::moveLeft()
{
	horizontalSpeed = Vect4(-1, 0, 0, 1);
	horizontalAcceleration = baseAcceleration;
}
void PhysicalComponent::moveRight()
{
	horizontalSpeed = Vect4(1, 0, 0, 1);
	horizontalAcceleration = baseAcceleration;
}

void  PhysicalComponent::stopMoveUp()
{
	verticalAcceleration = baseDeceleration;
}

void  PhysicalComponent::stopMoveDown()
{
	verticalAcceleration = baseDeceleration;
}

void  PhysicalComponent::stopMoveRight()
{
	horizontalAcceleration = baseDeceleration;
}

void  PhysicalComponent::stopMoveLeft()
{
	horizontalAcceleration = baseDeceleration;
}