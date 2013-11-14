#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "stdafx.h"
#include "GameObject.h"
#include "RenderableComponent.h"
#include "Material.h"
#include "Light.h"
#include "Shader.h"
#include "Program.h"

#include <list>
#include <fstream>


#include "OBJLoader.h"
#include "Level.h"

class MyEngine;

const int MAX_LIGHTS = 100;

class Renderer
{
private :
	RenderableComponent *models;
	Material *materials;
	unsigned int material_count, model_count;
	unsigned int vertice_array_object, coord_buffer_object, texcoord_buffer_object, normals_buffer_object, indice_buffer_object, index_count;
	unsigned int *textures;
	std::list<Program*> programs;
	Program* compute_illumination;
	std::list<Shader*> shaders;
	std::ofstream logs;
	Light *lights[MAX_LIGHTS];
	unsigned int lights_count;
	std::list<unsigned int> next_light_indices;
	MyEngine *engine;
public:
	Renderer(MyEngine *engine = NULL);
	~Renderer();

	void init();
	void load(SCENE **objects, unsigned int count);
	void render(GameObject **gameobject, unsigned int count, unsigned int u32Width, unsigned u32Height, Level *level=NULL);
	int addLight(Light *light);
	void removeLight(unsigned int id);
	RenderableComponent *getModels();

};

#endif