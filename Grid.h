#pragma once
#include "Level.h"
#include "PhysicalComponent.h"
#include <list>

class Grid
{
private:
	float limitsX[2], limitsY[2];
	float stepX,stepY,dX,dY;
	unsigned int nX, nY;
	std::list<PhysicalComponent*> *components;
	std::list<PhysicalComponent*>::iterator ite,end,begin;
public:
	Grid(Level *level = NULL);
	Grid(unsigned int nX, unsigned int nY, Level *level = NULL);
	Grid(float limitsX[2], float limitsY[2], unsigned int nX, unsigned int nY);
	~Grid();

	unsigned int getN();
	unsigned int getNx();
	unsigned int getNy();

	void update();
	std::list<PhysicalComponent*> *get(unsigned int n);
	std::list<PhysicalComponent*> *get(unsigned int x, unsigned int y);
	void set(PhysicalComponent* component);
	
};

