#include "VirusPhysicalComponent.h"
#include "Hero.h"
#include "GameEngine.h"



VirusPhysicalComponent::VirusPhysicalComponent(PhysicalComponent *attachedPhysicalComponent, GameObject *object, PhysicalEngine *engine)
: AttachablePhysicalComponent(attachedPhysicalComponent, object, engine)
{
	maxSeekDistance = 150;
	setBaseSpeed(1.2);
	baseMaxSpeed = maxSpeed = 1.2;
}
VirusPhysicalComponent::VirusPhysicalComponent(const AttachablePhysicalComponent& component) 
: AttachablePhysicalComponent(component)
{
	maxSeekDistance = 150;
	setBaseSpeed(1.2);
	baseMaxSpeed = maxSpeed = 1.2;
}
VirusPhysicalComponent::~VirusPhysicalComponent()
{
	setBaseSpeed(1.2);
	baseMaxSpeed = maxSpeed = 1.2;
}

void VirusPhysicalComponent::unattachedUpdate()
{
	Hero *hero = engine->getEngine()->getGameEngine()->getHero();
	Vect4 toHero = position - hero->getPhysicalComponent()->getPosition();
	float toHeroN = toHero.norme();
	if (toHeroN < maxSeekDistance)
	{
		innerForce = innerForce - toHero * ((maxSeekDistance - toHeroN) / maxSeekDistance)*0.05;
	}
	speed = Vect4(0, 0, 0, 1);
	for (list<Force>::iterator ite = forces.begin(); ite != forces.end();)
	{
		(*ite).update();
		speed = speed + (*ite);
		++ite;
	}
	//exit(0);
	innerForce.update();
	float norme = innerForce.norme();
	if (norme > maxSpeed){
		innerForce = innerForce * (1. / (norme/maxSpeed));
	}
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
}

void VirusPhysicalComponent::update()
{
	currentState->update();
}