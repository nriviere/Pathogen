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
#include "Indexer.h"

class MyEngine;


class Renderer
{

public:
	static const unsigned int MAX_LIGHT_COUNT = 100;
	static const unsigned int HERO_MODEL_INDEX = 0;
	static const unsigned int CELL_MODEL_INDEX = 1;
	static const unsigned int PROJECTILE_MODEL_INDEX = 2;
	/*-------------------------------------------------------*/
	static const unsigned int LYMPHOCYTE_MODEL_INDEX = 7;
	static const unsigned int BACTERIA_MODEL_INDEX = 3;
	static const unsigned int VIRUS_MODEL_INDEX = 4;
	static const unsigned int CANCER_MODEL_INDEX = 5;
	static const unsigned int MONOCYTE_MODEL_INDEX = 6;
	static const unsigned int NEUTROPHILE_MODEL_INDEX = 2;
	
	static const unsigned int DEPTH_PEELING_PASS_COUNT = 3;
	static unsigned int EXPLOSION_PARTICLE_TEXTURE_ID;
	static unsigned int TAGGED_VIRUS_TEXTURE_ID;
	static unsigned int TAGGED_CANCER_TEXTURE_ID;
	Renderer(MyEngine *engine = NULL);
	~Renderer();

	void init();
	void load();
	void render(GameObject **gameobject, unsigned int count, unsigned int u32Width, unsigned u32Height, Level *level=NULL);
	void render(Program *program);
	void renderLevel(Level *level);
	void setWidht(unsigned int width);
	void setHeight(unsigned int height);

	list<Light *> getLights();
	int addLight(Light *light);
	void removeLight(Light *light);
	
	RenderableComponent *getModels();
	Program* getCompute_illumination();

	unsigned int getCurrentLightCount();
	unsigned int getVertice_array_object();
	unsigned int getCoord_buffer_object();
	unsigned int getTexcoord_buffer_object();
	unsigned int getNormals_buffer_object();
	unsigned int getIndice_buffer_object();
	unsigned int getIndex_count();
	unsigned int loadTexture(const char *filename, GLenum type, GLenum envMode, GLenum magFilter, GLenum minFilter);
	void renderParticles();
	void render_string(float x, float y, float z, void* font, const char* s);
	void setColorRtoG(float &c1, float &c2, float position);
	void drawQuad(float x, float y, float width, float height);
	void drawTexQuad(float x, float y, float width, float height);
	void updateTime(float fDT);
	void drawHud(unsigned int width, unsigned int height);

	void updateLightUniforms(Matrx44 modelView);

	void clear();

private:
	
	MyEngine *engine;
	RenderableComponent *models;
	Material *materials;
	list<Light*> lights;
	list<Light*> toRemove;
	float	lightUniformAmbient[MAX_LIGHT_COUNT][4],
			lightUniformDiffuse[MAX_LIGHT_COUNT][4],
			lightUniformSpecular[MAX_LIGHT_COUNT][4],
			lightUniformPosition[MAX_LIGHT_COUNT][4],
			lightUniformMisc[MAX_LIGHT_COUNT][4];
	bool lightsChanged;
	Indexer lightIndexer;

	unsigned int 
		currentLightCount,
		width, 
		height,
		material_count,
		model_count,
		vertice_array_object,
		coord_buffer_object,
		texcoord_buffer_object, 
		normals_buffer_object,
		indice_buffer_object, 
		index_count,
		*textures,
		renderedTextures[DEPTH_PEELING_PASS_COUNT],
		depthTextures[DEPTH_PEELING_PASS_COUNT],
		framebufferIds[DEPTH_PEELING_PASS_COUNT];

	float timePassed;

	Program* compute_illumination, *depthShader;
	std::list<Program*> programs;
	std::list<Shader*> shaders;
	
	std::ofstream logs;

};

#endif