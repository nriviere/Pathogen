#pragma once
#ifndef MY3DENGINE_H
#define MY3DENGINE_H
#include <list>
#include "3DEngine.h"
#include "Renderer.h"
#include "PhysicalEngine.h"
#include "GameObject.h"
#include "GameState.h"
#include "GameEngine.h"

class MyEngine :
	public C3DEngine
{
public:

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
	void LButtonDown(POINT Pt);
	void LButtonUp(POINT Pt);

	Renderer *getRenderer();
	PhysicalEngine *getPhysicalEngine();
	GameEngine *getGameEngine();
	unsigned int getMaxConcurrence();
	
	std::ofstream *getErrLog();

	void setMaxConcurrence(unsigned int maxConcurrence);

	void setWidth(int width);
	void setHeight(int height);
	int getWidth();
	int getHeight();
	static std::ofstream errlog;
private:

	Renderer *renderer;
	PhysicalEngine *physicalEngine;
	GameEngine *gameEngine;

	unsigned int maxConcurrence;

	
	
	int width, height;

};

#endif