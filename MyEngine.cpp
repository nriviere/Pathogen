#include "stdafx.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include "MyEngine.h"
#include <iostream>
#include <fstream>
#include "OBJLoader.h"
#include "ShadersInc.h"
#include "Shader.h"
#include "Program.h"
#include "Renderer.h"
#include "InGameState.h"
#include "HeroPhysicalComponent.h"
#include "SelfMovingPhysicalComponent.h"
#include <time.h>

std::ofstream MyEngine::errlog;

int start = 0;
unsigned int frames = 0;

MyEngine::MyEngine(void)
{
	srand(time(NULL));
	gameEngine = new GameEngine(this);
	renderer = new Renderer(this);
	physicalEngine = new PhysicalEngine(this);
	soundEngine = new SoundEngine(this);
	errlog.open("log.txt", std::ios::trunc);
}


MyEngine::~MyEngine(void)
{
	delete renderer;
	delete physicalEngine;
	delete gameEngine;
	soundEngine->shutdown();
	delete soundEngine;
	errlog.close();
}




void MyEngine::Setup(HWND hWnd)
{
	start = clock();
	gameEngine->setup();
	
	RECT R;
	GetClientRect(hWnd, &R);

	renderer->setWidht(R.right);
	renderer->setHeight(R.bottom);
	soundEngine->init();
	renderer->init();

	
	errlog << "***********************************************************************************************************************************" << std::endl;
}


void MyEngine::Update(float fDT)
{
	gameEngine->update(fDT);
	soundEngine->update();
	frames++;
}

void MyEngine::Render(unsigned int u32Width, unsigned int u32Height)
{
	gameEngine->display(u32Width, u32Height);
}

void MyEngine::MouseWheel(float fIncrement)
{
	gameEngine->mouseWheel(fIncrement);
}

void MyEngine::MouseMove(POINT Pos)
{
	gameEngine->mouseMove(Pos);
}

void MyEngine::LButtonDown(POINT Pt)
{
	gameEngine->lButtonDown(Pt);
}

void MyEngine::LButtonUp(POINT Pt)
{
	gameEngine->lButtonUp(Pt);
}

void MyEngine::KeyDown(int s32VirtualKey)
{
	if (s32VirtualKey == VK_ESCAPE)
	{
		start = clock() - start;
		float fps = 1.*frames / (start * 0.001);
		errlog << fps << endl;
		exit(0);
	}
	gameEngine->keyDown(s32VirtualKey);
}

void MyEngine::KeyUp(int s32VirtualKey)
{
	gameEngine->keyUp(s32VirtualKey);
}


Renderer *MyEngine::getRenderer()
{
	return renderer;
}	

PhysicalEngine *MyEngine::getPhysicalEngine()
{
	return physicalEngine;
}

GameEngine *MyEngine::getGameEngine()
{
	return gameEngine;
}

SoundEngine *MyEngine::getSoundEngine()
{
	return soundEngine;
}

unsigned int MyEngine::getMaxConcurrence()
{
	return maxConcurrence;
}

std::ofstream *MyEngine::getErrLog()
{
	return &errlog;
}

void MyEngine::setMaxConcurrence(unsigned int maxConcurrence)
{
	this->maxConcurrence = maxConcurrence;
}

void MyEngine::setWidth(int width)
{
	this->width = width;
}

void MyEngine::setHeight(int height)
{
	this->height = height;
}

int MyEngine::getWidth()
{
	return this->width;
}

int MyEngine::getHeight()
{
	return this->height;
}