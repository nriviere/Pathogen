#include "CellPhysicalComponent.h"


CellPhysicalComponent::CellPhysicalComponent(GameObject *gameObject, PhysicalEngine *engine) : SelfMovingPhysicalComponent(gameObject,engine)
{
	
}


CellPhysicalComponent::~CellPhysicalComponent()
{
}

CellPhysicalComponent *CellPhysicalComponent::clone()
{
	return new CellPhysicalComponent(*this);
}