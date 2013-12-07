#pragma once
#include "stdafx.h"
#include <list>
#include "GameObject.h"
#include "SpawnLine.h"

class GameEngine;

class Level
{
private:
	float limitsX[2],limitsY[2];
	std::list<SpawnLine *> spawnLines;
	unsigned int spawnLinesCount;
	const char *filename;
	GameEngine *engine;

public:
	Level(const char *filename, GameEngine *engine);
	~Level();
	float *getLimitsX();
	float *getLimitsY();
	void load();
	void init();
	void update();
	void setGameEngine(GameEngine *engine);
	GameEngine * getGameEngine();
	GameObject **instantiateObjects(const char *className, unsigned int count);
	GameObject *instantiateObject(ObjectType objectType);
};

