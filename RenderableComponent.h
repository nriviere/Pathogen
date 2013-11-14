#pragma once
#ifndef RenderableComponent_H
#define RenderableComponent_H
#include "Material.h"

struct vbo_index{
	unsigned int vertex_start;
	unsigned int vertex_length;
	unsigned int normal_start;
	unsigned int normal_length;
	unsigned int index_start;
	unsigned int index_length;
};

class RenderableComponent
{
private :
	vbo_index **indices;
	Material **materials;
	unsigned int *textures;
	unsigned int index_count;
	unsigned int material_count;
	unsigned int texture_count;
	

public:
	RenderableComponent();
	void setIndices(vbo_index **indices, unsigned int index_count);
	void setMaterials(Material **materials, unsigned int material_count);
	void setTextures(unsigned int *textures,unsigned int texture_count);
	vbo_index **getIndices();
	Material **getMaterials();
	unsigned int *getTextures();
	unsigned int getIndexCount();
	unsigned int getMaterialCount();
	~RenderableComponent();
};

#endif

