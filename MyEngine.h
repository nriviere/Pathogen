#pragma once
#ifndef MY3DENGINE_H
#define MY3DENGINE_H
#include "3DEngine.h"
#include "Renderer.h"
#include "PhysicalEngine.h"
#include "GameObject.h"
#include "GameState.h"
#include "list"
#include "Hero.h"
#include "Cursor.h"

class MyEngine :
	public C3DEngine
{
public:

	static const unsigned int MAX_LIGHT_COUNT = 100;
	MyEngine(void);
	~MyEngine(void);
	void Setup(HWND hWnd);
	void load(const char** fileNames, unsigned int count);
	void Update(float fDT);
	void Render(unsigned int u32Width, unsigned int u32Height);
	

	void MouseWheel(float fIncrement);
	void MouseMove(POINT Pos);
	void KeyDown(int s32VirtualKey);
	void KeyUp(int s32VirtualKey);

	Renderer *getRenderer();
	GameObject **getGameObjects();
	unsigned int getGameObjectCount();
	unsigned int getMaxConcurrence();
	PhysicalEngine *getPhysicalEngine();
	Level *getCurrentLevel();
	Hero *getHero();
	Cursor *getCursor();
	std::ofstream *getErrLog();

	void setMaxConcurrence(unsigned int maxConcurrence);

private:
	GameState *currentState;
	GameState **gameStates;

	Renderer *renderer;
	PhysicalEngine *physicalEngine;

	unsigned int maxConcurrence;


	//a mettre dans le game engine ?

	Cursor *cursor;
	Level **levels;
	Level *currentLevel;
	unsigned int levelCount;
	Hero *hero;
	GameObject **gameobjects;
	unsigned int gameobject_count;

	std::ofstream errlog;

};

#endif