#pragma once
#include "Projectile.h"
class Lymphocyte :
	public Projectile
{
public:
	Lymphocyte(GameEngine *engine = NULL, ObjectType type = lymphocyteType);
	~Lymphocyte();

	virtual void hitBy(ObjectType opjectType);
};

