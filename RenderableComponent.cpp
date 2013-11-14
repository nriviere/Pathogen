#include "RenderableComponent.h"


RenderableComponent::RenderableComponent()
{
}


RenderableComponent::~RenderableComponent()
{
	for (int i = 0; i < index_count; i++)
	{
		delete indices[i];
	}
	delete[]indices;
	delete[]materials;
}

void RenderableComponent::setIndices(vbo_index **indices, unsigned int index_count)
{
	this->index_count = index_count;
	this->indices = indices;
}
void RenderableComponent::setMaterials(Material **materials, unsigned int material_count)
{
	this->materials = materials;
	this->material_count = material_count;
}

vbo_index **RenderableComponent::getIndices()
{
	return indices;
}
Material **RenderableComponent::getMaterials()
{
	return materials;
}

unsigned int RenderableComponent::getIndexCount()
{
	return index_count;
}

unsigned int RenderableComponent::getMaterialCount()
{
	return material_count;
}

void RenderableComponent::setTextures(unsigned int *textures ,unsigned int texture_count)
{
	this->textures = textures;
	this->texture_count = texture_count;
}

unsigned int *RenderableComponent::getTextures()
{
	return textures;
}