#pragma once
#include "SpawnPool.h"
#include <list>

using namespace std;

class Level;

class SpawnLine
{
private :
	Level *level;
	list<SpawnPool *> spawnPools;
public:
	SpawnLine(Level *level = NULL);
	~SpawnLine();
	void addSpawnPool(SpawnPool *spawnPool);
	void update();
	void loadToEngine();
	bool isEmpty();
};

