#pragma once
#include <stdio.h>
#include "stdafx.h"

class MyEngine;
class GameEngine;

class GameState
{
protected:
	GameEngine *engine;
public:
	GameState(GameEngine *engine = NULL);
	~GameState(void);
	virtual void keyUp(int s32VirtualKey) = 0;
	virtual void keyDown(int s32VirtualKey) = 0;
	virtual void mouseMove(POINT pos) = 0;
	virtual void lButtonDown(POINT Pt) = 0;
	virtual void lButtonUp(POINT Pt) = 0;
	virtual void setup() = 0;
	virtual void update(float fDT) = 0;
	virtual void display(unsigned int u32Width, unsigned int u32Height) = 0;

};

