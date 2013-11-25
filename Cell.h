#pragma once
#include "GameObject.h"
#include "ReplicableGameObject.h"

class Cell :
	public ReplicableGameObject
{
public:
	Cell(GameEngine *engine = NULL);
	Cell(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent);
	Cell(const Cell &cell);
	Cell &operator=(const Cell &cell);
	~Cell();

	void replicate();
};

