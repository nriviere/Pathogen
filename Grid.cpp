#include "Grid.h"

Grid::Grid(Level *level)
{
	if (level != NULL)
	{
		limitsX[0] = level->getLimitsX()[0]; limitsX[1] = level->getLimitsX()[1];
		limitsY[0] = level->getLimitsY()[0]; limitsY[1] = level->getLimitsY()[1];
	}
	else
	{
		limitsX[0] = limitsY[0] = -100;
		limitsX[1] = limitsY[1] = 100;
	}

	nY = nX = 10;
	
	dX = abs(limitsX[1] - limitsX[0]);
	dY = abs(limitsY[1] - limitsY[0]);
	stepX = dX / nX;
	stepY = dY / nY;
	components = new std::list<PhysicalComponent*>[nY*nX];
}

Grid::Grid(unsigned int nX, unsigned int nY, Level *level)
{
	if (level != NULL)
	{
		limitsX[0] = level->getLimitsX()[0]; limitsX[1] = level->getLimitsX()[1];
		limitsY[0] = level->getLimitsY()[0]; limitsY[1] = level->getLimitsY()[1];
	}
	else
	{
		limitsX[0] = limitsY[0] = -100;
		limitsX[1] = limitsY[1] = 100;
	}

	this->nX = nY;
	this->nY = nY;

	dX = abs(limitsX[1] - limitsX[0]);
	dY = abs(limitsY[1] - limitsY[0]);
	stepX = dX / nX;
	stepY = dY / nY;
	components = new std::list<PhysicalComponent*>[nY*nX];
}

Grid::Grid(float limitsX[2], float limitsY[2], unsigned int nX, unsigned int nY)
{
	this->limitsX[0] = limitsX[0]; this->limitsX[1] = limitsX[1];
	this->limitsY[0] = limitsY[0]; this->limitsY[1] = limitsY[1];

	this->nX = nX;
	this->nY = nY;

	dX = abs(limitsX[1] - limitsX[0]);
	dY = abs(limitsY[1] - limitsY[0]);
	stepX = dX / nX;
	stepY = dY / nY;
	components = new std::list<PhysicalComponent*>[nY*nX];
}

Grid::~Grid()
{
	delete[] components;
}

unsigned int Grid::getN()
{
	return nX * nY;
}

unsigned int Grid::getNx()
{
	return nX;
}
unsigned int Grid::getNy()
{
	return nY;
}

std::list<PhysicalComponent*> *Grid::get(unsigned int n)
{
	return &components[n];
}

std::list<PhysicalComponent*> *Grid::get(unsigned int x, unsigned int y)
{
	return &components[y*nX + x];
}

void Grid::set(PhysicalComponent* component)
{
	unsigned int uix, uiy;
	float fx = component->getPosition()[0], fy = component->getPosition()[1];
	uix = max(0,min(floor((fx - limitsX[0]) / stepX), nX - 1));
	uiy = max(0,min(floor((fy - limitsY[0]) / stepY), nY - 1));

	components[uiy * nX + uiy].push_back(component);
}

void Grid::update()
{
	unsigned int pos = 0;
	float fx = 0, fy = 0, minX = 0, maxX = 0, minY = 0, maxY = 0;
	std::list<PhysicalComponent*> toReassign;
	for (unsigned int y = 0; y < nY; y++)
	{
		for (unsigned int x = 0; x < nX; x++)
		{
			pos = y*nX + x;
			minX = x*stepX; maxX = (x + 1)*stepX; minY = y*stepY; maxY = (y + 1)*stepY;
			end = components[pos].end();
			for (ite = components[pos].begin();
				ite != end;)
			{
				if ((*ite)->getPosition()[0] < minX || (*ite)->getPosition()[0] > maxX ||
					(*ite)->getPosition()[1] < minY || (*ite)->getPosition()[1] > maxY)
				{
					toReassign.push_front((*ite));
					ite = components[pos].erase(ite);
				}
				else
				{
					++ite;
				}
			}
		}
	}

	end = toReassign.end();
	for (ite = toReassign.begin();
		ite != end;)
	{
		set((*ite));
		++ite;
	}
}
