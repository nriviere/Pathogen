#include "GameEngine.h"
#include "MyEngine.h"
#include "HeroPhysicalComponent.h"
#include "SelfMovingPhysicalComponent.h"
#include "Cell.h"
#include "Bacteria.h"
#include "CellPhysicalComponent.h"
#include "HelpState.h"
#include "GameOverState.h"


unsigned int GameEngine::MAX_CELL_COUNT = 50;
unsigned int GameEngine::CURRENT_CELL_COUNT = 0;

GameEngine::GameEngine(MyEngine *engine) : engine(engine)
{
	gameObjectCount = 0;
	particleSystemCount = 0;
	particleCount = 0;
	enemyCount = 0;
	fDT = 0;
	gameStates = new GameState*[6];
	gameStates[0] = new MainMenuState(this);
	gameStates[1] = briefingState = new BriefingState(this);
	inGameState = new InGameState(this);
	gameStates[2] = inGameState;
	gameStates[3] = new HelpState(this);
	debriefingState = new DebriefingState(this);
	gameStates[4] = debriefingState;
	gameOverState = new GameOverState(this);
	gameStates[5] = gameOverState;

	gameStateCount = 6;
	currentGameState = gameStates[0];
	levelCount = 5;
	levels = new Level*[levelCount];
	levels[0] = currentLevel = new Level("Levels/level1.xml", this);
	levels[1] = new Level("Levels/level2.xml", this);
	levels[2] = new Level("Levels/level3.xml", this);
	levels[3] = new Level("Levels/level4.xml", this);
	levels[4] = new Level("Levels/level5.xml", this);
	currentLevelId = 0;



	cursor = new Cursor();
	indexer = new Indexer(MAX_GAME_OBJECT_COUNT);
	particleSystemIndexer = new Indexer(MAX_PARTICLE_SYSTEM_COUNT);
	particleSystems = new ParticleSystem*[MAX_PARTICLE_SYSTEM_COUNT];
	for (int i = 0; i < MAX_PARTICLE_SYSTEM_COUNT; i++)
	{
		particleSystems[i] = NULL;
	}
	hero = NULL;

	gameObjects = new GameObject*[MAX_GAME_OBJECT_COUNT];
	for (int i = 0; i < MAX_GAME_OBJECT_COUNT; i++)
	{
		gameObjects[i] = NULL;
	}

	finished = false;
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

void GameEngine::init(){
	char **names = new char*[levelCount];
	names[0] = "assets/briefing/brief_lvl1.tga";
	names[1] = "assets/briefing/brief_lvl2.tga";
	names[2] = "assets/briefing/brief_lvl3.tga";
	names[3] = "assets/briefing/brief_lvl4.tga";
	names[4] = "assets/briefing/brief_lvl5.tga";

	briefingState->setBriefingScreens(names, 5);
	delete[] names;
}
void GameEngine::update(float fDT)
{
	this->fDT = fDT;
	currentGameState->update(fDT);
}

/*
void GameEngine::init()
{
	//unsigned int objectCount = 0;

	Renderer *renderer = engine->getRenderer();
	PhysicalEngine *physicalEngine = engine->getPhysicalEngine();

	
	//bouger le hero
	PhysicalComponent *physicalComponent = new HeroPhysicalComponent(cursor);
	physicalComponent->setPosition(Vect4(0, 0, 0, 1));
	hero = new Hero(this, &renderer->getModels()[0], physicalComponent);
	addObject(hero);

	currentLevel->load();
	currentLevel->init();

	physicalEngine->setGrid(currentLevel);
}*/


void GameEngine::display(unsigned int u32Width, unsigned int u32Height)
{
	currentGameState->display(u32Width, u32Height);
}

void GameEngine::mouseWheel(float fIncrement)
{
	currentGameState->mouseWheel(fIncrement);
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

bool GameEngine::isGameFinished()
{
	return finished;
}

void GameEngine::setFinished(bool finished)
{
	this->finished = finished;
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

unsigned int GameEngine::getCurrentLevelIndex()
{
	return currentLevelId;
}

unsigned int GameEngine::getEnemyCount()
{
	return enemyCount;
}

void GameEngine::setNextLevel()
{
	currentLevelId++;
	if (currentLevelId >= levelCount){
		finished = true;
		currentLevelId = 0;
	}
	currentLevel = levels[currentLevelId];
}

MyEngine *GameEngine::getParentEngine()
{
	return engine;
}

InGameState *GameEngine::getInGameState()
{
	return inGameState;
}

float GameEngine::getDeltaTime()
{
	return fDT;
}

void GameEngine::setHero(Hero *hero)
{
	if (this->hero != NULL && hero != NULL && hero->getGameEngineIndex() != this->hero->getGameEngineIndex())
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

void GameEngine::setCurrentLevelIndex(unsigned int levelId)
{
	currentLevelId = levelId;
}

void GameEngine::addObject(GameObject * object)
{
	unsigned int index = indexer->getNextIndex();

	if (object != NULL && index != UINT_MAX)
	{
		object->setGameEngineIndex(index);
		object->setGameEngine(this);
		gameObjects[index] = object;
		gameObjectCount++;
		engine->getPhysicalEngine()->addPhysicalComponent(object->getPhysicalComponent());
		object->selfAdd();
		switch (object->getObjectType())
		{
		case bacteriaType:;
		case virusType:;
		case cancerTypeDeclared:;
		case cancerTypeUndeclared:enemyCount++;
			break;
		default:break;
		}
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
		switch (gameObjects[index]->getObjectType())
		{
		case bacteriaType:;
		case virusType:;
		case cancerTypeDeclared:;
		case cancerTypeUndeclared:enemyCount--;
			break;
		default:break;
		}
		//gameObjects[index]->getPhysicalComponent()->destroy();
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

void GameEngine::clear(){
	for (unsigned int i = 0; i < MAX_GAME_OBJECT_COUNT; i++)
	{
		if (gameObjects[i] != NULL)
		{
			remove(i);
			gameObjects[i] = NULL;
		}
	}
	for (unsigned int i = 0; i < MAX_PARTICLE_SYSTEM_COUNT; i++)
	{
		if (particleSystems[i] != NULL)
		{
			removeParticleSystem(i);
			particleSystems[i] = NULL;
		}
	}
	gameObjectCount = enemyCount = particleSystemCount = 0;
}

void GameEngine::nextState(int id)
{
	currentGameState = gameStates[id];
	setup();
}

DebriefingState* GameEngine::getDebriefingState()
{
	return debriefingState;
}

void GameEngine::gameOver()
{
	currentGameState = gameStates[5];
	currentLevel = levels[0];
	setup();
}

void GameEngine::setRemainingLife(unsigned int life)
{
	inGameState->setRemainingLife(life);
}