#include "PhysicalEngine.h"
#include "MyEngine.h"
#include "Level.h"
#include "UpdaterThread.h"
#include "Indexer.h"

unsigned int ctest = 0;

PhysicalEngine::PhysicalEngine(MyEngine *engine)
{
	if (engine != NULL)
	{
		grid = new Grid(16,16, engine->getGameEngine()->getCurrentLevel());
	}
	else
	{
		grid = NULL;
	}

	this->engine = engine;
	physicalComponents = new PhysicalComponent*[MAX_PHYSICAL_COMPONENT_COUNT];

	collisions = new bool*[MAX_PHYSICAL_COMPONENT_COUNT];
	for (int i = 0; i < MAX_PHYSICAL_COMPONENT_COUNT; i++)
	{
		collisions[i] = new bool[MAX_PHYSICAL_COMPONENT_COUNT];
		physicalComponents[i] = NULL;
	}
	indexer = new Indexer(MAX_PHYSICAL_COMPONENT_COUNT);
	physicalComponentsCount = 0;

	for (int i = 0; i < MAX_PHYSICAL_COMPONENT_COUNT; i++)
	{
		for (int j = 0; j < MAX_PHYSICAL_COMPONENT_COUNT; j++)
		{
			collisions[i][j] = false;
		}
	}


}

PhysicalEngine::~PhysicalEngine()
{
	delete[]physicalComponents;
	for (int i = 0; i < MAX_PHYSICAL_COMPONENT_COUNT; i++)
	{
		delete[] collisions[i];
	}
	delete[] collisions;
}


void PhysicalEngine::setGrid(Level *level)
{
	grid->setLimits(level);
}

PhysicalComponent **PhysicalEngine::getComponents()
{
	return physicalComponents;
}

unsigned int PhysicalEngine::getPhysicalComponentsCount()
{
	return physicalComponentsCount;
}

Grid *PhysicalEngine::getGrid(){
	return grid;
}

void PhysicalEngine::update(float fDT)
{

	//pthread_mutex_lock(&UpdaterThread::test);
	if (grid != NULL)
	{
		unsigned int id1 = 0, id2 = 0;
		/*for (int i = 0; i < physicalComponentsCount; i++)
		{
		if (physicalComponents[i] != NULL)
		{
		id1 = physicalComponents[i]->getEngineIndex();
		for (int j = 0; j < physicalComponentsCount; j++)
		{
		if (physicalComponents[j] != NULL)
		{
		id2 = physicalComponents[j]->getEngineIndex();
		collisions[id1][id2] = collisions[id2][id2] = false;
		}
		}
		}

		}*/

		grid->update();
		for (int i = 0; i < MAX_PHYSICAL_COMPONENT_COUNT; i++)
		{
			if (physicalComponents[i] != NULL)
			{
				physicalComponents[i]->update();
			}
		}
		PhysicalComponent *p1, *p2;


		list<PhysicalComponent*> *L = NULL;
		list<PhysicalComponent*>::iterator end, begin;
		list<PhysicalComponent*>::iterator ite;
		Vect4 position;
		Level *level = engine->getGameEngine()->getCurrentLevel();;
		float limits[4] = { level->getLimitsX()[0], level->getLimitsX()[1], level->getLimitsY()[0], level->getLimitsY()[1] };
		float radius, radiussqr;
		int maxX = grid->getNx();
		int maxY = grid->getNy();
		for (unsigned int y = 0; y < maxY; y++)
		{
			for (unsigned int x = 0; x < maxX; x++)
			{
				L = grid->get(x, y);
				begin = L->begin();
				end = L->end();
				unsigned int gridcasesize = L->size();
				list<list<PhysicalComponent *> *> neighbours;
				unsigned int yii = 0, xii = 0;
				for (int yi = -1; yi < 2; yi++)
				{
					for (int xi = -1; xi < 2; xi++)
					{
						xii = x + xi;
						yii = y + yi;
						if (xii >= 0 && xii < maxX && yii >= 0 && yii < maxY)
						{
							neighbours.push_back(grid->get(xii, yii));
						}
					}
				}

				for (ite = begin;
					ite != end;)
				{
					if (*ite != NULL)
					{

						p1 = (*ite);
						id1 = p1->getEngineIndex();
						Vect4 position = p1->getPosition();
						radius = p1->getRadius();
						radiussqr = radius * radius;

						//collision avec le décor
						if (position[0] - radius <= limits[0])
						{
							p1->collision(Vect4(limits[0], 0, 0, 1));
						} else if (position[0] + radius >= limits[1])
						{
							p1->collision(Vect4(limits[1], 0, 0, 1));
						}
						if (position[1] - radius <= limits[2])
						{
							p1->collision(Vect4(0, limits[2], 0, 1));
						} else if (position[1] + radius >= limits[3])
						{
							p1->collision(Vect4(0, limits[3], 0, 1));
						}

						//collision avec les membres de la meme case de la grille

						for (list<list<PhysicalComponent *>*>::iterator neigh = neighbours.begin(); neigh != neighbours.end();)
						{
							checkCollisions(*neigh, ite);
							++neigh;
						}

						++ite;
					}
				}
			}
		}
	}
	else
	{
		//error
	}

	if (engine != NULL)
	{
		engine->getGameEngine()->getCursor()->getPhysicalComponent()->update();
	}



}

void PhysicalEngine::checkCollisions(list<PhysicalComponent *> *components, list<PhysicalComponent *>::iterator &componentIterator)
{
	PhysicalComponent *p2, *p1;
	p1 = *componentIterator;
	unsigned int id1, id2;
	id1 = p1->getEngineIndex();
	for (list<PhysicalComponent*>::iterator ite2 = components->begin();
		ite2 != components->end();)
	{
		p2 = (*ite2);
		id2 = p2->getEngineIndex();
		if (p2 != NULL)
		{
			if (id1 != id2)
			{
				Vect4 aToB(p2->getPosition() - p1->getPosition());
				id2 = p2->getEngineIndex();
				if (p2 != NULL && aToB.normesqr() <= (p2->getRadius()*p2->getRadius() + p1->getRadius()*p1->getRadius()))
				{
					if (!collisions[id1][id2])
					{
						p1->collision(p2);
						p2->collision(p1);
						collisions[id1][id2] = collisions[id2][id1] = true;
					}
					else
					{
						collisions[id1][id2] = collisions[id2][id1] = false;
					}
				}

			}
		}
		++ite2;

	}
}

void PhysicalEngine::addPhysicalComponent(PhysicalComponent *component)
{
	unsigned int index = indexer->getNextIndex();
	if (index != UINT_MAX)
	{
		physicalComponents[index] = component;
		component->setEngineIndex(index);
		component->setEngine(this);
		grid->set(component);
		physicalComponentsCount++;
	}
	else
	{
		//exit(-30);
	}
}

bool **PhysicalEngine::getCollisions(){
	return collisions;
}
MyEngine *PhysicalEngine::getEngine()
{
	return engine;
}

void PhysicalEngine::remove(unsigned int index)
{
	if (index < MAX_PHYSICAL_COMPONENT_COUNT && physicalComponents[index] != NULL)
	{
		PhysicalComponent *comp = physicalComponents[index];
		grid->get(comp->getGridX(), comp->getGridY())->erase(comp->getGridPosition());
		//(*comp->getGridPosition()) = NULL;
		delete physicalComponents[index];
		physicalComponents[index] = NULL;

		indexer->releaseIndex(index);
		physicalComponentsCount--;
	}
	else
	{
		cout << "lol" << endl;
	}
}
