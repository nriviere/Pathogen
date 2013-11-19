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

const unsigned int MAX_LIGHT_COUNT = 100;


MyEngine::MyEngine(void)
{
	srand(time(NULL));
	renderer = new Renderer(this);
	physicalEngine = new PhysicalEngine(this);
	gameobject_count = 0;
	gameStates = new GameState*[1];
	gameStates[0] = new InGameState(this);
	currentState = gameStates[0];
	levelCount = 1;
	levels = new Level*[levelCount];
	levels[0] = currentLevel = new Level();
	cursor = new Cursor();
}


MyEngine::~MyEngine(void)
{
	delete renderer;
	delete physicalEngine;
	delete gameStates[0];
	delete[] gameStates;
	for (int i = 0; i < levelCount; i++)
	{
		delete levels[i];
	}
	delete[] levels;
	errlog.close();
}

void MyEngine::load(const char** fileNames, unsigned int count)
{
	SCENE **objects = new SCENE*[count];

	for (int i = 0; i < count; i++)
	{
		objects[i] = ReadOBJFile(fileNames[i], true);
	}

	gameobject_count = 50;

	PhysicalComponent **physicalComponents = new PhysicalComponent*[gameobject_count];

	renderer->load(objects, count);
	
	gameobjects = new GameObject*[gameobject_count];
	physicalComponents[0] = new HeroPhysicalComponent(cursor);
	physicalComponents[0]->setPosition(Vect4(0, 0, 0, 1));
	gameobjects[0] = hero = new Hero(&renderer->getModels()[0], physicalComponents[0]);

	GameObject *cell;

	for (int i = 1; i < gameobject_count; i++)
	{
		physicalComponents[i] = new SelfMovingPhysicalComponent();
		physicalComponents[i]->setPosition(Vect4(100,0,0,1));
		gameobjects[i] = cell = new GameObject(&renderer->getModels()[1], &(*physicalComponents[i]));
	}

	physicalEngine->setComponents(physicalComponents, gameobject_count);
}

void MyEngine::Setup(HWND hWnd)
{
	currentState->setup();
	

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
	currentState->update(fDT);
}

void MyEngine::MouseWheel(float fIncrement)
{

}

void MyEngine::MouseMove(POINT Pos)
{
	currentState->mouseMove(Pos);
}


void MyEngine::KeyDown(int s32VirtualKey)
{
	if (s32VirtualKey == VK_ESCAPE)
	{
		exit(0);
	}
	currentState->keyDown(s32VirtualKey);
}

void MyEngine::KeyUp(int s32VirtualKey)
{
	currentState->keyUp(s32VirtualKey);
}

void MyEngine::Render(unsigned int u32Width, unsigned int u32Height)
{
	currentState->render(u32Width, u32Height);
	//glDisable(GL_LIGHTING);
	
	//logs << "------------------------------------------------------------------" << std::endl;


	//p->start();
	/*glBindBuffer(GL_ARRAY_BUFFER, coord_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, normals_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indice_buffer_object);
	glDrawElements(GL_TRIANGLES, index_count*3, GL_UNSIGNED_INT, 0);*/
	/*
	for (int o = 0; o < scene->u32ObjectsCount; o++)
	{
		bool has_texture = false;
		if (scene->pObjects[o].u32Material != UINT_MAX)
		{
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, scene->pMaterials[scene->pObjects[o].u32Material].pfDiffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, scene->pMaterials[scene->pObjects[o].u32Material].pfAmbient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, scene->pMaterials[scene->pObjects[o].u32Material].pfSpecular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, scene->pMaterials[scene->pObjects[o].u32Material].pfEmission);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, scene->pMaterials[scene->pObjects[o].u32Material].fShininess);
			IMAGE_DATA *image = NULL;
			image = scene->pMaterials[scene->pObjects[o].u32Material].pDiffuse;
			if (image != NULL)
			{
				glBindTexture(GL_TEXTURE_2D, *(GLuint*)(image->pUserData));
				//logs << *(GLuint*)image->pUserData << std::endl;
				has_texture = true;
			}
		}

		p->start();

		

		for (int f = scene->pObjects[o].u32FirstFace; f < scene->pObjects[o].u32FirstFace + scene->pObjects[o].u32FacesCount; f++)
		{
			glBegin(GL_TRIANGLES);
			glNormal3f(scene->pNormals[scene->pFaces[f].pu32Normals[0]].fX,
				scene->pNormals[scene->pFaces[f].pu32Normals[0]].fY,
				scene->pNormals[scene->pFaces[f].pu32Normals[0]].fZ);
			if (has_texture){
				glTexCoord2f(scene->pUV[scene->pFaces[f].pu32UV[0]].fU, scene->pUV[scene->pFaces[f].pu32UV[0]].fV);
			}
			glVertex3f(scene->pVertices[scene->pFaces[f].pu32Vertices[0]].fX,
				scene->pVertices[scene->pFaces[f].pu32Vertices[0]].fY,
				scene->pVertices[scene->pFaces[f].pu32Vertices[0]].fZ);

			glNormal3f(scene->pNormals[scene->pFaces[f].pu32Normals[1]].fX,
				scene->pNormals[scene->pFaces[f].pu32Normals[1]].fY,
				scene->pNormals[scene->pFaces[f].pu32Normals[1]].fZ);
			if (has_texture){
				glTexCoord2f(scene->pUV[scene->pFaces[f].pu32UV[1]].fU, scene->pUV[scene->pFaces[f].pu32UV[1]].fV);
			}
			glVertex3f(scene->pVertices[scene->pFaces[f].pu32Vertices[1]].fX,
				scene->pVertices[scene->pFaces[f].pu32Vertices[1]].fY,
				scene->pVertices[scene->pFaces[f].pu32Vertices[1]].fZ);

			glNormal3f(scene->pNormals[scene->pFaces[f].pu32Normals[2]].fX,
				scene->pNormals[scene->pFaces[f].pu32Normals[2]].fY,
				scene->pNormals[scene->pFaces[f].pu32Normals[2]].fZ);
			if (has_texture){
				glTexCoord2f(scene->pUV[scene->pFaces[f].pu32UV[2]].fU, scene->pUV[scene->pFaces[f].pu32UV[2]].fV);
			}
			glVertex3f(scene->pVertices[scene->pFaces[f].pu32Vertices[2]].fX,

				scene->pVertices[scene->pFaces[f].pu32Vertices[2]].fY,
				scene->pVertices[scene->pFaces[f].pu32Vertices[2]].fZ);
			glEnd();
		}
	}
	*/
	//p->stop();

}

GameObject **MyEngine::getGameObjects()
{
	return gameobjects;
}

Renderer *MyEngine::getRenderer()
{
	return renderer;
}	

PhysicalEngine *MyEngine::getPhysicalEngine()
{
	return physicalEngine;
}

unsigned int MyEngine::getGameObjectCount()
{
	return gameobject_count;
}

std::ofstream *MyEngine::getErrLog()
{
	return &errlog;
}

Hero *MyEngine::getHero()
{
	return hero;
}

Cursor *MyEngine::getCursor()
{
	return cursor;
}

Level *MyEngine::getCurrentLevel()
{
	return currentLevel;
}