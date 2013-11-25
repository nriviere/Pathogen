#pragma once
#include "SelfMovingPhysicalComponent.h"
class CellPhysicalComponent :
	public SelfMovingPhysicalComponent
{
public:
	CellPhysicalComponent();
	~CellPhysicalComponent();

	CellPhysicalComponent *clone();
};

