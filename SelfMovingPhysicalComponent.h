#pragma once
#include "Force.h"
#include "PhysicalComponent.h"
#include "GameObject.h"
#include <list>



class SelfMovingPhysicalComponent :
	public PhysicalComponent
{
protected:
	Force innerForce;
	std::list<Force> forces;
	float baseSpeed;
public:
	SelfMovingPhysicalComponent(GameObject *object = NULL, PhysicalEngine *engine = NULL);
	SelfMovingPhysicalComponent(const SelfMovingPhysicalComponent& component);
	~SelfMovingPhysicalComponent();

	Force getInnerForce();
	void setInnerForce(Force f);
	void setBaseSpeed(float speed);
	virtual void setAcceleration(float acceleration);
	virtual void collision(PhysicalComponent *physicalComponent);
	virtual void collision(Vect4 axis);

	virtual void update();

	SelfMovingPhysicalComponent *clone();

	void setHeading(Vect4 v);
};

