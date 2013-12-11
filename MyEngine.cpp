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
	errlog.open("log.txt", std::ios::trunc);
}


MyEngine::~MyEngine(void)
{
	delete renderer;
	delete physicalEngine;
	delete gameEngine;
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
	/*
	for (int o = 0; o < scene->u32ObjectsCount; o++)
	{
		if (scene->pObjects[o].u32Material != UINT_MAX){

			IMAGE_DATA *image = NULL;
			image = scene->pMaterials[scene->pObjects[o].u32Material].pDiffuse;
			if (image != NULL)
			{
				image->pUserData = new GLuint();
				glGenTextures(1, (GLuint *)image->pUserData);
				glBindTexture(GL_TEXTURE_2D, *(GLuint *)(image->pUserData));
				logs << "ID créés : " << std::endl;
				logs << *(GLuint *)image->pUserData << std::endl;
				unsigned int b = 24;
				GLenum format = GL_RGB;

				if (scene->pMaterials[scene->pObjects[o].u32Material].pDiffuse->PixelFormat != 0)
				{
					b = 32;
					format = GL_RGBA;
				}
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					format,
					image->u32Width,
					image->u32Height,
					0,
					format,
					GL_UNSIGNED_BYTE,
					image->pu8Pixels
					);
				glTexEnvi(GL_TEXTURE, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
		}
	}
	*/
	
	
	errlog << "***********************************************************************************************************************************" << std::endl;
	/*
	delete[]vertice_coord;
	delete[]faces;
	delete[]normals;*/

	//Shaders init 
	

}


void MyEngine::Update(float fDT)
{
	gameEngine->update(fDT);
	frames++;
}

void MyEngine::Render(unsigned int u32Width, unsigned int u32Height)
{
	gameEngine->display(u32Width, u32Height);
}

void MyEngine::MouseWheel(float fIncrement)
{

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