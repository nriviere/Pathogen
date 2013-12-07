#pragma once
#include "Enemy.h"


class Bacteria :
	public Enemy
{
public:
	Bacteria(GameEngine *engine = NULL);
	Bacteria(GameEngine *engine, PhysicalComponent *physicalComponent);
	Bacteria(const Bacteria &cell);
	Bacteria &operator=(const Bacteria &cell);
	void replicate();
	void hitBy(Projectile *projectile);
	virtual void hitBy(ObjectType opjectType);
	~Bacteria();
};

