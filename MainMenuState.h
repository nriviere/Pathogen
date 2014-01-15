#pragma once

#include "stdafx.h"
#include "gamestate.h"
#include "MyEngine.h"
#include "TGALoader.h"
#include "gl\glut.h"

#include <fstream>

using namespace std;

class MainMenuState :
	public GameState
{
public:
	MainMenuState(GameEngine *engine = NULL);
	~MainMenuState(void);

	void keyUp(int s32VirtualKey){};
	void keyDown(int s32VirtualKey){};
	void mouseWheel(float fIncrement){};
	void mouseMove(POINT pos){};
	void lButtonDown(POINT pos){};
	void lButtonUp(POINT pos);
	void setup();
	void display(unsigned int u32Width, unsigned int u32Height);
	void update(float fDT);

private:
	float b1xMin, b1xMax, b1yMin, b1yMax;
	float b2xMin, b2xMax, b2yMin, b2yMax;
	float b3xMin, b3xMax, b3yMin, b3yMax;
	float r, g, b;
	int width, height;

	IMAGE_DATA *data[4];
};

