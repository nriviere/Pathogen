#pragma once
#include "stdafx.h"
#include "gamestate.h"


class InGameState :
	public GameState
{
private :
	bool isZdown, isQdown, isSdown, isDdown;
	POINT prevMousePos;

public:
	InGameState(MyEngine *engine = NULL);
	~InGameState(void);
	void keyUp(int s32VirtualKey);
	void keyDown(int s32VirtualKey);
	void mouseMove(POINT pos);
	void setup();
	void update(float fDT);
	void render(unsigned int u32Width, unsigned int u32Height);
};

