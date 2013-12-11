#pragma once
#include "SelfMovingPhysicalComponent.h"
class GameObject;
class CellPhysicalComponent :
	public SelfMovingPhysicalComponent
{
public:
	CellPhysicalComponent(GameObject *gameObject = NULL, PhysicalEngine *engine = NULL);
	~CellPhysicalComponent();

	CellPhysicalComponent *clone();
};

