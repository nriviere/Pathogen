#pragma once
#include "Enemy.h"


class Cancer :
	public Enemy
{
public:
	Cancer(GameEngine *engine = NULL);
	Cancer(GameEngine *engine, PhysicalComponent *physicalComponent);
	Cancer(const Cancer &cell);
	Cancer &operator=(const Cancer &cell);
	void replicate();
	virtual void destroy();
	virtual void selfRemove();
	virtual void hitBy(ObjectType opjectType);
	~Cancer();
};

