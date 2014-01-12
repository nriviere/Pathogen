#pragma once

#include "stdafx.h"
#include "gamestate.h"

#include "TGALoader.h"
#include "gl/gl.h"
#include "gl\glut.h"


class MyEngine;

class BriefingState :
	public GameState
{
public:
	BriefingState(GameEngine *engine = NULL);
	~BriefingState();

	void keyUp(int s32VirtualKey){};
	void keyDown(int s32VirtualKey){};
	void mouseWheel(float fIncrement){};
	void mouseMove(POINT pos){};
	void lButtonDown(POINT pos){};
	void lButtonUp(POINT pos);
	void setup();
	void display(unsigned int u32Width, unsigned int u32Height);
	void update(float fDT);
	void setBriefingScreens(char **fileNames, unsigned int count);

private:
	float b1xMin, b1xMax, b1yMin, b1yMax;
	float b2xMin, b2xMax, b2yMin, b2yMax;
	float b3xMin, b3xMax, b3yMin, b3yMax;

	float r, g, b;
	int width, height;
	unsigned int briefingScreensCount;
	unsigned int *briefingScreens;
	IMAGE_DATA *data[4];
};

