#include "stdafx.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include "My3DEngine.h"
#include <iostream>
#include <fstream>
#include "OBJLoader.h"
#include "ShadersInc.h"
#include "GLShader.h"
#include "Program.h"
#include "Renderer.h"

//SCENE * scene = NULL;
float dezoom = 0;
float prevx = 0;
float prevy = 0;
float dx = 0;
float dy = 0;
float ax = 0;
float ay = 0;
std::ofstream logs;
const GLfloat lightPos[] = { 10, 1000, 100 };
GLfloat modelAmbient[] = { 0.4, 0.4, 0.4, 1 };
GLfloat mat1Diffuse[] = { 0.5, 0.5, 0.5, 0.5 };
GLfloat mat1Ambient[] = { 0.3, 0.3, 0.3, 0.5 };
GLfloat mat1Specular[] = { 0.8, 0.8, 0.8, 0.5};

unsigned int *material_indices;

const unsigned int MAX_LIGHT_COUNT = 100;

struct Material {
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess;
};



GLShader *s1;
Program *p;

My3DEngine::My3DEngine(void)
{
	renderer = new Renderer();
	gameobject_count = 0;
}


My3DEngine::~My3DEngine(void)
{
	delete renderer;
	logs.close();
}

void My3DEngine::load(const char** fileNames, unsigned int count)
{
	SCENE **objects = new SCENE*[count];

	for (int i = 0; i < count; i++)
	{
		objects[i] = ReadOBJFile(fileNames[i], true);
	}

	renderer->load(objects, count);
	gameobject_count = 1000;
	gameobjects = new GameObject*[gameobject_count];
	for (int i = 0; i < gameobject_count; i++)
	{
		gameobjects[i] = new GameObject(&renderer->getModels()[0]);
	}
}

void My3DEngine::Setup(HWND hWnd)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelAmbient);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1Diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat1Ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat1Specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.5);

	const char *test = "3DS/Island 001/Island_001.obj";
	load(&test,1);

	MyLight * light = new MyLight(Matrx44(	Vect4(0.2,0.2,0.2, 1),
											Vect4(0.5, 0.5, 0.5, 1), 
											Vect4(0.8, 0.8, 0.8, 1), 
											Vect4(10, 10, 10, 0)));

	int lightId = renderer->addLight(light);

	logs.open("log.txt", std::ios::trunc);

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
	
	
	logs << "***********************************************************************************************************************************" << std::endl;
	/*
	delete[]vertice_coord;
	delete[]faces;
	delete[]normals;*/

	//Shaders init 
	

}
void My3DEngine::Update(float fDT)
{

}

void My3DEngine::MouseWheel(float fIncrement)
{

	if (fIncrement < 0)dezoom -= 1;
	else dezoom += 1;

}

void My3DEngine::MouseMove(POINT Pos)
{
	dx = Pos.x - prevx;
	dy = Pos.y - prevy;
	ax += dx;
	ay += dy;
	prevx = Pos.x;
	prevy = Pos.y;
}

void My3DEngine::Render(unsigned int u32Width, unsigned int u32Height)
{
	glClearColor(0, 0, 0, 1);
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1.*u32Width / u32Height, 0.1, 10000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 1);
	glColor3f(1, 0, 0);

	glRotatef(ay, 1, 0, 0);
	glRotatef(ax, 0, 1, 0);
	glTranslatef(0, -20, 0);
	glTranslatef(0, 0, dezoom * 5);



	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	renderer->render(gameobjects, gameobject_count);
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

GameObject **My3DEngine::getGameObjects()
{
	return gameobjects;
}