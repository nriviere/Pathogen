#pragma once
#include "PhysicalComponent.h"
#include "Grid.h"
class MyEngine;

class PhysicalEngine
{
private:
	PhysicalComponent **physicalComponents;
	MyEngine *engine;
	Grid *grid;
	bool **collisions;
	unsigned int physicalComponentsCount;
	PhysicalEngine();
	
public:
	PhysicalEngine(MyEngine *engine);
	~PhysicalEngine();

	void setComponents(PhysicalComponent **physicalComponents,unsigned int componentCount);
	void setGrid(Level *level);


	Grid *getGrid();
	PhysicalComponent ** getComponents();
	unsigned int getPhysicalComponentsCount();

	void update(float fDT);
	
	
};

