#pragma once
#include "SelfMovingPhysicalComponent.h"
class ProjectilePhysicalComponent :
	public SelfMovingPhysicalComponent
{
public:
	ProjectilePhysicalComponent(GameObject *object = NULL, PhysicalEngine *engine = NULL);
	~ProjectilePhysicalComponent();

	void collision(Vect4 axis);
	void collision(PhysicalComponent *component);
};

