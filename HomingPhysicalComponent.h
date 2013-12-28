#pragma once
#include "ProjectilePhysicalComponent.h"

class HomingPhysicalComponent :
	public ProjectilePhysicalComponent
{
protected:
	PhysicalComponent *target;
public:
	HomingPhysicalComponent(GameObject *object = NULL, PhysicalEngine *engine = NULL, PhysicalComponent *target = NULL);
	HomingPhysicalComponent(const HomingPhysicalComponent& component);
	~HomingPhysicalComponent();

	virtual void update();
	HomingPhysicalComponent *clone();
	void setTarget(PhysicalComponent *target);
	PhysicalComponent *getTarget();
};








