#include "PhysicalEngine.h"
#include "MyEngine.h"
#include "Level.h"
#include "UpdaterThread.h"

unsigned int ctest = 0;

PhysicalEngine::PhysicalEngine(MyEngine *engine)
{
	if (engine != NULL)
	{
		grid = new Grid(4, 4, engine->getCurrentLevel());
	}
	else
	{
		grid = NULL;
	}

	this->engine = engine;
	physicalComponents = NULL;
	collisions = new bool*[PhysicalComponent::MAX_COMPONENTS_COUNT];
	for (int i = 0; i < PhysicalComponent::MAX_COMPONENTS_COUNT; i++)
	{
		collisions[i] = new bool[PhysicalComponent::MAX_COMPONENTS_COUNT];
	}
}

PhysicalEngine::~PhysicalEngine()
{
	delete[]physicalComponents;
	for (int i = 0; i < PhysicalComponent::MAX_COMPONENTS_COUNT; i++)
	{
		delete [] collisions[i];
	}
	delete[] collisions;
}

void PhysicalEngine::setComponents(PhysicalComponent **physicalComponents, unsigned int componentCount)
{
	this->physicalComponents = physicalComponents;
	this->physicalComponentsCount = componentCount;
	for (int i = 0; i < componentCount; i++)
	{
		grid->set(this->physicalComponents[i]);
	}
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
		for (int i = 0; i < physicalComponentsCount; i++)
		{
			id1 = physicalComponents[i]->getID();
			for (int j = 0; j < physicalComponentsCount; j++)
			{
				id2 = physicalComponents[j]->getID();
				collisions[id1][id2] = collisions[id2][id2] = false;
			}

		}

		/*ctest = 0;
		for (int n = 0; n < grid->getN(); n++)
		{
			for (std::list<PhysicalComponent *>::iterator ite = grid->get(n)->begin(); ite != grid->get(n)->end();)
			{
				ctest++;
				++ite;
			}
		}*/

		//pthread_mutex_unlock(&UpdaterThread::test);
		grid->update();

		/*ctest = 0;
		for (int n = 0; n < grid->getN(); n++)
		{
			for (std::list<PhysicalComponent *>::iterator ite = grid->get(n)->begin(); ite != grid->get(n)->end();)
			{
				ctest++;
				++ite;
			}
		}*/

		//pthread_mutex_lock(&UpdaterThread::test);
		PhysicalComponent *p1, *p2;
		
		
		list<PhysicalComponent*> *L = NULL;
		list<PhysicalComponent*>::iterator end,begin;
		list<PhysicalComponent*>::iterator ite;
		Vect4 position;
		Level *level = engine->getCurrentLevel();;
		float limits[4] = { level->getLimitsX()[0], level->getLimitsX()[1], level->getLimitsY()[0], level->getLimitsY()[1] };
		float radius, radiussqr;
		for (int y = 0; y < grid->getNy(); y++)
		{
			for (int x = 0; x < grid->getNx(); x++)
			{
				L = grid->get(x, y);
				begin = L->begin();
				end = L->end();
				unsigned int gridcasesize = L->size();
				for (ite = begin;
					ite != end;)
				{
					p1 = (*ite);
					Vect4 position = p1->getPosition();
					radius = p1->getRadius();
					radiussqr = radius * radius;
					
					//collision avec le décor
					if (position[0] - radius <= limits[0])
					{
						p1->collision(Vect4(limits[0], 0, 0, 1));
					}
					if (position[0] + radius >= limits[1])
					{
						p1->collision(Vect4(limits[1], 0, 0, 1));
					}
					if (position[1] - radius <= limits[2])
					{
						p1->collision(Vect4(0, limits[2], 0, 1));
					}
					if (position[1] + radius >= limits[3])
					{
						p1->collision(Vect4(0, limits[3], 0, 1));
					}
					
					//collision avec les membres de la meme case de la grille
					id1 = p1->getID();
					
					for (list<PhysicalComponent*>::iterator ite2 = begin;
						ite2 != end;)
					{
						
						p2 = (*ite2);
						if (ite != ite2)
						{
							Vect4 aToB(p2->getPosition() - position);
							id2 = p2->getID();
							if (!collisions[id1][id2] && aToB.normesqr() <= (p2->getRadius()*p2->getRadius() + radiussqr))
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
						++ite2;
						
					}
					++ite;

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
		engine->getCursor()->getPhysicalComponent()->update();
	}
	/*
	ctest = 0;
	for (int n = 0; n < grid->getN(); n++)
	{
		for (std::list<PhysicalComponent *>::iterator ite = grid->get(n)->begin(); ite != grid->get(n)->end();)
		{
			ctest++;
			(*ite)->update();
			++ite;
		}
	}
	*/
	//pthread_mutex_unlock(&UpdaterThread::test);

	
	for (int i = 0; i < physicalComponentsCount; i++)
	{
		physicalComponents[i]->update();		
	}
	
	/*
	if (physicalComponents != NULL){
	for (int i = 0; i < physicalComponentsCount; i++)
	{
	Vect4 position = physicalComponents[i]->getTransform().getPos();
	float radius = physicalComponents[i]->getRadius();
	Level *level = engine->getCurrentLevel();

	if (position[0] - radius <= level->getLimitsX()[0])
	{
	physicalComponents[i]->collision(Vect4(level->getLimitsX()[0], 0, 0, 1));
	}
	if (position[0] + radius >= level->getLimitsX()[1])
	{
	physicalComponents[i]->collision(Vect4(level->getLimitsX()[1], 0, 0, 1));
	}
	if (position[1] - radius <= level->getLimitsY()[0])
	{
	physicalComponents[i]->collision(Vect4(0, level->getLimitsY()[0], 0, 1));
	}
	if (position[1] + radius >= level->getLimitsY()[1])
	{
	physicalComponents[i]->collision(Vect4(0, level->getLimitsY()[1], 0, 1));
	}

	for (int j = 0; j < physicalComponentsCount; j++)
	{

	Vect4 aToB(physicalComponents[j]->getPosition() - physicalComponents[i]->getPosition());
	/*if (i != j && aToB.norme() <= (physicalComponents[j]->getRadius() + physicalComponents[i]->getRadius()))
	{
	//physicalComponents[i]->collision(physicalComponents[j]);
	//exit(0);

	}
	Vect4 A = physicalComponents[j]->getPosition();
	Vect4 B = physicalComponents[i]->getPosition();
	Vect4 u = physicalComponents[i]->getSpeed();
	Vect4 BA = A-B;
	if (u.norme() != 0)
	{
	float d = ((B - A)^u).norme() / u.norme();
	float uDotBA = u*BA;
	if (i != j && d <= (physicalComponents[j]->getRadius() + physicalComponents[i]->getRadius()) && uDotBA < u.norme())
	{
	physicalComponents[i]->collision(physicalComponents[j]);
	}
	}
	A = physicalComponents[i]->getPosition();
	B = physicalComponents[j]->getPosition();
	u = physicalComponents[j]->getSpeed();
	if (u.norme() != 0)
	{
	float d = ((B - A)^u).norme() / u.norme();
	float uDotBA = u*BA;
	if (i != j && d <= (physicalComponents[i]->getRadius() + physicalComponents[j]->getRadius()) && abs(uDotBA) < u.norme())
	{
	physicalComponents[i]->collision(physicalComponents[j]);
	}
	}*/
	/*
	if (i != j && aToB.norme() <= (physicalComponents[j]->getRadius() + physicalComponents[i]->getRadius()))
	{
	physicalComponents[i]->collision(physicalComponents[j]);
	}


	}
	}
	*/
	

}

bool **PhysicalEngine::getCollisions(){
	return collisions;
}
MyEngine *PhysicalEngine::getEngine()
{
	return engine;
}