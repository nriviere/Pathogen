#include "Renderer.h"
#include <iostream>
#include "VBO.h"
#include "ShadersInc.h"
#include "ShaderException.h"
#include "MyEngine.h"
#include "exception"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\GLExt.h>
#include "InGameState.h"



SCENE *scene = NULL;

using namespace std;

Renderer::Renderer(MyEngine *engine)
{
	models = NULL;
	materials = NULL;
	material_count = model_count = lights_count = 0;
	next_light_indices.push_back(0);
	vertice_array_object = normals_buffer_object = coord_buffer_object = indice_buffer_object = index_count = 0;
	logs.open("log.txt", ios::trunc);
	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		lights[i] = NULL;
	}
	this->engine = engine;
}

void Renderer::init(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
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
	scene = objects[0];
	unsigned int vertex_count = 0, face_count = 0, normal_count = 0, material_count = 0, submodel_count = 0, texcoord_count = 0;
	for (int i = 0; i < count; i++)
	{
		vertex_count += objects[i]->u32VerticesCount;
		face_count += objects[i]->u32FacesCount;
		normal_count += objects[i]->u32NormalsCount;
		material_count += objects[i]->u32MaterialsCount;
		submodel_count += objects[i]->u32ObjectsCount;
		texcoord_count += objects[i]->u32UVCount;
	}

	materials = new Material[material_count];
	models = new RenderableComponent[count];

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

	glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, texcoord_count * 2 * sizeof(float), NULL, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indice_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_count * sizeof(GL_UNSIGNED_INT)* 3, NULL, GL_STATIC_DRAW);



	//REMPLISSAGE VBOs

	unsigned int model_pos = 0, material_pos = 0, vertex_pos = 0, normals_pos = 0, index_pos = 0, textcoord_pos = 0, material_offset = 0;
	for (int s = 0; s < count; s++)
	{
		//CREATION DES MATERIAUX
		for (int i = 0; i < objects[s]->u32MaterialsCount; i++)
		{
			materials[material_pos++] = Material(
				Vect4(objects[s]->pMaterials[i].pfAmbient),
				Vect4(objects[s]->pMaterials[i].pfDiffuse),
				Vect4(objects[s]->pMaterials[i].pfSpecular),
				objects[s]->pMaterials->fShininess);
		}

		//RECUPERATION DES COORDONNEES DES VERTICES
		glBindBuffer(GL_ARRAY_BUFFER, coord_buffer_object);
		glBufferSubData(GL_ARRAY_BUFFER, vertex_pos * 3 * sizeof(GL_FLOAT), objects[s]->u32VerticesCount * 3 * sizeof(GL_FLOAT), objects[s]->pVertices);


		//RECUPERATION DES COORDONNES DE NORMALES
		glBindBuffer(GL_ARRAY_BUFFER, normals_buffer_object);
		glBufferSubData(GL_ARRAY_BUFFER, normals_pos * 3 * sizeof(GL_FLOAT), objects[s]->u32NormalsCount * 3 * sizeof(GL_FLOAT), objects[s]->pNormals);


		//RECUPERATION DES COORDONNES DE TEXTURES
		glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer_object);
		glBufferSubData(GL_ARRAY_BUFFER, textcoord_pos * 2 * sizeof(GL_FLOAT), objects[s]->u32UVCount * 2 * sizeof(GL_FLOAT), objects[s]->pUV);


		vbo_index **model_indices = new vbo_index*[objects[s]->u32ObjectsCount];
		Material **model_materials = new Material*[objects[s]->u32ObjectsCount];
		unsigned int *textures = new unsigned int[objects[s]->u32ObjectsCount];


		unsigned int material_counter = 0, index_counter = 0, index_offset = 0;
		for (int o = 0; o < objects[s]->u32ObjectsCount; o++)
		{
			textures[o] = UINT_MAX;
			//RECUPERATION DES INDICES
			model_indices[index_counter] = NULL;

			if (objects[s]->pObjects[o].u32FirstFace <= objects[s]->u32FacesCount && objects[s]->pObjects[o].u32FacesCount > 0 && objects[s]->pObjects[o].u32FacesCount <= objects[s]->u32FacesCount)
			{
				unsigned int *indices = new unsigned int[objects[s]->pObjects[o].u32FacesCount * 3];
				model_indices[index_counter] = new vbo_index();
				model_indices[index_counter]->index_start = index_pos + index_offset;
				model_indices[index_counter]->index_length = objects[s]->pObjects[o].u32FacesCount;

				for (int r = 0; r < objects[s]->pObjects[o].u32FacesCount; r++)
				{
					for (int l = 0; l < 3; l++)
					{
						indices[r * 3 + l] = vertex_pos + objects[s]->pFaces[objects[s]->pObjects[o].u32FirstFace + r].pu32Vertices[l];
					}
				}

				unsigned int start = (index_pos + index_offset) * 3 * sizeof(GL_UNSIGNED_INT), length = objects[s]->pObjects[o].u32FacesCount * 3 * sizeof(GL_UNSIGNED_INT);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indice_buffer_object);
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, start, length, indices);

				delete[] indices;

				if (objects[s]->pObjects[o].u32Material != UINT_MAX)
				{
					Material *mat = &materials[objects[s]->pObjects[o].u32Material + material_offset];
					model_materials[material_counter++] = mat;
					//RECUPERATION DES TEXTURES
					if (objects[s]->pMaterials[objects[s]->pObjects[o].u32Material].pDiffuse != NULL)
					{
						IMAGE_DATA *image = NULL;
						image = scene->pMaterials[scene->pObjects[o].u32Material].pDiffuse;
						if (image != NULL)
						{
							unsigned int ID;
							glGenTextures(1, &ID);
							textures[o] = ID;
							glBindTexture(GL_TEXTURE_2D, ID);
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
				else
				{
					model_materials[material_counter++] = NULL;
				}
				index_offset += objects[s]->pObjects[o].u32FacesCount;
			}
			else{
				model_materials[material_counter++] = NULL;
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			index_counter++;
		}

		index_pos += objects[s]->u32FacesCount;
		vertex_pos += objects[s]->u32VerticesCount;
		normals_pos += objects[s]->u32NormalsCount;
		textcoord_pos += objects[s]->u32UVCount;


		models[model_pos].setTextures(textures, objects[s]->u32MaterialsCount);
		models[model_pos].setIndices(model_indices, objects[s]->u32ObjectsCount);
		models[model_pos].setMaterials(model_materials, objects[s]->u32MaterialsCount);
		model_pos++;
		material_offset += objects[s]->u32MaterialsCount;

	}
	index_count = index_pos;

	glBindBuffer(GL_ARRAY_BUFFER, coord_buffer_object);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, normals_buffer_object);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer_object);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	try{
		initApi();

		Shader *s1 = new  Shader("shaders/tp1v.gls", GL_VERTEX_SHADER);
		shaders.push_back(s1);
		s1->init();
		s1->loadSource();
		s1->loadShader();

		Shader *f1 = new  Shader("shaders/tp1f.gls", GL_FRAGMENT_SHADER);
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

float t = 0;

void Renderer::render(GameObject **gameobject, unsigned int count, unsigned int u32Width, unsigned u32Height, Level *level)
{
	t += 0.1;
	glClearColor(0, 0, 0, 1);
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1.*u32Width / u32Height, 0.1, 10000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.5, 0.5, 0.5, 1);
	glColor3f(1, 0, 0);

	//Placer la camera// faire un objet caméra
	glTranslatef(0, 0, -200);


	//Rendu du niveau temporaire
	glDisable(GL_LIGHTING);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_LINE_STRIP);
	glVertex3f(level->getLimitsX()[0], level->getLimitsY()[0], 0);
	glVertex3f(level->getLimitsX()[1], level->getLimitsY()[0], 0);
	glVertex3f(level->getLimitsX()[1], level->getLimitsY()[1], 0);
	glVertex3f(level->getLimitsX()[0], level->getLimitsY()[1], 0);
	glVertex3f(level->getLimitsX()[0], level->getLimitsY()[0], 0);
	glEnd();

	Vect4 cursorPosition = engine->getGameEngine()->getCursor()->getPhysicalComponent()->getPosition();
	Vect4 heroPosition = engine->getGameEngine()->getHero()->getPhysicalComponent()->getPosition();
	glBegin(GL_LINES);
	glVertex3f(cursorPosition[0], cursorPosition[1], 0);
	glVertex3f(heroPosition[0], heroPosition[1], 0);
	glEnd();

	glEnable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);
	compute_illumination->start();
	//Envoi des uniforms au shader
	GLuint lights_positions_uniloc = glGetUniformLocation(compute_illumination->getID(), "lights_position");
	GLuint lights_ambient_uniloc = glGetUniformLocation(compute_illumination->getID(), "lights_ambient");
	GLuint lights_diffuse_uniloc = glGetUniformLocation(compute_illumination->getID(), "lights_diffuse");
	GLuint lights_specular_uniloc = glGetUniformLocation(compute_illumination->getID(), "lights_specular");
	GLuint t_uniloc = glGetUniformLocation(compute_illumination->getID(), "t");

	GLuint lights_count_uniloc = glGetUniformLocation(compute_illumination->getID(), "lights_count");
	//utiliser une list pour les lights sinon ca va planter...

	float lights_position[MAX_LIGHT_COUNT][4];
	float lights_ambient[MAX_LIGHT_COUNT][4];
	float lights_diffuse[MAX_LIGHT_COUNT][4];
	float lights_specular[MAX_LIGHT_COUNT][4];

	int p = 0;
	float mvf[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mvf);
	Matrx44 mvm(mvf);
	Matrx44 pos;

	for (int i = 0; i < MAX_LIGHT_COUNT; i++)
	{
		if (lights[i] != NULL)
		{
			pos.setPos(lights[i]->getPosition());
			Vect4 position = (mvm*pos).getPos();
			Vect4 ambient = lights[i]->getAmbient();
			Vect4 diffuse = lights[i]->getDiffuse();
			Vect4 specular = lights[i]->getSpecular();

			position.toFloatv(lights_position[p]);
			ambient.toFloatv(lights_ambient[p]);
			diffuse.toFloatv(lights_diffuse[p]);
			specular.toFloatv(lights_specular[p]);

			p++;
		}
	}

	glUniform4fv(lights_positions_uniloc, MAX_LIGHT_COUNT, lights_position[0]);
	glUniform4fv(lights_ambient_uniloc, MAX_LIGHT_COUNT, lights_ambient[0]);
	glUniform4fv(lights_diffuse_uniloc, MAX_LIGHT_COUNT, lights_diffuse[0]);
	glUniform4fv(lights_specular_uniloc, MAX_LIGHT_COUNT, lights_specular[0]);
	glUniform1ui(lights_count_uniloc, lights_count);
	glUniform1f(t_uniloc, (float)t);

	//Draw
	glBindBuffer(GL_ARRAY_BUFFER, coord_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, normals_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indice_buffer_object);
	for (int o = 0; o < GameEngine::MAX_GAME_OBJECT_COUNT; o++)
	{
		if (gameobject[o] != NULL)
		{

			RenderableComponent *model = gameobject[o]->getModel();
			if (model != NULL){
				PhysicalComponent *physicalComponent = gameobject[o]->getPhysicalComponent();
				glPushMatrix();
				float transform[16];
				physicalComponent->getTransform().toGlMatrix(transform);
				glMultMatrixf(transform);

				for (int i = 0; i < model->getIndexCount(); i++)
				{
					Material *material = model->getMaterials()[i];
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
					unsigned int textureId = model->getTextures()[i];

					if (textureId != UINT_MAX)
					{
						glBindTexture(GL_TEXTURE_2D, textureId);
						glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer_object);
					}

					//glScalef(10,10,10);
					if (index != NULL)
					{
						glDrawElements(GL_TRIANGLES, index->index_length * 3, GL_UNSIGNED_INT, (GLvoid *)(index->index_start * 3 * sizeof(GL_UNSIGNED_INT)));
					}
				}
				glPopMatrix();
			}
		}
		
	}
	compute_illumination->stop();
}


int Renderer::addLight(Light *light)
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

RenderableComponent *Renderer::getModels()
{
	return models;
}

Program* Renderer::getCompute_illumination()
{
	return compute_illumination;
}

Light **Renderer::getLights()
{
	return lights;
}

unsigned int Renderer::getLights_count()
{
	return lights_count;
}

unsigned int Renderer::getVertice_array_object()
{
	return vertice_array_object;
}

unsigned int Renderer::getCoord_buffer_object(){
	return coord_buffer_object;
}

unsigned int Renderer::getTexcoord_buffer_object()
{
	return texcoord_buffer_object;
}

unsigned int Renderer::getNormals_buffer_object()
{
	return normals_buffer_object;
}

unsigned int Renderer::getIndice_buffer_object()
{
	return indice_buffer_object;
}

unsigned int Renderer::getIndex_count()
{
	return index_count;
}