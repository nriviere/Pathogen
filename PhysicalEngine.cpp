#include "PhysicalEngine.h"
#include "MyEngine.h"
#include "Level.h"


PhysicalEngine::PhysicalEngine(MyEngine *engine)
{
	if (engine != NULL)
	{
		grid = new Grid(6, 4, engine->getCurrentLevel());
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

void PhysicalEngine::setGrid(Grid *grid)
{
	delete this->grid;
	this->grid = grid;
}

void PhysicalEngine::setGrid(Level *level)
{
	this->grid = new Grid(level);
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
		grid->update();
		PhysicalComponent *p1, *p2;
		
		for (int y = 0; y < grid->getNy(); y++)
		{
			for (int x = 0; x < grid->getNx(); x++)
			{
				list<PhysicalComponent*>::iterator end = grid->get(x, y)->end();
				for (list<PhysicalComponent*>::iterator ite = grid->get(x,y)->begin();
					ite != end;)
				{
					p1 = (*ite);
					Vect4 position = p1->getTransform().getPos();
					float radius = p1->getRadius();
					Level *level = engine->getCurrentLevel();

					//collision avec le décor
					if (position[0] - radius <= level->getLimitsX()[0])
					{
						p1->collision(Vect4(level->getLimitsX()[0], 0, 0, 1));
					}
					if (position[0] + radius >= level->getLimitsX()[1])
					{
						p1->collision(Vect4(level->getLimitsX()[1], 0, 0, 1));
					}
					if (position[1] - radius <= level->getLimitsY()[0])
					{
						p1->collision(Vect4(0, level->getLimitsY()[0], 0, 1));
					}
					if (position[1] + radius >= level->getLimitsY()[1])
					{
						p1->collision(Vect4(0, level->getLimitsY()[1], 0, 1));
					}

					//collision avec les membres de la meme case de la grille
					id1 = p1->getID();
					
					for (list<PhysicalComponent*>::iterator ite2 = grid->get(x,y)->begin();
						ite2 != end;)
					{
						unsigned int gridcasesize = grid->get(x, y)->size();
						p2 = (*ite2);
						if (ite != ite2)
						{
							Vect4 aToB(p2->getPosition() - p1->getPosition());
							id2 = p2->getID();
							if (!collisions[id1][id2] && aToB.norme() <= (p2->getRadius() + p1->getRadius()))
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