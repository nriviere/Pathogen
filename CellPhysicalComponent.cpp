#include "CellPhysicalComponent.h"


CellPhysicalComponent::CellPhysicalComponent()
{
	
}


CellPhysicalComponent::~CellPhysicalComponent()
{
}

CellPhysicalComponent *CellPhysicalComponent::clone()
{
	return new CellPhysicalComponent(*this);
}