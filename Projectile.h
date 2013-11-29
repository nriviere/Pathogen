#pragma once
#include "GameObject.h"
#include "Vect4.h"
#include "Light.h"
#include "LightingGameObject.h"


class Enemy;

class Projectile :
	public LightingGameObject
{
private:
public:
	Projectile(GameEngine *engine = NULL);
	~Projectile();
	void hit(Enemy *enemy);
	void setHeading(Vect4 v);
	virtual void update();
};

