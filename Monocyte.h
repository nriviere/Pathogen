#pragma once
#include "Projectile.h"
#include "HomingPhysicalComponent.h"
class Monocyte :
	public Projectile
{
public:
	Monocyte(GameEngine *engine = NULL, GameObject *target = NULL);
	~Monocyte();

	virtual void hitBy(ObjectType objectType);
	void setTarget(GameObject *target);
	GameObject *getTarget();
protected:
	GameObject *target;
	HomingPhysicalComponent *homingPhysicalComponent;

};

