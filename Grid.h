#pragma once
#include "Level.h"
#include "PhysicalComponent.h"
#include "UpdaterThread.h"
#include <list>

class Grid
{
private:
	float limitsX[2], limitsY[2];
	float stepX,stepY,dX,dY;
	unsigned int nX, nY, componentsCount, updaterThreadCount;
	std::list<PhysicalComponent*> **components;
	std::list<PhysicalComponent*>::iterator ite,end,begin;
	UpdaterThread **updaterThreads;

	void init();
	
public:
	Grid(Level *level = NULL);
	Grid(unsigned int nX, unsigned int nY, Level *level = NULL);
	Grid(float limitsX[2], float limitsY[2], unsigned int nX, unsigned int nY);
	~Grid();

	Grid(const Grid &grid);
	Grid &operator=(const Grid &);
	
	unsigned int getN();
	unsigned int getNx();
	unsigned int getNy();
	
/*	unsigned int getDy();
	unsigned int getComponentsCount();
	unsigned int getUpdaterThreadCount();
	unsigned int *getLimitsX();
	unsigned int *getLimitsY();
	
	std::list<PhysicalComponent*> *getComponents();*/

	void update();
	std::list<PhysicalComponent*> *get(unsigned int n);
	std::list<PhysicalComponent*> *get(unsigned int x, unsigned int y);
	std::list<PhysicalComponent*> *get(float x, float y);
	std::list<std::list<PhysicalComponent*>*> getNeighborhood(float x, float y, float radius);
	void set(PhysicalComponent* component);
	void setLimits(Level *level);	
};

