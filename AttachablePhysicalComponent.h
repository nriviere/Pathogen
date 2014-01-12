#pragma once
#include "SelfMovingPhysicalComponent.h"

class AttachablePhysicalComponentState;
class AttachedState;
class UnattachedState;



class AttachablePhysicalComponent :
	public SelfMovingPhysicalComponent
{
protected:
	PhysicalComponent *attachedPhysicalComponent;
	AttachedState *attachedState;
	UnattachedState *unattachedState;
	AttachablePhysicalComponentState *currentState;
	Vect4 offset;

public:
	AttachablePhysicalComponent(PhysicalComponent *attachedPhysicalComponent = NULL, GameObject *object = NULL, PhysicalEngine *engine = NULL);
	AttachablePhysicalComponent(const AttachablePhysicalComponent& component);
	~AttachablePhysicalComponent();

	virtual void collision(PhysicalComponent *physicalComponent);
	virtual void collision(Vect4 axis);

	virtual void update();

	void attach(PhysicalComponent *component);

	virtual void attachedCollision(PhysicalComponent *physicalComponent);
	virtual void attachedCollision(Vect4 axis);

	virtual void unattachedCollision(PhysicalComponent *physicalComponent);
	virtual void unattachedCollision(Vect4 axis);

	virtual void attachedUpdate();
	virtual void unattachedUpdate();

	PhysicalComponent *getAttachedPhysicalComponent();
	AttachablePhysicalComponent *clone();
};

class AttachablePhysicalComponentState
{
protected:
	AttachablePhysicalComponent *component;
public:
	AttachablePhysicalComponentState(AttachablePhysicalComponent *component = NULL);

	virtual void collision(PhysicalComponent *physicalComponent){};
	virtual void collision(Vect4 axis){};
	virtual void update(){};
};

class AttachedState : public AttachablePhysicalComponentState
{
protected:
	AttachablePhysicalComponent *component;
public:
	AttachedState(AttachablePhysicalComponent *component = NULL);

	virtual void collision(PhysicalComponent *physicalComponent);
	virtual void collision(Vect4 axis);
	virtual void update();
};

class UnattachedState : public AttachablePhysicalComponentState
{
protected:
	AttachablePhysicalComponent *component;
public:
	UnattachedState(AttachablePhysicalComponent *component = NULL);

	virtual void collision(PhysicalComponent *physicalComponent);
	virtual void collision(Vect4 axis);
	virtual void update();
};

