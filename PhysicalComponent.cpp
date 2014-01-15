#include "PhysicalComponent.h"
#include <time.h>
#include "PhysicalEngine.h"

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

PhysicalComponent::PhysicalComponent(GameObject *gameObject, PhysicalEngine *engine)
{
	transform = Matrx44(	Vect4(1,0,0,0),
							Vect4(0,1,0,0),
							Vect4(0,0,1,0),
							Vect4(0,0,0,1));
	speed = verticalSpeed = horizontalSpeed = Vect4(0, 0, 0, 0);
	currentAngle = rotationSpeed =rotationAcceleration = acceleration = verticalAcceleration = horizontalAcceleration = 0;
	baseAcceleration = 1.1;
	baseDeceleration = 0.97;
	baseMaxSpeed = maxSpeed = 3;
	radius = 3.2; //faire une classe pour chaque type
	position = Vect4(0,0,0,1);
	this->gameObject = gameObject;
	this->engine = engine;
	priority = 0;
	attachment = NULL;
	slowed = false;
	slowingComponent = NULL;
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
	position = physicalComponent.position;
	radius = physicalComponent.radius;
	engineIndex = UINT_MAX;
	baseAcceleration = physicalComponent.baseAcceleration;
	baseDeceleration = physicalComponent.baseDeceleration;
	maxSpeed = physicalComponent.maxSpeed;
	gameObject = physicalComponent.gameObject;
	attachment = NULL;
	slowed = false;
	slowingComponent = NULL;
}

PhysicalComponent &PhysicalComponent::operator=(const PhysicalComponent &physicalComponent)
{
	PhysicalComponent::PhysicalComponent(physicalComponent);
	return (*this);
}

PhysicalComponent::~PhysicalComponent()
{
	cout << "poil" << endl;
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

GameObject *PhysicalComponent::getGameObject()
{
	return gameObject;
}

PhysicalEngine *PhysicalComponent::getEngine()
{
	return engine;
}

int PhysicalComponent::getPriority()
{
	return priority;
}

PhysicalComponent *PhysicalComponent::getAttachment()
{
	return attachment;
}

void PhysicalComponent::setTransform(Matrx44 transform)
{
	this->transform = transform;
}
void PhysicalComponent::setSpeed(Vect4 speed)
{
	this->speed = speed;
}

void PhysicalComponent::setRadius(float radius)
{
	this->radius = radius;
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

void PhysicalComponent::setEngine(PhysicalEngine *engine)
{
	this->engine = engine;
}

void PhysicalComponent::setPriority(int priority)
{
	this->priority = priority;
}

void PhysicalComponent::setAttachment(PhysicalComponent *component)
{
	this->attachment = component;
}

void PhysicalComponent::setTargetingComponent(PhysicalComponent *component)
{
	targetingComponents.push_back(component);
}

void PhysicalComponent::setUntargetingComponent(PhysicalComponent *component)
{
	for (list<PhysicalComponent *>::iterator c = targetingComponents.begin(); c != targetingComponents.end();)
	{
		if ((*c)->getEngineIndex() == component->getEngineIndex())
		{
			c = targetingComponents.erase(c);
		}
		else
		{
			++c;
		}
	}
}

bool PhysicalComponent::isSlowed()
{
	return slowed;
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

	//rotation 
	//Vect4 v3 = physicalComponent->getSpeed();
	float dot = speed.dot(v);
	float nn = speed.norme() * v.norme();
	rotationSpeed = dot - nn;
	rotationAcceleration = 0.8;
}

void PhysicalComponent::update()
{
	rotationSpeed *= rotationAcceleration;
	currentAngle += rotationSpeed;
	if (currentAngle >= 360) currentAngle = 0;
	if (abs(rotationSpeed) < 0.1) rotationSpeed = 0;
	Matrx44 rotation,translation;
	translation.setPos(position);
	rotation.rotation(currentAngle, Vect4(0, 0, 1, 1));

	position = position + speed;
	
	transform = translation * rotation;
	speed = speed * acceleration;
}

void PhysicalComponent::moveUp()
{
	verticalSpeed = Vect4(0, maxSpeed, 0, 1);
	verticalAcceleration = baseAcceleration;
}
void PhysicalComponent::moveDown()
{
	verticalSpeed = Vect4(0, -maxSpeed, 0, 1);
	verticalAcceleration = baseAcceleration;
}
void PhysicalComponent::moveLeft()
{
	horizontalSpeed = Vect4(-maxSpeed, 0, 0, 1);
	horizontalAcceleration = baseAcceleration;
}
void PhysicalComponent::moveRight()
{
	horizontalSpeed = Vect4(maxSpeed, 0, 0, 1);
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


void  PhysicalComponent::slow(float slowFactor, PhysicalComponent *component)
{
	maxSpeed = baseMaxSpeed * slowFactor;
	slowingComponent = component;
	slowed = true;
}

void PhysicalComponent::unslow()
{
	maxSpeed = baseMaxSpeed;
	slowed = false;
	slowingComponent = NULL;
}

void PhysicalComponent::setEngineIndex(unsigned int index)
{
	engineIndex = index;
}

void PhysicalComponent::destroy()
{
	if (slowingComponent != NULL)
	{
		slowingComponent->sendDestroyed(this);
	}

	while (targetingComponents.size() > 0)
	{
		targetingComponents.front()->sendDestroyedTarget(this);
		targetingComponents.pop_front();
	}
	//engine->remove(engineIndex);
}

void PhysicalComponent::sendDestroyed(PhysicalComponent *component)
{

}

void PhysicalComponent::sendDestroyedTarget(PhysicalComponent *component)
{

}

PhysicalComponent *PhysicalComponent::clone()
{
	return new PhysicalComponent(*this);
}