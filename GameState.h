#pragma once
#include <stdio.h>
#include "stdafx.h"

class MyEngine;

class GameState
{
protected:
	MyEngine *engine;
public:
	GameState(MyEngine *engine = NULL);
	~GameState(void);
	virtual void keyUp(int s32VirtualKey) = 0;
	virtual void keyDown(int s32VirtualKey) = 0;
	virtual void mouseMove(POINT pos) = 0;
	virtual void setup() = 0;
	virtual void update(float fDT) = 0;
	virtual void render(unsigned int u32Width, unsigned int u32Height) = 0;

};

