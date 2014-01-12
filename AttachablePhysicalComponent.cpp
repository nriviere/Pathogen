#include "AttachablePhysicalComponent.h"


AttachablePhysicalComponent::AttachablePhysicalComponent(PhysicalComponent *attachedPhysicalComponent, GameObject *object, PhysicalEngine *engine)
: SelfMovingPhysicalComponent(object, engine)
{
	this->attachedPhysicalComponent = attachedPhysicalComponent;
	attachedState = new AttachedState(this);
	unattachedState = new UnattachedState(this);
	currentState = unattachedState;
}

AttachablePhysicalComponent::AttachablePhysicalComponent(const AttachablePhysicalComponent& component) : SelfMovingPhysicalComponent(component)
{
	this->attachedPhysicalComponent = component.attachedPhysicalComponent;
	attachedState = new AttachedState(this);
	unattachedState = new UnattachedState(this);
	currentState = unattachedState;
}


AttachablePhysicalComponent::~AttachablePhysicalComponent()
{
	delete attachedState;
	delete unattachedState;
}

void AttachablePhysicalComponent::collision(PhysicalComponent *physicalComponent)
{
	currentState->collision(physicalComponent);
}
void AttachablePhysicalComponent::collision(Vect4 axis)
{
	currentState->collision(axis);
}

void AttachablePhysicalComponent::update()
{
	currentState->update();
}

void AttachablePhysicalComponent::attach(PhysicalComponent *component)
{
	currentState = attachedState;
	this->attachedPhysicalComponent = component;
	offset = component->getPosition() - position;
	component->setAttachment(this);
}

void AttachablePhysicalComponent::attachedCollision(PhysicalComponent *physicalComponent)
{
	/*
	if (priority <= physicalComponent->getPriority())
	{
		if (attachedPhysicalComponent->getEngineIndex() != physicalComponent->getEngineIndex())
		{
			PhysicalComponent comp(*physicalComponent);
			comp.setPosition(comp.getPosition() - offset);
			attachedPhysicalComponent->collision(&comp);
		}
	}
	attachedPhysicalComponent->collision(physicalComponent);*/
}

void AttachablePhysicalComponent::attachedCollision(Vect4 axis)
{
	//Faire un truc qui marche
	//attachedPhysicalComponent->collision(axis-offset);
}

void AttachablePhysicalComponent::unattachedCollision(PhysicalComponent *physicalComponent)
{
	SelfMovingPhysicalComponent::collision(physicalComponent);
	GameObject *componentGameObject = physicalComponent->getGameObject();
	if (componentGameObject != NULL)
	{
		physicalComponent->getGameObject()->hitBy(gameObject);
		gameObject->hitBy(physicalComponent->getGameObject());
	}
}

void AttachablePhysicalComponent::unattachedCollision(Vect4 axis)
{
	SelfMovingPhysicalComponent::collision(axis);
}

void AttachablePhysicalComponent::attachedUpdate()
{
	transform = attachedPhysicalComponent->getTransform();
	Matrx44 translation;
	translation.setPos(offset);
	transform = transform*translation;
	position = transform.getPos();
}

void AttachablePhysicalComponent::unattachedUpdate()
{
	//SelfMovingPhysicalComponent::update();
}

PhysicalComponent *AttachablePhysicalComponent::getAttachedPhysicalComponent()
{
	return attachedPhysicalComponent;
}

AttachablePhysicalComponent *AttachablePhysicalComponent::clone()
{
	return new AttachablePhysicalComponent(*this);
}

void UnattachedState::collision(PhysicalComponent *physicalComponent)
{
	component->unattachedCollision(physicalComponent);
}
void UnattachedState::collision(Vect4 axis)
{
	component->unattachedCollision(axis);
}
void UnattachedState::update()
{
	component->unattachedUpdate();
}

void AttachedState::collision(PhysicalComponent *physicalComponent)
{
	component->attachedCollision(physicalComponent);
}
void AttachedState::collision(Vect4 axis)
{
	component->attachedCollision(axis);
}
void AttachedState::update()
{
	component->attachedUpdate();
}

AttachablePhysicalComponentState::AttachablePhysicalComponentState(AttachablePhysicalComponent *component)
{
	this->component = component;
}

AttachedState::AttachedState(AttachablePhysicalComponent *component)
{
	this->component = component;
}

UnattachedState::UnattachedState(AttachablePhysicalComponent *component)
{
	this->component = component;
}