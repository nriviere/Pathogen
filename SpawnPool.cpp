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
		Vect4 limitsX = engine->getCurrentLevel()->getLimitsX();
		Vect4 limitsY = engine->getCurrentLevel()->getLimitsY();
		while (((*o)->getPhysicalComponent()->getPosition() - engine->getHero()->getPhysicalComponent()->getPosition()).norme() < 150)
		{
			float x = limitsX[0] + (1.*rand() / RAND_MAX) * (limitsX[1] - limitsX[0]);
			float y = limitsY[0] + (1.*rand() / RAND_MAX) * (limitsY[1] - limitsY[0]);
			(*o)->getPhysicalComponent()->setPosition(Vect4(x, y, 0, 1));
		}
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