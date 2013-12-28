#pragma once
#include "GameObject.h"
#include "Light.h"
class LightingGameObject :
	public GameObject
{
protected:
	Light *light;
public:
	LightingGameObject(GameEngine *engine = NULL);
	~LightingGameObject();
	Light *getLight();
	void setLight(Light *light);
	virtual void update();
	virtual void selfAdd();
	virtual void selfRemove();
};

