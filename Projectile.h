#pragma once
#include "GameObject.h"
#include "Vect4.h"
#include "Light.h"
#include "LightingGameObject.h"


class Enemy;

class Projectile :
	public LightingGameObject
{
protected:
	unsigned int type;
	
public:
	Projectile();
	Projectile(GameEngine *engine);
	~Projectile();
	void hit(GameObject *gameObject);
	void setHeading(Vect4 v);
	virtual void update();
};

