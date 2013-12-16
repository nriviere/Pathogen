#pragma once
#include "Projectile.h"
class Monocyte :
	public Projectile
{
public:
	Monocyte(GameEngine *engine = NULL);
	~Monocyte();

	virtual void hitBy(ObjectType objectType);

private:
	GameEngine* engine;
};

