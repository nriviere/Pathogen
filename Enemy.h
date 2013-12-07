#pragma once
#include "ReplicableGameObject.h"

class Cell;
class Hero;

class Enemy :
	public ReplicableGameObject
{
public:
	Enemy(GameEngine *engine = NULL);
	Enemy(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent, float replicateTime = 3);
	~Enemy();

	void hit(Cell *cell);
	void hit(Hero *hero);

	virtual void selfAdd();
	virtual void selfRemove();
	virtual void replicate() = 0;
};