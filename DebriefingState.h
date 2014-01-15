#pragma once

#include "stdafx.h"
#include "GameState.h"
#include "GameObject.h"
#include "gl/gl.h"
#include "gl/glut.h"

class DebriefingState :
	public GameState
{
public:
	DebriefingState(GameEngine *engine = NULL);
	~DebriefingState();

	void keyUp(int s32VirtualKey){};
	void keyDown(int s32VirtualKey){};
	void mouseWheel(float fIncrement){};
	void mouseMove(POINT pos){};
	void lButtonDown(POINT pos){};
	void lButtonUp(POINT pos);
	void setup();
	void display(unsigned int u32Width, unsigned int u32Height);
	void update(float fDT);

	void updateStatistics(ObjectType target, ObjectType ammo);

private:
	void render_string(float x, float y, void* font, const char* s);
	void clearStatistics();

	float b1xMin, b1xMax, b1yMin, b1yMax;
	float r, g, b;
	int width, height;
	unsigned int newLifeThreshold;

	float virusAccuracy, virusInaccuracy;
	float cancerAccuracy, cancerInaccuracy;
	float bacteriaAccuracy, bacteriaInaccuracy;
	float bacteriaWasteAccuracy, bacteriaWasteInaccuracy;
};

