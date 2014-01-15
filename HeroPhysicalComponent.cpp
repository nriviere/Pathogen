#include "HeroPhysicalComponent.h"


HeroPhysicalComponent::HeroPhysicalComponent(Cursor *cursor, GameObject *object, PhysicalEngine *engine) : PhysicalComponent(object,engine)
{
	angle = angleAim = 0;
	this->cursor = cursor;
	radius = 6;
	priority = 10;
	horizontalSpeed[0] = verticalSpeed[1] = baseMaxSpeed = maxSpeed = 3;
	baseDeceleration = 0.5;
	baseAcceleration = 1;
}

HeroPhysicalComponent::HeroPhysicalComponent(const HeroPhysicalComponent &heroPhysicalComponent) :PhysicalComponent(heroPhysicalComponent)
{
	horizontalSpeed[0] = verticalSpeed[1] = baseMaxSpeed = maxSpeed = 3;
	baseDeceleration = 0.8;
	baseAcceleration = 1;
}

HeroPhysicalComponent &HeroPhysicalComponent::operator=(const HeroPhysicalComponent &heroPhysicalComponent)
{
	PhysicalComponent::operator=(heroPhysicalComponent);
	return (*this);
}

HeroPhysicalComponent::~HeroPhysicalComponent()
{

}

void HeroPhysicalComponent::collision(Vect4 axis)
{
	Vect4 newPosition = transform.getPos();
	
	if (axis[0] != 0)
	{
		if (axis[0] > 0)
		{
			if (horizontalSpeed[0] > 0)
			{
				horizontalSpeed[0] = -horizontalSpeed[0];
			}
		}
		else if (axis[0] < 0)
		{
			if (horizontalSpeed[0] < 0)
			{
				horizontalSpeed[0] = -horizontalSpeed[0];
			}
		}
		horizontalAcceleration = baseDeceleration;
	} else
	if (axis[1] != 0 )
	{
		if (axis[1]  > 0)
		{
			if (verticalSpeed[1] > 0)
			{
				verticalSpeed[1] = -verticalSpeed[1];
			}
		}
		else if (axis[1] < 0)
		{
			if (verticalSpeed[1] < 0)
			{
				verticalSpeed[1] = -verticalSpeed[1];
			}
		}
		verticalAcceleration = baseDeceleration;
	}
}
void HeroPhysicalComponent::collision(PhysicalComponent *physicalComponent)
{
	GameObject *componentGameObject = physicalComponent->getGameObject();
	if (componentGameObject != NULL)
	{
		gameObject->hitBy(physicalComponent->getGameObject());
	}
}



void HeroPhysicalComponent::update()
{
	angle += 0.1;
	if (angle >= 360) angle = 0;
	
	speed = verticalSpeed + horizontalSpeed;

	if (speed.norme() != 0){
		speed.normalize();
	}
	speed = speed * maxSpeed;
	position = position + speed;
	Matrx44 translation,rotation,rotationAim;
	translation.setPos(position);
	rotation.rotation(angle, Vect4(1,0,0,1));

	Vect4 cursorPos = cursor->getPhysicalComponent()->getPosition();
	Vect4 posToCurs = position - cursorPos;

	angleAim = atan2(posToCurs[1],posToCurs[0]);
	rotationAim.rotation(angleAim, Vect4(0,0,1,1));
	transform = translation *rotationAim * rotation ;

	if (horizontalSpeed.norme() <= maxSpeed || horizontalAcceleration < 1)
	{
		horizontalSpeed = horizontalSpeed * horizontalAcceleration;
	}

	if (verticalSpeed.norme() <= maxSpeed || verticalAcceleration < 1)
	{
		verticalSpeed = verticalSpeed * verticalAcceleration;
	}

	if (horizontalSpeed.norme() < 0.01)
	{
		horizontalSpeed = Vect4(0, 0, 0, 0);
		horizontalAcceleration = 0;
	}

	if (verticalSpeed.norme() < 0.01)
	{
		verticalSpeed = Vect4(0, 0, 0, 0);
		verticalAcceleration = 0;
	}
}

HeroPhysicalComponent *HeroPhysicalComponent::clone()
{
	return new HeroPhysicalComponent(*this);
}