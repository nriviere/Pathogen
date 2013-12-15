#include "VBO.h"
#include "ShadersInc.h"
#include "ShaderException.h"
#include "MyEngine.h"
#include "exception"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\GLExt.h>
#include "InGameState.h"
#include "Renderer.h"



SCENE *scene = NULL;

using namespace std;

unsigned int Renderer::EXPLOSION_PARTICLE_TEXTURE_ID = 0;

Renderer::Renderer(MyEngine *engine)
{
	models = NULL;
	materials = NULL;
	material_count = model_count = currentLightCount = 0;
	vertice_array_object = normals_buffer_object = coord_buffer_object = indice_buffer_object = index_count = 0;
	logs.open("log.txt", ios::trunc);
	this->engine = engine;
	width = 1920;
	height = 1080;
	lightsChanged = true;
	currentLightCount = 0;
}

void Renderer::init(){
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
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
		logs << e->what();
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
			Material m(
				Vect4(objects[s]->pMaterials[i].pfAmbient),
				Vect4(objects[s]->pMaterials[i].pfDiffuse),
				Vect4(objects[s]->pMaterials[i].pfSpecular),
				objects[s]->pMaterials->fShininess);
			materials[material_pos++] = m;
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

	//PARTICLES TEXTURES
	
	IMAGE_DATA *particleTexture;
	particleTexture = ReadTGA("Textures/ExplosionParticle2.tga");
	glGenTextures(1, &EXPLOSION_PARTICLE_TEXTURE_ID);
	glBindTexture(GL_TEXTURE_2D, EXPLOSION_PARTICLE_TEXTURE_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, particleTexture->u32Width, particleTexture->u32Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, particleTexture->pu8Pixels);
	glTexEnvi(GL_TEXTURE, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBindTexture(GL_TEXTURE_2D, 0);

	try{
		initApi();
		
		//FRAMEBUFFERS

		for (int i = 0; i < DEPTH_PEELING_PASS_COUNT; i++)
		{
			framebufferIds[i] = 0;
			glGenFramebuffers(1, &framebufferIds[i]);
			glBindFramebuffer(GL_FRAMEBUFFER, framebufferIds[i]);

			renderedTextures[i] = 0;
			glGenTextures(1, &renderedTextures[i]);
			glBindTexture(GL_TEXTURE_2D, renderedTextures[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);

			depthTextures[i] = 0;
			glGenTextures(1, &depthTextures[i]);
			glBindTexture(GL_TEXTURE_2D, depthTextures[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTextures[i], 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextures[i], 0);
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				exit(-250);
			}
			GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers(1, DrawBuffers);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

	
		//SHADERS

		Shader *s1 = new Shader("shaders/tp1v.gls", GL_VERTEX_SHADER);
		shaders.push_back(s1);
		s1->init();
		s1->loadSource();
		s1->loadShader();

		Shader *f1 = new Shader("shaders/tp1f.gls", GL_FRAGMENT_SHADER);
		shaders.push_back(f1);
		f1->init();
		f1->loadSource();
		f1->loadShader();

		Shader *f3 = new  Shader("shaders/depthWritef.gls", GL_FRAGMENT_SHADER);
		shaders.push_back(f3);
		f3->init();
		f3->loadSource();
		f3->loadShader();
		
		depthShader = new Program();
		depthShader->setShader(s1, 0);
		depthShader->setShader(f3, 1);
		glBindAttribLocation(depthShader->getID(), 0, "in_position");
		glBindAttribLocation(depthShader->getID(), 1, "in_normal");
		depthShader->linkProgram();
		programs.push_back(depthShader);
		
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
	glDeleteFramebuffers(DEPTH_PEELING_PASS_COUNT, framebufferIds);
	glDeleteTextures(DEPTH_PEELING_PASS_COUNT,renderedTextures);
	glDeleteTextures(DEPTH_PEELING_PASS_COUNT, depthTextures);
	logs.close();
}

void Renderer::render(GameObject **gameobject, unsigned int count, unsigned int u32Width, unsigned u32Height, Level *level)
{
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1.*u32Width / u32Height, 1, 1000);
	//glOrtho(-1.*width/2., 1.*width/2., -1.*height/2.,1.*height/2., -400, 400);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	glColor3f(1, 0, 0);

	//Placer la camera// faire un objet cam�ra
	glTranslatef(0, 0, -200);
	float mvf[16]; 
	glGetFloatv(GL_MODELVIEW_MATRIX, mvf); //Utiliser nos propres matrices
	updateLightUniforms(Matrx44(mvf));

	glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferIds[0]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//light test
	glColor4f(1, 1, 1, 1);
	/*glBegin(GL_QUADS);
	glVertex3f(-200, -200, -50);
	glVertex3f(200, -200, -50);
	glVertex3f(200, 200, -50);
	glVertex3f(-200, 200, -50);
	glEnd();*/
	//
	
	
	compute_illumination->start();

	
	

	render(compute_illumination);
	compute_illumination->stop();
	renderParticles();
	renderLevel(level);
	for (int i = 1; i < DEPTH_PEELING_PASS_COUNT; i++)
	{
		depthShader->start();
		glBindFramebuffer(GL_FRAMEBUFFER, framebufferIds[i]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, depthTextures[i-1]);

		GLuint depthTexID = glGetUniformLocation(depthShader->getID(), "depthTex");
		GLuint width_uniloc = glGetUniformLocation(depthShader->getID(), "width");
		GLuint height_uniloc = glGetUniformLocation(depthShader->getID(), "height");
		glUniform1i(depthTexID, 0);
		glUniform1f(width_uniloc, width);
		glUniform1f(height_uniloc, height);
		render(depthShader);
		depthShader->stop();
	}


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glViewport(0, 0, u32Width, u32Height);

	
	



	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	
	glDisable(GL_LIGHTING);
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, level->getBackgroundTextureId());
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, 0);
	glEnd();

	
	for (int i = DEPTH_PEELING_PASS_COUNT - 1; i >= 0 ; i--)
	{
		glColor4f(1,1,1,1);
		glBindTexture(GL_TEXTURE_2D, renderedTextures[i]);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(-1,-1,0);
		glTexCoord2f(1,0);
		glVertex3f(1,-1,0);
		glTexCoord2f(1,1);
		glVertex3f(1,1,0);
		glTexCoord2f(0,1);
		glVertex3f(-1,1,0);
		glEnd();
	}
	


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glTranslatef(0, 1.* height, 0);
	glScalef(1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawHud(width, height);

	glDisable(GL_BLEND);

	
	glEnable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::renderLevel(Level *level)
{
	//Rendu du niveau temporaire
	glDisable(GL_LIGHTING);
	glColor3f(1., 0., 0.);
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
}

void Renderer::render(Program *program)
{
	GameObject **gameobject = engine->getGameEngine()->getGameObjects();

	GLuint lights_positions_uniloc = glGetUniformLocation(program->getID(), "lights_position");
	GLuint lights_ambient_uniloc = glGetUniformLocation(program->getID(), "lights_ambient");
	GLuint lights_diffuse_uniloc = glGetUniformLocation(program->getID(), "lights_diffuse");
	GLuint lights_specular_uniloc = glGetUniformLocation(program->getID(), "lights_specular");
	GLuint lights_misc_uniloc = glGetUniformLocation(program->getID(), "lights_misc");
	GLuint t_uniloc = glGetUniformLocation(program->getID(), "t");

	GLuint material_ambient_uniloc = glGetUniformLocation(program->getID(), "material_ambient");
	GLuint material_diffuse_uniloc = glGetUniformLocation(program->getID(), "material_diffuse");
	GLuint material_specular_uniloc = glGetUniformLocation(program->getID(), "material_specular");
	GLuint material_shininess_uniloc = glGetUniformLocation(program->getID(), "material_shininess");

	GLuint mvm_uniloc = glGetUniformLocation(program->getID(), "MV");
	GLuint p_uniloc = glGetUniformLocation(program->getID(), "P");

	GLuint lights_count_uniloc = glGetUniformLocation(program->getID(), "lights_count");

	//utiliser une list pour les lights sinon ca va planter...

	int p = 0;
	float mvf[16], pf[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mvf);
	glGetFloatv(GL_PROJECTION_MATRIX, pf);
	Matrx44 mvm(mvf);
	Matrx44 pos;

	glUniformMatrix4fv(p_uniloc, 1, FALSE, pf);

	glUniform4fv(lights_positions_uniloc, MAX_LIGHT_COUNT, lightUniformPosition[0]);
	glUniform4fv(lights_ambient_uniloc, MAX_LIGHT_COUNT, lightUniformAmbient[0]);
	glUniform4fv(lights_diffuse_uniloc, MAX_LIGHT_COUNT, lightUniformDiffuse[0]);
	glUniform4fv(lights_specular_uniloc, MAX_LIGHT_COUNT, lightUniformSpecular[0]);
	glUniform4fv(lights_misc_uniloc, MAX_LIGHT_COUNT, lightUniformMisc[0]);
	glUniform1ui(lights_count_uniloc, currentLightCount);

	//Draw
	glBindVertexArray(vertice_array_object);
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
				glGetFloatv(GL_MODELVIEW_MATRIX, mvf);
				glUniformMatrix4fv(mvm_uniloc, 1, FALSE, mvf);

				for (int i = 0; i < model->getIndexCount(); i++)
				{
					Material *material = model->getMaterials()[i];
					if (material != NULL){
						glUniform4f(material_ambient_uniloc, material->getAmbient()[0], material->getAmbient()[1], material->getAmbient()[2], material->getAmbient()[3]);
						glUniform4f(material_diffuse_uniloc, material->getDiffuse()[0], material->getDiffuse()[1], material->getDiffuse()[2], material->getDiffuse()[3]);
						glUniform4f(material_specular_uniloc, material->getSpecular()[0], material->getSpecular()[1], material->getSpecular()[2], material->getSpecular()[3]);
						glUniform1f(material_shininess_uniloc, material->getShininess());
					}
					else
					{
						glUniform4f(material_ambient_uniloc, 1, 1, 1, 1);
						glUniform4f(material_diffuse_uniloc, 1, 1, 1, 1);
						glUniform4f(material_specular_uniloc, 1, 1, 1, 1);
						glUniform1f(material_shininess_uniloc, 1);
					}

					vbo_index *index = model->getIndices()[i];
					unsigned int textureId = model->getTextures()[i];

					if (textureId != UINT_MAX)
					{
						//glBindTexture(GL_TEXTURE_2D, textureId);
						//glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer_object);
						//glBindTexture(GL_TEXTURE_2D, 0);
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
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Renderer::addLight(Light *light)
{
	if (currentLightCount < MAX_LIGHT_COUNT)
	{
		
		lights.push_back(light);
		list<Light*>::iterator id = lights.end();
		id--;
		light->setId(id);
		currentLightCount++;
		lightsChanged = true;
		return 0;
	}
	else
	{
		return -1;
	}
}

void Renderer::removeLight(Light *light)
{
	//ce serait cool de pouvoir tester si cette light est bien dans la liste (faire nos propres iterator ? quand ?)
	toRemove.push_back(light);
	lightsChanged = true;
}

void Renderer::updateLightUniforms(Matrx44 modelView)
{
	while (toRemove.size() != 0)
	{
		lights.erase(toRemove.front()->getId());
		toRemove.pop_front();
		currentLightCount--;
	}

	list<Light*>::iterator l = lights.begin();
	if (lights.size() != currentLightCount)
	{
		//exit(-30);
	}
	for (int i = 0; i < currentLightCount; i++)
	{
		float v[4];
		(*l)->getAmbient().toFloatv(v);
		memcpy(lightUniformAmbient[i], v, 4 * sizeof(float));
		(*l)->getDiffuse().toFloatv(v);
		memcpy(lightUniformDiffuse[i], v, 4 * sizeof(float));
		(*l)->getSpecular().toFloatv(v);
		memcpy(lightUniformSpecular[i], v, 4 * sizeof(float));
		(modelView *(*l)->getPosition()).toFloatv(v);
		memcpy(lightUniformPosition[i], v, 4 * sizeof(float));
		lightUniformMisc[i][0] = (*l)->getRange();
		lightUniformMisc[i][1] = (*l)->getAttenuation();
		lightUniformMisc[i][2] = lightUniformMisc[i][3] = 0;
		++l;
	}
}
void Renderer::renderParticles()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	
	GameEngine *gameEngine = engine->getGameEngine();
	ParticleSystem **particleSystems = gameEngine->getParticleSystems();
	Particle **particles = NULL;
	unsigned int particleSystemCount = gameEngine->getParticleSystemCount();
	unsigned int particleCount;
	Vect4 position;
	PhysicalComponent *physicalComponent = NULL;
	Particle *particle = NULL;
	glColor4f(1., 1., 1., 1.);
	
	
	for (int i = 0; i < GameEngine::MAX_PARTICLE_SYSTEM_COUNT; i++)
	{
		if (particleSystems[i] != NULL)
		{
			ParticleSystem * particleSystem = particleSystems[i];
			particles = particleSystem->getParticles();
			particleCount = particleSystem->getMaxParticleCount();


			for (int j = 0; j < particleCount; j++)
			{
				particle = particles[j];
				if (particle != NULL)
				{
					unsigned int id = particle->getTextureId();
					glBindTexture(GL_TEXTURE_2D, id);
					glBegin(GL_QUADS);
					physicalComponent = particle->getPhysicalComponent();
					position = physicalComponent->getPosition();
					float size = particle->getSize() / 2;
					glTexCoord2f(0,0);
					glNormal3f(0,0,-1);
					glVertex3f(position[0] - size, position[1] - size, 0);
					glTexCoord2f(1, 0);
					glNormal3f(0, 0, -1);
					glVertex3f(position[0] + size, position[1] - size, 0);
					glTexCoord2f(1, 1);
					glNormal3f(0, 0, -1);
					glVertex3f(position[0] + size, position[1] + size, 0);
					glTexCoord2f(0, 1);
					glNormal3f(0, 0, -1);
					glVertex3f(position[0] - size, position[1] + size, 0);
					glEnd();
				}
			}
		}
	}
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}
void Renderer::render_string(float x, float y, float z, void* font, const char* s)
{
	glColor3f(.5f, .5f, .5f);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2f(x, y);
	while (*s)
	{
		glutBitmapCharacter(font, *s);
		s++;
	}
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::setColorRtoG(float &r, float &g, float position)
{
	if (position <= .5f)
	{
		r = 1;
		g = 2 * position;
	}
	else{
		r = 2 * (1 - position);
		g = 1;
	}
}

void Renderer::drawQuads(float x, float y, float width, float height)
{
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x, y + height);
	glVertex2f(x + width, y + height);
	glVertex2f(x + width, y);
	glEnd();
}

void Renderer::drawHud(unsigned int width, unsigned int height)
{
	int score = 0;
	float tim = 0;
	float c1, c2;
	float mun = 1.f;
	float mun1 = 1.f;
	float mun2 = 1.f;
	

	string s1 = "SCORE : ";
	string s2 = to_string(score);
	string s = s1 + s2;
	const char *c = s.c_str();
	render_string(10, 20, 0, GLUT_BITMAP_9_BY_15, c);

	string t1 = "TEMPS : ";
	string t2 = to_string((int)tim);
	string t = t1 + t2;
	const char *ct = t.c_str();
	render_string(width / 2 - 80, 20, 0, GLUT_BITMAP_9_BY_15, ct);

	glDisable(GL_TEXTURE_2D);

	setColorRtoG(c1, c2, mun);
	glColor3f(c1, c2, 0);
	drawQuads(1700, 20, 200 * mun, 10);

	setColorRtoG(c1, c2, mun1);
	glColor3f(c1, c2, 0);
	drawQuads(1700, 40, 200 * mun1, 10);

	setColorRtoG(c1, c2, mun2);
	glColor3f(c1, c2, 0);
	drawQuads(1700, 60, 200 * mun2, 10);
	glEnable(GL_TEXTURE_2D);
}


void Renderer::setWidht(unsigned int width)
{
	this->width = width;

}

void Renderer::setHeight(unsigned int height)
{
	this->height = height;
}

RenderableComponent *Renderer::getModels()
{
	return models;
}

Program* Renderer::getCompute_illumination()
{
	return compute_illumination;
}

list<Light*> Renderer::getLights()
{
	return lights;
}

unsigned int Renderer::getCurrentLightCount()
{
	return currentLightCount;
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