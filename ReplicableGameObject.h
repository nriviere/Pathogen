#pragma once
#include "GameObject.h"
#include "Timer.h"

class GameEngine;

class ReplicableGameObject :
	public GameObject
{
protected:
	float replicateTime;
	Timer *replicateTimer;
public:
	ReplicableGameObject();
	ReplicableGameObject(GameEngine *engine,float replicateTime = 3);
	ReplicableGameObject(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent, float replicateTime = 3);
	ReplicableGameObject(const ReplicableGameObject &object);
	ReplicableGameObject &operator=(const ReplicableGameObject &object);
	~ReplicableGameObject();
	virtual void replicate()=0;
	virtual void update();
	virtual void selfAdd();
	virtual void selfRemove();
};

