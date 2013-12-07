#include "SpawnPool.h"
#include "GameEngine.h"

SpawnPool::SpawnPool()
{
}


SpawnPool::~SpawnPool()
{
}

void SpawnPool::addObject(GameObject *object)
{
	object->setSpawnPool(this);
	gameObjects.push_back(object);
}

void SpawnPool::addObjects(GameObject **objects, unsigned int count)
{
	for (int i = 0; i < count; i++)
	{
		addObject(objects[i]);
	}
}

void SpawnPool::loadToEngine(GameEngine *engine)
{
	for (list<GameObject*>::iterator o = gameObjects.begin(); o != gameObjects.end();)
	{
		engine->addObject(*o);
		++o;
	}
}

void SpawnPool::removeObject(GameObject *object)
{
	gameObjects.remove(object);
}

bool SpawnPool::isEmpty()
{
	return gameObjects.size() == 0;
}