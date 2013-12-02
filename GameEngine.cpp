#include "GameEngine.h"
#include "MyEngine.h"
#include "HeroPhysicalComponent.h"
#include "SelfMovingPhysicalComponent.h"
#include "Cell.h"
#include "CellPhysicalComponent.h"

unsigned int GameEngine::MAX_CELL_COUNT = 200;
unsigned int GameEngine::CURRENT_CELL_COUNT = 0;

GameEngine::GameEngine(MyEngine *engine) : engine(engine)
{
	gameObjectCount = 0;
	gameStates = new GameState*[2];
	gameStates[0] = new MainMenuState(this);
	gameStates[1] = new InGameState(this);
	currentGameState = gameStates[0];
	levelCount = 1;
	levels = new Level*[levelCount];
	levels[0] = currentLevel = new Level();
	cursor = new Cursor();
	indexer = new Indexer(MAX_GAME_OBJECT_COUNT);
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
	delete[] levels;
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

	unsigned int objectCount = 100;

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
	for (int i = 1; i < objectCount; i++)
	{
		float x = currentLevel->getLimitsX()[0] + (1.*rand() / RAND_MAX) * (currentLevel->getLimitsX()[1] - currentLevel->getLimitsX()[0]);
		float y = currentLevel->getLimitsY()[0] + (1.*rand() / RAND_MAX) * (currentLevel->getLimitsY()[1] - currentLevel->getLimitsY()[0]);
		physicalComponent = new CellPhysicalComponent();
		physicalComponent->setPosition(Vect4(x, y, 0, 1));
		RenderableComponent *component = &renderer->getModels()[1];
		Cell *cell = new Cell(this, &renderer->getModels()[1], physicalComponent);
		addObject(cell);
	}

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

unsigned int GameEngine::getGameObjectCount()
{
	return gameObjectCount;
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
		gameObjects[index] = object;
		gameObjectCount++;
		engine->getPhysicalEngine()->addPhysicalComponent(object->getPhysicalComponent());
		object->selfAdd();
	}
	else
	{
		exit(-30);
	}

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

void GameEngine::setToRemove(GameObject *gameObject)
{
	toRemove.push_back(gameObject);
}

void GameEngine::setToRemove(unsigned int gameObjectIndex)
{
	setToRemove(gameObjects[gameObjectIndex]);
}

void GameEngine::remove()
{
	while (!toRemove.empty())
	{
		remove(toRemove.front()->getGameEngineIndex());
		toRemove.pop_front();
	}
}

void GameEngine::nextState(int id)
{
	currentGameState = gameStates[id];
	setup();
}