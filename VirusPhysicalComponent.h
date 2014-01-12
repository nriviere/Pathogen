#pragma once
#include "AttachablePhysicalComponent.h"
class VirusPhysicalComponent :
	public AttachablePhysicalComponent
{
protected:
	float maxSeekDistance;
public:
	VirusPhysicalComponent(PhysicalComponent *attachedPhysicalComponent = NULL, GameObject *object = NULL, PhysicalEngine *engine = NULL);
	VirusPhysicalComponent(const AttachablePhysicalComponent& component);
	~VirusPhysicalComponent();
	virtual void unattachedUpdate();
	virtual void update();
};

