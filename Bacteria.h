#pragma once
#include "Enemy.h"


class Bacteria :
	public Enemy
{
public:
	Bacteria(GameEngine *engine = NULL);
	Bacteria(GameEngine *engine, SelfMovingPhysicalComponent *physicalComponent);
	Bacteria(const Bacteria &cell);
	Bacteria &operator=(const Bacteria &cell);
	void replicate();
	virtual void destroy();
	virtual void selfRemove();
	virtual void hitBy(ObjectType opjectType);
	~Bacteria();
};

