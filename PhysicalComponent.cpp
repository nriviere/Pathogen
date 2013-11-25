#include "PhysicalComponent.h"
#include <time.h>

unsigned int PhysicalComponent::MAX_COMPONENTS_COUNT = 1000;
unsigned int PhysicalComponent::currentID = 0;

unsigned int PhysicalComponent::getNewID()
{
	if (unusedIDs.size() == 0)
	{
		return currentID++;
	}
	else {
		unsigned int id = unusedIDs.front();
		unusedIDs.pop_front();
		return id;
	}
}

PhysicalComponent::PhysicalComponent(GameObject *gameObject)
{
	ID = getNewID();
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
	this->gameObject = gameObject;
}

PhysicalComponent::PhysicalComponent(const PhysicalComponent &physicalComponent)
{
	ID = getNewID();
	transform = physicalComponent.transform;
	speed = physicalComponent.speed;
	verticalSpeed = physicalComponent.verticalSpeed;
	horizontalSpeed = physicalComponent.horizontalSpeed;
	acceleration = physicalComponent.acceleration;
	verticalAcceleration = physicalComponent.verticalAcceleration;
	horizontalAcceleration = physicalComponent.verticalAcceleration;
	position = physicalComponent.position;
	radius = physicalComponent.radius;
	engineIndex = UINT_MAX;
	baseAcceleration = physicalComponent.baseAcceleration;
	baseDeceleration = physicalComponent.baseDeceleration;
	maxSpeed = physicalComponent.maxSpeed;
	gameObject = physicalComponent.gameObject;
}

PhysicalComponent &PhysicalComponent::operator=(const PhysicalComponent &physicalComponent)
{
	PhysicalComponent::PhysicalComponent(physicalComponent);
	return (*this);
}

PhysicalComponent::~PhysicalComponent()
{
	unusedIDs.push_back(ID);
}

unsigned int PhysicalComponent::getID()
{
	return ID;
}

Matrx44 PhysicalComponent::getTransform()
{
	return transform;
}
Vect4 PhysicalComponent::getSpeed()
{
	return speed;
}

Vect4 &PhysicalComponent::getPosition()
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

unsigned int PhysicalComponent::getEngineIndex()
{
	return engineIndex;
}

std::list<PhysicalComponent*>::iterator PhysicalComponent::getGridPosition()
{
	return gridPosition;
}

unsigned int PhysicalComponent::getGridX()
{
	return gridX;
}

unsigned int PhysicalComponent::getGridY()
{
	return gridY;
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
	this->transform.setPos(position);
}

void PhysicalComponent::setAcceleration(float acceleration)
{
	this->acceleration = acceleration;
}

void PhysicalComponent::setGameObject(GameObject *object)
{
	this->gameObject = object;
}

void PhysicalComponent::setGridPosition(std::list<PhysicalComponent*>::iterator gridPosition, unsigned int x, unsigned int y)
{
	this->gridPosition = gridPosition;
	gridX = x;
	gridY = y;
}

void PhysicalComponent::setHeading(Vect4 v)
{
	this->speed = v;
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

void PhysicalComponent::setEngineIndex(unsigned int index)
{
	engineIndex = index;
}

PhysicalComponent *PhysicalComponent::clone()
{
	return new PhysicalComponent(*this);
}