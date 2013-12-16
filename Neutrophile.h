#pragma once

#include "Projectile.h"

class Neutrophile :
	public Projectile
{
public:
	Neutrophile(GameEngine *engine = NULL);
	~Neutrophile();

	virtual void hitBy(ObjectType opjectType);
};

