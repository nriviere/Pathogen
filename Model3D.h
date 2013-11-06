#pragma once
#ifndef Model3D_H
#define Model3D_H
#include "MyMaterial.h"

struct vbo_index{
	unsigned int vertex_start;
	unsigned int vertex_length;
	unsigned int normal_start;
	unsigned int normal_length;
	unsigned int index_start;
	unsigned int index_length;
};

class Model3D
{
private :
	vbo_index **indices;
	MyMaterial **materials;
	unsigned int index_count;
	unsigned int material_count;

public:
	Model3D();
	void setIndices(vbo_index **indices, unsigned int index_count);
	void setMaterials(MyMaterial **materials, unsigned int material_count);
	vbo_index **getIndices();
	MyMaterial **getMaterials();
	unsigned int getIndexCount();
	unsigned int getMaterialCount();
	~Model3D();
};

#endif

