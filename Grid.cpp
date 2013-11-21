#include "Grid.h"

void Grid::init()
{
	updaterThreadCount = 4;
	updaterThreadCount = min(updaterThreadCount, nY);

	updaterThreads = new UpdaterThread*[updaterThreadCount];
	components = new std::list<PhysicalComponent*>*[componentsCount];
	unsigned int currentY = 0;
	for (int i = 0; i < componentsCount; i++)
	{
		components[i] = new std::list<PhysicalComponent*>();
	}

	std::list<PhysicalComponent*> ***parametersComponents = new std::list<PhysicalComponent*> **[updaterThreadCount];

	for (int i = 0; i < updaterThreadCount; i++)
	{
		unsigned int sizeY = ceil(1.*(nY - i) / updaterThreadCount),pos = 0;
		parametersComponents[i] = new std::list<PhysicalComponent*> *[sizeY*nX];
		for (int y = i; y < nY; y += updaterThreadCount)
		{
			for (int x = 0; x < nX; x++)
			{
				parametersComponents[i][pos++] = &(*components[y*nX + x]);
			}
		}
	}

	pthread_mutex_lock(&UpdaterThread::mutex_init);

	for (int i = 0; i < updaterThreadCount; i++)
	{
	
		updaterThreads[i] = new UpdaterThread(new UpdaterThreadParameters(updaterThreadCount, i, nX, nY, stepX, stepY, parametersComponents[i]));
		updaterThreads[i]->run();
	}

	
	pthread_cond_wait(&UpdaterThread::init_cond, &UpdaterThread::mutex_init);
	pthread_mutex_unlock(&UpdaterThread::mutex_init);
}

Grid::Grid(Level *level)
{
	setLimits(level);

	nY = nX = 10;

	dX = abs(limitsX[1] - limitsX[0]);
	dY = abs(limitsY[1] - limitsY[0]);
	stepX = dX / nX;
	stepY = dY / nY;
	componentsCount = nY*nX;
	init();
}

Grid::Grid(const Grid &grid)
{
	limitsX[0] = grid.limitsX[0]; limitsX[1] = grid.limitsX[1];
	limitsY[0] = grid.limitsY[0]; limitsY[1] = grid.limitsY[1];

	nY = grid.nY; nX = grid.nX;

	dX = abs(limitsX[1] - limitsX[0]);
	dY = abs(limitsY[1] - limitsY[0]);
	stepX = dX / nX;
	stepY = dY / nY;
	componentsCount = nY*nX;

	memcpy(components, grid.components, componentsCount*sizeof(PhysicalComponent*));
	updaterThreadCount = grid.updaterThreadCount;
	updaterThreads = new UpdaterThread*[updaterThreadCount];

	for (int i = 0; i < updaterThreadCount; i++)
	{
		updaterThreads[i] = grid.updaterThreads[i];

	}


}
Grid &Grid::operator=(const Grid &grid)
{
	Grid::Grid(grid);
	return (*this);
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
	componentsCount = nY*nX;
	init();
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
	componentsCount = nY*nX;
	init();
}

Grid::~Grid()
{
	for (int i = 0; i < updaterThreadCount; i++)
	{
		delete updaterThreads[i];
	}

	delete[]updaterThreads;
	for (int i = 0; i < componentsCount; i++)
	{
		delete components[i];
	}

	delete[]components;
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
	return components[n];
}

std::list<PhysicalComponent*> *Grid::get(unsigned int x, unsigned int y)
{
	return components[y*nX + x];
}

void Grid::set(PhysicalComponent* component)
{
	unsigned int uix, uiy;
	float fx = component->getPosition()[0], fy = component->getPosition()[1];
	uix = max(0, min(floor((fx - limitsX[0]) / stepX), nX - 1));
	uiy = max(0, min(floor((fy - limitsY[0]) / stepY), nY - 1));

	components[uiy * nX + uiy]->push_back(component);
}

unsigned int ctest2 = 0;

void Grid::update()
{

	pthread_mutex_lock(&UpdaterThread::mutex_finish);


	for (int i = 0; i < updaterThreadCount; i++)
	{
		updaterThreads[i]->lockWait();
	}
	
	pthread_cond_broadcast(&UpdaterThread::start_update);
	pthread_mutex_unlock(&UpdaterThread::mutex_start);
	
	for (int i = 0; i < updaterThreadCount; i++)
	{
		updaterThreads[i]->unlockWait();
	}
	
	pthread_cond_wait(&UpdaterThread::finish_cond, &UpdaterThread::mutex_finish);
	pthread_mutex_unlock(&UpdaterThread::mutex_finish);
	

	std::list<PhysicalComponent*> *reassignList = NULL;
	for (unsigned int i = 0; i < updaterThreadCount; i++)
	{
		reassignList = updaterThreads[i]->getReassignList();
		ite = reassignList->begin();
		end = reassignList->end();
		for (ite; ite != end;)
		{
			ctest2++;
			set(*ite);
			++ite;
		}
		reassignList->clear();
	}


	
	std::list<PhysicalComponent*> toReassign;
	unsigned int pos = 0;
	float fx = 0, fy = 0, minX = 0, maxX = 0, minY = 0, maxY = 0;

	for (unsigned int y = 0; y < nY; y++)
	{
		for (unsigned int x = 0; x < nX; x++)
		{
			pos = y*nX + x;
			minX = x*stepX; maxX = (x + 1)*stepX; minY = y*stepY; maxY = (y + 1)*stepY;
			end = components[pos]->end();
			for (ite = components[pos]->begin();
				ite != end;)
			{
				if ((*ite)->getPosition()[0] < minX || (*ite)->getPosition()[0] > maxX ||
					(*ite)->getPosition()[1] < minY || (*ite)->getPosition()[1] > maxY)
				{
					toReassign.push_front((*ite));
					ite = components[pos]->erase(ite);
				}
				else
				{
					++ite;
				}
			}
		}
	}
	end = toReassign.end();
	for (ite = toReassign.begin(); ite != end;)
	{
		set(*ite);
		++ite;
	}
	


}

void Grid::setLimits(Level *level)
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
}