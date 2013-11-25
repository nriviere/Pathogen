#pragma once
#include "PhysicalComponent.h"
#include "Grid.h"
#include "Indexer.h"
class MyEngine;

class PhysicalEngine
{
private:
	PhysicalComponent **physicalComponents;
	MyEngine *engine;
	Grid *grid;
	bool **collisions;
	unsigned int physicalComponentsCount;
	Indexer *indexer;
	PhysicalEngine();

	
public:
	PhysicalEngine(MyEngine *engine);
	~PhysicalEngine();

	void setGrid(Level *level);


	Grid *getGrid();
	PhysicalComponent ** getComponents();
	unsigned int getPhysicalComponentsCount();
	void addPhysicalComponent(PhysicalComponent *component);

	bool **getCollisions();
	MyEngine *getEngine();

	void update(float fDT);
	void remove(unsigned int index);
	
	
};

