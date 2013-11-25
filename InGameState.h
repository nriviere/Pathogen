#pragma once
#include "stdafx.h"
#include "gamestate.h"

class MyEngine;

class InGameState :
	public GameState
{
private :
	bool isZdown, isQdown, isSdown, isDdown;
	POINT prevMousePos;
	MyEngine *parentEngine;

public:
	InGameState(GameEngine *engine = NULL);
	~InGameState(void);
	void keyUp(int s32VirtualKey);
	void keyDown(int s32VirtualKey);
	void mouseMove(POINT pos);
	void lButtonDown(POINT pt);
	void setup();
	void update(float fDT);
	void display(unsigned int u32Width, unsigned int u32Height);
};

