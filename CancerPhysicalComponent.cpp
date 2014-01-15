#include "CancerPhysicalComponent.h"
#include "Cancer.h"


CancerPhysicalComponent::CancerPhysicalComponent(Cancer *object, PhysicalEngine *engine) : SelfMovingPhysicalComponent(object, engine)
{
	declaredState = new CancerPhysicalComponentDeclaredState(this);
	currentState = undeclaredState = new CancerPhysicalComponentUndeclaredState(this);
	if (object != NULL){
		object->setCancerPhysicalComponent(this);
	}
	movementProbability = 1. / (60 * 10);
	baseMaxSpeed = maxSpeed = 1.5;
}

CancerPhysicalComponent::CancerPhysicalComponent(const CancerPhysicalComponent& component) 
: SelfMovingPhysicalComponent(component)
{
	declaredState = new CancerPhysicalComponentDeclaredState(this);
	currentState = undeclaredState = new CancerPhysicalComponentUndeclaredState(this);
	baseMaxSpeed = maxSpeed = 1.5;
}

CancerPhysicalComponent::~CancerPhysicalComponent()
{
	delete declaredState;
	delete undeclaredState;
}

void CancerPhysicalComponent::update()
{
	currentState->update();
}

void CancerPhysicalComponent::declaredUpdate()
{
	float proba = 1. * rand() / RAND_MAX;
	float n = innerForce.norme();
	if (n == 0 && proba <= movementProbability)
	{
		do{
			float x = (2. * rand() / RAND_MAX) - 1;
			float y = (2. * rand() / RAND_MAX) - 1;
			innerForce = Force(x, y, 0, 0.5);
			n = innerForce.norme();
		} while (n == 0);
		innerForce = innerForce * (maxSpeed / n);
		innerForce.setAcceleration(0.995);
	}

	speed = Vect4(0, 0, 0, 0);
	
	innerForce.update();
	//speed = speed + innerForce;
	position = position + innerForce;

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
}

void CancerPhysicalComponent::undeclaredUpdate()
{
	SelfMovingPhysicalComponent::update();
}

void CancerPhysicalComponent::collision(Vect4 axis)
{
	currentState->collision(axis);
}
void CancerPhysicalComponent::collision(PhysicalComponent *component)
{
	currentState->collision(component);
}

void CancerPhysicalComponent::declaredCollision(Vect4 axis)
{
	SelfMovingPhysicalComponent::collision(axis);
}

void CancerPhysicalComponent::undeclaredCollision(Vect4 axis)
{
	SelfMovingPhysicalComponent::collision(axis);
}

void CancerPhysicalComponent::declaredCollision(PhysicalComponent *component)
{
	if (priority <= component->getPriority())
	{
		if (attachment == NULL || attachment->getEngineIndex() != component->getEngineIndex())
		{
			Vect4 n = position - component->getPosition();
			n[3] = 0;
			if (n.norme() == 0){
				float x = (1.*rand() / RAND_MAX), y = (1.*rand() / RAND_MAX), z = 0;
				n = Vect4(x, y, z, 0);
			}
			n.normalize();
			innerForce = Force(n,0.7);
			position = component->getPosition() + n*(component->getRadius() + radius + 0.1);

			float dot = speed.dot(n);
			float nn = speed.norme() * n.norme();
			float orientation = 1;
			float det = speed[0] * n[1] - speed[1] * n[0];
			if (det < 0) orientation = -1;
			rotationSpeed = (dot - nn) * 0.05 * orientation;
			rotationAcceleration = 0.999;
		}
	}
}

void CancerPhysicalComponent::undeclaredCollision(PhysicalComponent *component)
{
	SelfMovingPhysicalComponent::collision(component);
}

void CancerPhysicalComponent::setDeclaredState()
{
	currentState = declaredState;
	innerForce.setAcceleration(0.995);
	setPriority(3);
}

void CancerPhysicalComponentDeclaredState::update()
{
	cancerPhysicalComponent->declaredUpdate();
}

void CancerPhysicalComponentUndeclaredState::update()
{
	cancerPhysicalComponent->undeclaredUpdate();
}

void CancerPhysicalComponentDeclaredState::collision(PhysicalComponent *component)
{
	cancerPhysicalComponent->declaredCollision(component);
}

void CancerPhysicalComponentUndeclaredState::collision(PhysicalComponent *component)
{
	cancerPhysicalComponent->undeclaredCollision(component);
}

void CancerPhysicalComponentDeclaredState::collision(Vect4 axis)
{
	cancerPhysicalComponent->declaredCollision(axis);
}

void CancerPhysicalComponentUndeclaredState::collision(Vect4 axis)
{
	cancerPhysicalComponent->undeclaredCollision(axis);
}