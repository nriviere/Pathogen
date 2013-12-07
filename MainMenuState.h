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
	void mouseMove(POINT pos){};
	void lButtonDown(POINT pos){};
	void lButtonUp(POINT pos);
	void setup();
	void display(unsigned int u32Width, unsigned int u32Height);
	void update(float fDT);

private:
	float b1xMin, b1xMax, b1yMin, b1yMax;
	float b2xMin, b2xMax, b2yMin, b2yMax;
	float r, g, b;
	int width, height;


	void render_string(float x, float y, float z, void* font, const char* s);
	void drawHub();
	void setColorRtoG(float &c1, float &c2, float position);
	void drawQuads(float x, float y, float width, float height);


	IMAGE_DATA *data[2];
};

