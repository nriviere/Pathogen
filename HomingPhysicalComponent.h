#pragma once
#include "ProjectilePhysicalComponent.h"


class HomingPhysicalComponentState;
class TagetingState;
class UntargetingState;

class HomingPhysicalComponent :
	public ProjectilePhysicalComponent
{
protected:
	PhysicalComponent *target;
	HomingPhysicalComponentState *currentState;
	TagetingState *targetingState;
	UntargetingState *untargetingState;
public:
	HomingPhysicalComponent(GameObject *object = NULL, PhysicalEngine *engine = NULL, PhysicalComponent *target = NULL);
	HomingPhysicalComponent(const HomingPhysicalComponent& component);
	~HomingPhysicalComponent();

	virtual void update();
	void targetingUpdate();
	void untargetingUpdate();
	HomingPhysicalComponent *clone();
	void setTarget(PhysicalComponent *target);
	virtual void sendDestroyedTarget(PhysicalComponent *component);
	virtual void destroy();
	PhysicalComponent *getTarget();
};

class HomingPhysicalComponentState
{
protected:
	HomingPhysicalComponent *homingPhysicalComponent;
public:
	HomingPhysicalComponentState(HomingPhysicalComponent *homingPhysicalComponent=NULL) 
		: homingPhysicalComponent(homingPhysicalComponent)
	{}
	virtual void update(){};
};

class TagetingState : public HomingPhysicalComponentState
{
public:
	TagetingState(HomingPhysicalComponent *homingPhysicalComponent = NULL)
		: HomingPhysicalComponentState(homingPhysicalComponent)
	{}
	virtual void update()
	{
		homingPhysicalComponent->targetingUpdate();
	};
};
class UntargetingState : public HomingPhysicalComponentState
{
public:
	UntargetingState(HomingPhysicalComponent *homingPhysicalComponent = NULL)
		: HomingPhysicalComponentState(homingPhysicalComponent)
	{}
	virtual void update()
	{
		homingPhysicalComponent->untargetingUpdate();
	};
};






