#pragma once

#include "stdafx.h"
#include "GameState.h"
#include "MyEngine.h"
#include "TGALoader.h"
#include "gl\glut.h"

class GameOverState :
	public GameState
{
public:
	GameOverState(GameEngine *engine = NULL);
	~GameOverState();

	void keyUp(int s32VirtualKey){};
	void keyDown(int s32VirtualKey){};
	void mouseWheel(float fIncrement){};
	void mouseMove(POINT pos){};
	void lButtonDown(POINT pos){};
	void lButtonUp(POINT pos);
	void setup();
	void display(unsigned int u32Width, unsigned int u32Height);
	void update(float fDT){};
private:
	float b1xMin, b1xMax, b1yMin, b1yMax;
	IMAGE_DATA *data[4];
	int width, height;
};

