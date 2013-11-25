#pragma once
#include "GameObject.h"
#include "Vect4.h"

class Enemy;

class Projectile :
	public GameObject
{
public:
	Projectile(GameEngine *engine = NULL);
	~Projectile();
	void hit(Enemy *enemy);
	void setHeading(Vect4 v);
};

