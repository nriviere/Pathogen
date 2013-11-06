#include "Model3D.h"


Model3D::Model3D()
{
}


Model3D::~Model3D()
{
	for (int i = 0; i < index_count; i++)
	{
		delete indices[i];
	}
	delete[]indices;
	delete[]materials;
}

void Model3D::setIndices(vbo_index **indices, unsigned int index_count)
{
	this->index_count = index_count;
	this->indices = indices;
}
void Model3D::setMaterials(MyMaterial **materials, unsigned int material_count)
{
	this->materials = materials;
	this->material_count = material_count;
}

vbo_index **Model3D::getIndices()
{
	return indices;
}
MyMaterial **Model3D::getMaterials()
{
	return materials;
}

unsigned int Model3D::getIndexCount()
{
	return index_count;
}

unsigned int Model3D::getMaterialCount()
{
	return material_count;
}