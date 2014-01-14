#pragma once
#include "ReplicableGameObject.h"
#include "SelfMovingPhysicalComponent.h"

class Cell;
class Hero;

class Enemy :
	public ReplicableGameObject
{
protected:
	SelfMovingPhysicalComponent *selfMovingPhysicalComponent;
public:
	Enemy(GameEngine *engine = NULL, float replicateTime = 3);
	Enemy(GameEngine *engine, RenderableComponent *model, SelfMovingPhysicalComponent *physicalComponent, float replicateTime = 3);
	~Enemy();

	void hit(Cell *cell);
	void hit(Hero *hero);

	virtual void selfAdd();
	virtual void selfRemove();
	virtual void replicate() = 0;
};