#pragma once
#include "Level.h"
#include "InGameState.h"
#include "GameObject.h"
#include "Hero.h"
#include "Cursor.h"
#include "Indexer.h"
#include "Cell.h"
#include "Projectile.h"
#include <list>

class MyEngine;


class GameEngine
{
private:
	MyEngine *engine;
	Level **levels;
	Level *currentLevel;
	GameState **gameStates;
	GameState *currentGameState;
	GameObject **gameObjects;
	Cursor *cursor;
	Hero *hero;
	Indexer *indexer;
	std::list<GameObject*> toRemove;

	unsigned int levelCount, gameObjectCount, gameStateCount;
public:
	static const unsigned int MAX_GAME_OBJECT_COUNT = 1000;
	static unsigned int MAX_CELL_COUNT,CURRENT_CELL_COUNT;
	GameEngine(MyEngine *engine = NULL);
	~GameEngine();

	void load(const char** fileNames, unsigned int count);
	void setup();
	void update(float fDT);
	void display(unsigned int u32Width, unsigned int u32Height);

	void mouseMove(POINT Pos);
	void keyDown(int s32VirtualKey);
	void keyUp(int s32VirtualKey);
	void lButtonDown(POINT Pt);
	

	GameObject **getGameObjects();
	unsigned int getGameObjectCount();
	Level *getCurrentLevel();
	Hero *getHero();
	Cursor *getCursor();
	MyEngine *getParentEngine();

	void setHero(Hero *hero);

	void addObject(GameObject *object);
	void setToRemove(GameObject *gameObject);
	void setToRemove(unsigned int gameObjectIndex);
	void remove(unsigned int index);
	void remove();
};

