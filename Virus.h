#pragma once
#include "Enemy.h"


class Virus :
	public Enemy
{
public:
	Virus(GameEngine *engine = NULL);
	Virus(GameEngine *engine, PhysicalComponent *physicalComponent);
	Virus(const Virus &cell);
	Virus &operator=(const Virus &cell);
	void replicate();
	virtual void destroy();
	virtual void selfRemove();
	virtual void hitBy(ObjectType opjectType);
	~Virus();
};

