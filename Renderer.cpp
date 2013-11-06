#include "Renderer.h"
#include <iostream>
#include "VBO.h"
#include "ShadersInc.h"
#include "ShaderException.h"
#include "exception"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\GLExt.h>


using namespace std;

Renderer::Renderer()
{
	models = NULL;
	materials = NULL;
	material_count = model_count = lights_count = 0;
	next_light_indices.push_back(0);
	vertice_array_object = normals_buffer_object = coord_buffer_object = indice_buffer_object = index_count = 0;
	logs.open("log.txt", ios::trunc);
}

void Renderer::load(SCENE **objects, unsigned int count)
{
	try{
		init_vbo();
	}
	catch (exception *e)
	{
		//logs << e->what();
		exit(-1);
	}

	unsigned int vertex_count = 0, face_count = 0, normal_count = 0, material_count = 0, submodel_count = 0;
	for (int i = 0; i < count; i++)
	{
		vertex_count += objects[i]->u32VerticesCount;
		face_count += objects[i]->u32FacesCount;
		normal_count += objects[i]->u32NormalsCount;
		material_count += objects[i]->u32MaterialsCount;
		submodel_count += objects[i]->u32ObjectsCount;
	}

	materials = new MyMaterial[material_count];
	models = new Model3D[count];

	//INITIALISATION VBOs

	glGenVertexArrays(1, &vertice_array_object);
	glBindVertexArray(vertice_array_object);

	glGenBuffers(1, &coord_buffer_object);
	glGenBuffers(1, &normals_buffer_object);
	glGenBuffers(1, &indice_buffer_object);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, coord_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * 3 * sizeof(float), NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, normals_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, normal_count * 3 * sizeof(float), NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indice_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_count * sizeof(GL_UNSIGNED_INT)* 3, NULL, GL_STATIC_DRAW);

	//REMPLISSAGE VBOs

	unsigned int model_pos = 0, material_pos = 0, vertex_pos = 0, normals_pos = 0, index_pos = 0, material_offset = 0;
	for (int s = 0; s < count; s++)
	{
		//CREATION DES MATERIAUX
		for (int i = 0; i < objects[s]->u32MaterialsCount; i++)
		{
			materials[material_pos++] = MyMaterial(
				Vect4(objects[s]->pMaterials->pfAmbient),
				Vect4(objects[s]->pMaterials->pfDiffuse),
				Vect4(objects[s]->pMaterials->pfSpecular),
				objects[s]->pMaterials->fShininess);
		}

		//RECUPERATION DES COORDONNEES DES VERTICES
		glBindBuffer(GL_ARRAY_BUFFER, coord_buffer_object);
		glBufferSubData(GL_ARRAY_BUFFER, vertex_pos * 3 * sizeof(GL_FLOAT), objects[s]->u32VerticesCount * 3 * sizeof(GL_FLOAT), &objects[s]->pVertices[vertex_pos]);
		vertex_pos += objects[s]->u32VerticesCount;

		//RECUPERATION DES COORDONNES DE NORMALES
		glBindBuffer(GL_ARRAY_BUFFER, normals_buffer_object);
		glBufferSubData(GL_ARRAY_BUFFER, normals_pos * 3 * sizeof(GL_FLOAT), objects[s]->u32NormalsCount * 3 * sizeof(GL_FLOAT), &objects[s]->pNormals[normals_pos]);
		normals_pos += objects[s]->u32NormalsCount;

		vbo_index **model_indices = new vbo_index*[objects[s]->u32ObjectsCount];
		MyMaterial **model_materials = new MyMaterial*[objects[s]->u32ObjectsCount];

		unsigned int material_counter = 0, index_counter = 0;
		for (int o = 0; o < objects[s]->u32ObjectsCount + 1; o++)
		{
			//RECUPERATION DES INDICES
			model_indices[index_counter] = NULL;
			if (objects[s]->pObjects[o].u32FirstFace <= objects[s]->u32FacesCount && objects[s]->pObjects[o].u32FacesCount > 0 && objects[s]->pObjects[o].u32FacesCount < objects[s]->u32FacesCount)
			{
				unsigned int *indices = new unsigned int[objects[s]->pObjects[o].u32FacesCount * 3];
				model_indices[index_counter] = new vbo_index();
				model_indices[index_counter]->index_start = index_pos;
				model_indices[index_counter]->index_length = objects[s]->pObjects[o].u32FacesCount;

				for (int r = 0; r < objects[s]->pObjects[o].u32FacesCount; r++)
				{
					for (int l = 0; l < 3; l++)
					{
						indices[r * 3 + l] = objects[s]->pFaces[objects[s]->pObjects[o].u32FirstFace + r].pu32Vertices[l];
					}
				}

				unsigned int start = index_pos * 3 * sizeof(GL_UNSIGNED_INT), length = objects[s]->pObjects[o].u32FacesCount * 3 * sizeof(GL_UNSIGNED_INT);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indice_buffer_object);
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, start, length, indices);
				index_pos += objects[s]->pObjects[o].u32FacesCount;
				delete[] indices;

				if (objects[s]->pObjects[o].u32Material != UINT_MAX)
				{
					MyMaterial *mat = &materials[objects[s]->pObjects[o].u32Material + material_offset];
					model_materials[material_counter++] = mat;
				}
				else
				{
					model_materials[material_counter++] = NULL;
				}
			}
			else{
				model_materials[material_counter++] = NULL;
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			index_counter++;
		}
		models[model_pos].setIndices(model_indices, objects[s]->u32ObjectsCount);
		models[model_pos].setMaterials(model_materials, objects[s]->u32MaterialsCount);
		material_offset = material_pos;

	}
	index_count = index_pos;

	glBindBuffer(GL_ARRAY_BUFFER, coord_buffer_object);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, normals_buffer_object);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	try{
		initApi();

		GLShader *s1 = new  GLShader("shaders/s1.gls", GL_VERTEX_SHADER);
		shaders.push_back(s1);
		s1->init();
		s1->loadSource();
		s1->loadShader();

		GLShader *f1 = new  GLShader("shaders/f1.gls", GL_FRAGMENT_SHADER);
		shaders.push_back(f1);
		f1->init();
		f1->loadSource();
		f1->loadShader();

		Program *p = new Program();
		p->setShader(s1, 0);
		p->setShader(f1, 1);
		glBindAttribLocation(p->getID(), 0, "in_position");
		glBindAttribLocation(p->getID(), 1, "in_normal");
		p->linkProgram();
		compute_illumination = p;
		programs.push_back(p);
	}
	catch (ShaderException *e)
	{
		string s = e->what();
		logs << s;
		exit(-1);
	}
}


Renderer::~Renderer()
{
	delete[] models;
	delete[] materials;
	logs.close();
}


void Renderer::render(GameObject **gameobject, unsigned int count)
{
	//Envoi des uniforms au shader
	GLuint lights_positions_uniloc = glGetUniformLocation(compute_illumination->getID(), "lights_positions");
	GLuint lights_ambient_uniloc = glGetUniformLocation(compute_illumination->getID(), "lights_ambient");
	GLuint lights_diffuse_uniloc = glGetUniformLocation(compute_illumination->getID(), "lights_diffuse");
	GLuint lights_specular_uniloc = glGetUniformLocation(compute_illumination->getID(), "lights_specular");

	GLuint lights_count_uniloc = glGetUniformLocation(compute_illumination->getID(), "lights_count");
	compute_illumination->start();
	float * lights_position = new float[4 * lights_count];
	float * lights_ambient = new float[4 * lights_count];
	float * lights_diffuse = new float[4 * lights_count];
	float * lights_specular = new float[4 * lights_count];

	int p = 0;
	for (int i = 0; i < lights_count; i++)
	{
		if (lights[i] != NULL)
		{
			memcpy(&lights_position[4 * p], (void*)(&lights[i]->getPosition()), 4);
			memcpy(&lights_ambient[4 * p], (void*)(&lights[i]->getAmbient()), 4);
			memcpy(&lights_diffuse[4 * p], (void*)(&lights[i]->getDiffuse()), 4);
			memcpy(&lights_specular[4 * p], (void*)(&lights[i]->getSpecular()), 4);
			p++;
		}
	}

	glUniform4fv(lights_positions_uniloc,lights_count * 4, lights_position);
	glUniform4fv(lights_ambient_uniloc, lights_count * 4, lights_ambient);
	glUniform4fv(lights_diffuse_uniloc, lights_count * 4, lights_diffuse);
	glUniform4fv(lights_specular_uniloc, lights_count * 4, lights_specular);
	glUniform1ui(lights_count_uniloc,lights_count);

	//Draw
	glBindBuffer(GL_ARRAY_BUFFER, coord_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, normals_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indice_buffer_object);
	for (int o = 0; o < count; o++)
	{
		Model3D *model = gameobject[0]->getModel();
		for (int i = 0; i < model->getIndexCount(); i++)
		{
			MyMaterial *material = model->getMaterials()[i];
			if (material != NULL){

				float ambient[4] = { material->getAmbient()[0], material->getAmbient()[1], material->getAmbient()[2], material->getAmbient()[3] };
				float diffuse[4] = { material->getDiffuse()[0], material->getDiffuse()[1], material->getDiffuse()[2], material->getDiffuse()[3] };
				float specular[4] = { material->getSpecular()[0], material->getSpecular()[1], material->getSpecular()[2], material->getSpecular()[3] };
				float shininess = material->getShininess();
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess);
			}
			vbo_index *index = model->getIndices()[i];
			if (index != NULL)
			{
				glDrawElements(GL_TRIANGLES, index->index_length * 3, GL_UNSIGNED_INT, (GLvoid *)(index->index_start * 3 * sizeof(GL_UNSIGNED_INT)));
			}

		}
	}
	delete lights_position;
	delete lights_ambient;
	delete lights_diffuse;
	delete lights_specular;
}

int Renderer::addLight(MyLight *light)
{
	int id;
	if (lights_count <= MAX_LIGHTS)
	{
		id = lights_count;
		if (!next_light_indices.empty())
		{
			id = next_light_indices.front();
			next_light_indices.pop_front();
		}
		lights[id] = light;
		lights_count++;
	}
	else
	{
		id = -1;
	}
	return id;
}

void Renderer::removeLight(unsigned int id)
{
	if (lights[id] != NULL)
	{
		delete lights[id];
		lights[id] = NULL;
		next_light_indices.push_back(id);
		lights_count--;
	}
}

Model3D *Renderer::getModels()
{
	return models;
}