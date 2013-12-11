#include "GameEngine.h"
#include "MyEngine.h"
#include "HeroPhysicalComponent.h"
#include "SelfMovingPhysicalComponent.h"
#include "Cell.h"
#include "Bacteria.h"
#include "CellPhysicalComponent.h"

unsigned int GameEngine::MAX_CELL_COUNT = 50;
unsigned int GameEngine::CURRENT_CELL_COUNT = 0;

GameEngine::GameEngine(MyEngine *engine) : engine(engine)
{
	gameObjectCount = 0;
	particleSystemCount = 0;
	particleCount = 0;
	gameStates = new GameState*[2];
	gameStates[0] = new MainMenuState(this);
	inGameState = new InGameState(this);
	gameStates[1] = inGameState;
	currentGameState = gameStates[0];
	levelCount = 1;
	levels = new Level*[levelCount];
	levels[0] = currentLevel = new Level("Levels/level1.xml",this);
	cursor = new Cursor();
	indexer = new Indexer(MAX_GAME_OBJECT_COUNT);
	particleSystemIndexer = new Indexer(MAX_PARTICLE_SYSTEM_COUNT);
	particleSystems = new ParticleSystem*[MAX_PARTICLE_SYSTEM_COUNT];
	for (int i = 0; i < MAX_PARTICLE_SYSTEM_COUNT; i++)
	{
		particleSystems[i] = NULL;
	}
	hero = NULL;
}

GameEngine::~GameEngine()
{
	for (int i = 0; i < gameStateCount; i++)
	{
		delete gameStates[i];
	}
	delete[] gameStates;
	for (int i = 0; i < levelCount; i++)
	{
		delete levels[i];
	}
	for (int i = 0; i < MAX_GAME_OBJECT_COUNT; i++)
	{
		if (gameObjects[i] != NULL)
		{
			remove(gameObjects[i]->getGameEngineIndex());
		}
	}

	for (int i = 0; i < MAX_PARTICLE_SYSTEM_COUNT; i++)
	{
		if (particleSystems[i] != NULL)
		{
			removeParticleSystem(gameObjects[i]->getGameEngineIndex());
		}
	}
	delete [] gameObjects;
	delete [] levels;
	delete cursor;
	delete hero;
}

void GameEngine::setup()
{
	currentGameState->setup();
}

void GameEngine::update(float fDT)
{
	currentGameState->update(fDT);
}

void GameEngine::load(const char** fileNames, unsigned int count) //charger a partir d'un fichier level
{
	SCENE **objects = new SCENE*[count];

	for (int i = 0; i < count; i++)
	{
		objects[i] = ReadOBJFile(fileNames[i], true);
	}

	//unsigned int objectCount = 0;

	Renderer *renderer = engine->getRenderer();
	PhysicalEngine *physicalEngine = engine->getPhysicalEngine();

	renderer->load(objects, count);
	
	gameObjects = new GameObject*[MAX_GAME_OBJECT_COUNT];
	for (int i = 0; i < MAX_GAME_OBJECT_COUNT; i++)
	{
		gameObjects[i] = NULL;
	}
	PhysicalComponent *physicalComponent = new HeroPhysicalComponent(cursor);
	physicalComponent->setPosition(Vect4(0, 0, 0, 1));
	hero = new Hero(this, &renderer->getModels()[0], physicalComponent);
	addObject(hero);

	currentLevel->load();
	currentLevel->init();

	/*
	for (int i = 1; i < objectCount/2; i++)
	{
		float x = currentLevel->getLimitsX()[0] + (1.*rand() / RAND_MAX) * (currentLevel->getLimitsX()[1] - currentLevel->getLimitsX()[0]);
		float y = currentLevel->getLimitsY()[0] + (1.*rand() / RAND_MAX) * (currentLevel->getLimitsY()[1] - currentLevel->getLimitsY()[0]);
		physicalComponent = new CellPhysicalComponent();
		physicalComponent->setPosition(Vect4(x, y, 0, 1));
		RenderableComponent *component = &renderer->getModels()[1];
		Cell *cell = new Cell(this, &renderer->getModels()[1], physicalComponent);
		addObject(cell);
	}
	for (int i = objectCount / 2; i < objectCount; i++)
	{
		float x = currentLevel->getLimitsX()[0] + (1.*rand() / RAND_MAX) * (currentLevel->getLimitsX()[1] - currentLevel->getLimitsX()[0]);
		float y = currentLevel->getLimitsY()[0] + (1.*rand() / RAND_MAX) * (currentLevel->getLimitsY()[1] - currentLevel->getLimitsY()[0]);
		physicalComponent = new CellPhysicalComponent();
		physicalComponent->setPosition(Vect4(x, y, 0, 1));
		Bacteria *bacteria = new Bacteria(this,physicalComponent);
		addObject(bacteria);
	}
	*/
	physicalEngine->setGrid(currentLevel);
}


void GameEngine::display(unsigned int u32Width, unsigned int u32Height)
{
	currentGameState->display(u32Width, u32Height);
}

void GameEngine::mouseMove(POINT Pos)
{
	currentGameState->mouseMove(Pos);
}

void GameEngine::lButtonDown(POINT Pt)
{
	currentGameState->lButtonDown(Pt);
}

void GameEngine::lButtonUp(POINT Pt)
{
	currentGameState->lButtonUp(Pt);
}

void GameEngine::keyDown(int s32VirtualKey)
{
	currentGameState->keyDown(s32VirtualKey);
}

void GameEngine::keyUp(int s32VirtualKey)
{
	currentGameState->keyUp(s32VirtualKey);
}

GameObject **GameEngine::getGameObjects()
{
	return gameObjects;
}

ParticleSystem **GameEngine::getParticleSystems()
{
	return particleSystems;
}

unsigned int GameEngine::getGameObjectCount()
{
	return gameObjectCount;
}

unsigned int GameEngine::getParticleSystemCount()
{
	return particleSystemCount;
}

Hero *GameEngine::getHero()
{
	return hero;
}

Cursor *GameEngine::getCursor()
{
	return cursor;
}

Level *GameEngine::getCurrentLevel()
{
	return currentLevel;
}

MyEngine *GameEngine::getParentEngine()
{
	return engine;
}

InGameState *GameEngine::getInGameState()
{
	return inGameState;
}

void GameEngine::setHero(Hero *hero)
{
	if (this->hero != NULL && hero->getGameEngineIndex() != this->hero->getGameEngineIndex())
	{
		unsigned int heroIndex = this->hero->getGameEngineIndex();
		engine->getPhysicalEngine()->remove(heroIndex);
		delete gameObjects[heroIndex];
		gameObjects[heroIndex] = NULL;
		indexer->releaseIndex(heroIndex);
		gameObjectCount--;
	}
	this->hero = hero;
}

void GameEngine::addObject(GameObject * object)
{
	unsigned int index = indexer->getNextIndex();

	if (index != UINT_MAX)
	{
		object->setGameEngineIndex(index);
		object->setGameEngine(this);
		gameObjects[index] = object;
		gameObjectCount++;
		engine->getPhysicalEngine()->addPhysicalComponent(object->getPhysicalComponent());
		object->selfAdd();
	}
	else
	{
		//exit(-30);
	}

}

void GameEngine::addParticleSystems()
{
	/*ParticleSystem *particleSystem;
	while (!particleSystemsToAdd.empty())
	{
		particleSystem = particleSystemsToAdd.front();

		unsigned int index = particleSystemIndexer->getNextIndex();

		if (index != UINT_MAX)
		{
			particleSystem->setGameEngineIndex(index);
			particleSystem->setGameEngine(this);
			particleSystems[index] = particleSystem;
			particleSystemCount++;
			Particle **particles = particleSystem->getParticles();
			for (int i = 0; i < particleSystem->getMaxParticleCount(); i++)
			{
				if (particles[i] != NULL)
				{
					engine->getPhysicalEngine()->addPhysicalComponent(particles[i]->getPhysicalComponent());
				}
			}
		}
		else
		{
			exit(-30);
		}
		particleSystemsToAdd.pop_front();
	}*/
}

void GameEngine::addParticleSystem(ParticleSystem *particleSystem)
{
	//particleSystemsToAdd.push_back(particleSystem);
	unsigned int index = particleSystemIndexer->getNextIndex();

	particleSystem->setGameEngineIndex(index);
	particleSystem->setGameEngine(this);
	particleSystems[index] = particleSystem;
	
	particleSystemCount++;
	Particle **particles = particleSystem->getParticles();
	for (int i = 0; i < particleSystem->getMaxParticleCount(); i++)
	{
		if (particles[i] != NULL)
		{
			engine->getPhysicalEngine()->addPhysicalComponent(particles[i]->getPhysicalComponent());
		}
	}
	particleSystem->selfAdd();

}

void GameEngine::remove(unsigned int index)
{
	if (index < MAX_GAME_OBJECT_COUNT && gameObjects[index] != NULL)
	{
		engine->getPhysicalEngine()->remove(gameObjects[index]->getPhysicalComponent()->getEngineIndex());
		gameObjects[index]->selfRemove();
		delete gameObjects[index];
		gameObjects[index] = NULL;
		indexer->releaseIndex(index);
		gameObjectCount--;
	}
}

void GameEngine::removeParticleSystem(unsigned int index)
{
	if (index < MAX_PARTICLE_SYSTEM_COUNT && particleSystems[index] != NULL)
	{
		particleSystems[index]->selfRemove();
		delete particleSystems[index];
		particleSystems[index] = NULL;
		particleSystemIndexer->releaseIndex(index);
		particleSystemCount--;
	}
}

void GameEngine::setToRemove(GameObject *gameObject)
{
	toRemove.push_back(gameObject);
}

void GameEngine::setToRemove(unsigned int gameObjectIndex)
{
	setToRemove(gameObjects[gameObjectIndex]);
}

void GameEngine::setParticleSystemToRemove(ParticleSystem *particleSystem)
{
	if (particleSystem != NULL)
	{
		if (particleSystem->getEngineIndex() != UINT_MAX)
		{
			particleSystemsToRemove.push_back(particleSystem);
		}
	}
}

void GameEngine::remove()
{
	while (!toRemove.empty())
	{
		remove(toRemove.front()->getGameEngineIndex());
		toRemove.pop_front();
	}
	while (!particleSystemsToRemove.empty())
	{
		removeParticleSystem(particleSystemsToRemove.front()->getEngineIndex());
		particleSystemsToRemove.pop_front();
	}
}

void GameEngine::nextState(int id)
{
	currentGameState = gameStates[id];
	setup();
}