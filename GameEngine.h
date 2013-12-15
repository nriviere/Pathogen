#pragma once
#include "Level.h"
#include "MainMenuState.h"
#include "BriefingState.h"
#include "InGameState.h"
#include "GameObject.h"
#include "Hero.h"
#include "Cursor.h"
#include "Indexer.h"
#include "Cell.h"
#include "Projectile.h"
#include "ParticleSystem.h"
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
	ParticleSystem **particleSystems;
	Particle **particles;
	InGameState *inGameState;
	Cursor *cursor;
	Hero *hero;
	Indexer *indexer,*particleSystemIndexer,*particleIndexer;
	std::list<GameObject*> toRemove;
	std::list<ParticleSystem *> particleSystemsToRemove;
	std::list<ParticleSystem *> particleSystemsToAdd;
	std::list<Particle *> particlesToRemove;
	
	unsigned int levelCount, gameObjectCount, particleCount,particleSystemCount,gameStateCount;
public:
	static const unsigned int MAX_GAME_OBJECT_COUNT = 1000;
	static const unsigned int MAX_PARTICLE_SYSTEM_COUNT = 1000;
	static const unsigned int MAX_PARTICLE_COUNT = 1000;
	static unsigned int MAX_CELL_COUNT,CURRENT_CELL_COUNT;
	GameEngine(MyEngine *engine = NULL);
	~GameEngine();

	void load(const char** fileNames, unsigned int count);
	void setup();
	void update(float fDT);
	void display(unsigned int u32Width, unsigned int u32Height);

	void mouseWheel(float fIncrement);
	void mouseMove(POINT Pos);
	void keyDown(int s32VirtualKey);
	void keyUp(int s32VirtualKey);
	void lButtonDown(POINT Pt);
	void lButtonUp(POINT Pt);
	

	GameObject **getGameObjects();
	ParticleSystem **getParticleSystems();
	unsigned int getGameObjectCount();
	unsigned int getParticleSystemCount();
	Level *getCurrentLevel();
	Hero *getHero();
	Cursor *getCursor();
	MyEngine *getParentEngine();
	InGameState *getInGameState();
	void setHero(Hero *hero);

	void addObject(GameObject *object);
	void addParticleSystem(ParticleSystem *particleSystem);
	void addParticleSystems();
	void setToRemove(GameObject *gameObject);
	void setToRemove(unsigned int gameObjectIndex);
	void setParticleSystemToRemove(ParticleSystem *particleSystem);
	void remove(unsigned int index);
	void removeParticleSystem(unsigned int index);
	void remove();

	void nextState(int id);
};

