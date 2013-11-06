#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "stdafx.h"
#include "GameObject.h"
#include "Model3D.h"
#include "MyMaterial.h"
#include "MyLight.h"
#include "GLShader.h"
#include "Program.h"

#include <list>
#include <fstream>


#include "OBJLoader.h"


const int MAX_LIGHTS = 100;

class Renderer
{
private :
	Model3D *models;
	MyMaterial *materials;
	unsigned int material_count, model_count;
	unsigned int vertice_array_object, coord_buffer_object, normals_buffer_object, indice_buffer_object, index_count;
	std::list<Program*> programs;
	Program* compute_illumination;
	std::list<GLShader*> shaders;
	std::ofstream logs;
	MyLight *lights[MAX_LIGHTS];
	unsigned int lights_count;
	std::list<unsigned int> next_light_indices;
public:
	Renderer();
	~Renderer();
	void init();
	void load(SCENE **objects, unsigned int count);
	void render(GameObject **gameobject, unsigned int count);
	int addLight(MyLight *light);
	void removeLight(unsigned int id);
	Model3D *getModels();

};

#endif