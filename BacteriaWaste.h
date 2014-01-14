#pragma once
#include "GameObject.h"

class GameEngine;
class BacteriaWastePhysicalComponent;

class BacteriaWaste :
	public GameObject
{
protected:
	BacteriaWastePhysicalComponent *bacteriaWastePhysicalComponent;
public:
	BacteriaWaste(GameEngine *engine=NULL);
	BacteriaWaste(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent);
	~BacteriaWaste();
	virtual void hitBy(GameObject *gameObject);
	void destroy();
};

