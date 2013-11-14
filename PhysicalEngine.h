#pragma once
#include "PhysicalComponent.h"

class MyEngine;

class PhysicalEngine
{
private:
	PhysicalComponent **physicalComponents;
	MyEngine *engine;
	unsigned int physicalComponentsCount;
public:
	PhysicalEngine(MyEngine *engine = NULL);
	~PhysicalEngine();

	void setComponents(PhysicalComponent **physicalComponents,unsigned int componentCount);
	PhysicalComponent ** getComponents();

	void update(float fDT);

	unsigned int getPhysicalComponentsCount();
};

