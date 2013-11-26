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
	Program* compute_illumination, *renderTexture;
	std::list<Shader*> shaders;
	std::ofstream logs;
	Light *lights[MAX_LIGHTS];
	unsigned int lights_count;
	std::list<unsigned int> next_light_indices;
	MyEngine *engine;

	unsigned int renderedTexture;
	unsigned int depthrenderbuffer;
	unsigned int frameBufferId;
	unsigned int quad_vertexbuffer;
	unsigned int quad_uvbuffer;
	unsigned int quad_VertexArrayID;
	unsigned int width, height;

public:
	static const unsigned int MAX_LIGHT_COUNT = 100;
	static const unsigned int HERO_MODEL_INDEX = 0;
	static const unsigned int CELL_MODEL_INDEX = 1;
	static const unsigned int PROJECTILE_MODEL_INDEX = 2;
	Renderer(MyEngine *engine = NULL);
	~Renderer();

	void init();
	void load(SCENE **objects, unsigned int count);
	void render(GameObject **gameobject, unsigned int count, unsigned int u32Width, unsigned u32Height, Level *level=NULL);
	int addLight(Light *light);
	void removeLight(unsigned int id);
	RenderableComponent *getModels();
	Program* getCompute_illumination();
	Light **getLights();
	unsigned int getLights_count();
	unsigned int getVertice_array_object();
	unsigned int getCoord_buffer_object();
	unsigned int getTexcoord_buffer_object();
	unsigned int getNormals_buffer_object();
	unsigned int getIndice_buffer_object();
	unsigned int getIndex_count();
};

#endif