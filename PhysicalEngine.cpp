#include "PhysicalEngine.h"
#include "MyEngine.h"
#include "Level.h"


PhysicalEngine::PhysicalEngine(MyEngine *engine)
{
	this->engine = engine;
	physicalComponents = NULL;
}

PhysicalEngine::~PhysicalEngine()
{
	delete[]physicalComponents;
}

void PhysicalEngine::setComponents(PhysicalComponent **physicalComponents, unsigned int componentCount)
{
	this->physicalComponents = physicalComponents;
	this->physicalComponentsCount = componentCount;
}

PhysicalComponent **PhysicalEngine::getComponents()
{
	return physicalComponents;
}

unsigned int PhysicalEngine::getPhysicalComponentsCount()
{
	return physicalComponentsCount;
}

void PhysicalEngine::update(float fDT)
{
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
			if (i != j && aToB.norme() <= (physicalComponents[j]->getRadius() + physicalComponents[i]->getRadius()))
			{
				physicalComponents[i]->collision(physicalComponents[j]);
				//exit(0);
			}
		}
	}

	engine->getCursor()->getPhysicalComponent()->update();

	for (int i = 0; i < physicalComponentsCount; i++)
	{
		physicalComponents[i]->update();
	}
}