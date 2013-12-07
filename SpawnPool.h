#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include <list>

class GameEngine;

class SpawnPool
{
private:
	std::list<GameObject*> gameObjects;

public:
	SpawnPool();
	~SpawnPool();
	void addObjects(GameObject **objects, unsigned int count);
	void addObject(GameObject *object);
	void loadToEngine(GameEngine *engine);
	void removeObject(GameObject *object);
	bool isEmpty();
};

