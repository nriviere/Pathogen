#include "ProjectilePhysicalComponent.h"
#include "GameObject.h"
#include "GameEngine.h"
#include "Hero.h"

ProjectilePhysicalComponent::ProjectilePhysicalComponent(GameObject *object, PhysicalEngine *engine) : SelfMovingPhysicalComponent(object,engine)
{
	baseMaxSpeed = maxSpeed = baseSpeed = 3;
	if (object != NULL)
	{
		PhysicalComponent *component = object->getGameEngine()->getHero()->getPhysicalComponent();
		Vect4 v = object->getGameEngine()->getHero()->getHeading();
		v.normalize();
		position = component->getPosition() + v * (component->getRadius() + radius + 1);
		transform.setPos(position);
	}
}


ProjectilePhysicalComponent::~ProjectilePhysicalComponent()
{
}

void ProjectilePhysicalComponent::collision(Vect4 axis)
{
	gameObject->destroy();
}

void ProjectilePhysicalComponent::collision(PhysicalComponent *component)
{
	GameObject *componentGameObject = component->getGameObject();
	if (componentGameObject != NULL)
	{
		component->getGameObject()->hitBy(gameObject);
		gameObject->hitBy(component->getGameObject());
	}
}

