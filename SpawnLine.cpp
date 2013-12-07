#include "SpawnLine.h"
#include "Level.h"

SpawnLine::SpawnLine(Level *level)
{
	this->level = level;
}


SpawnLine::~SpawnLine()
{
}

void SpawnLine::addSpawnPool(SpawnPool *spawnPool)
{
	spawnPools.push_back(spawnPool);
}

void SpawnLine::update()
{
	if (spawnPools.size() != 0)
	{
		if (spawnPools.front()->isEmpty())
		{
			delete spawnPools.front();
			spawnPools.pop_front();
			loadToEngine();
		}
	}
}

void SpawnLine::loadToEngine()
{
	if (spawnPools.size() != 0)
	{
		if (!spawnPools.front()->isEmpty())
		{
			spawnPools.front()->loadToEngine(level->getGameEngine());
		}
	}
}

bool SpawnLine::isEmpty()
{
	return spawnPools.size() == 0;
}