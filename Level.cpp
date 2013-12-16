#include "Level.h"
#include "tinyxml.h"
#include "Cell.h"
#include "Bacteria.h"
#include "Cancer.h"
#include "Virus.h"
#include "GameEngine.h"

Level::Level(const char *filename, GameEngine *engine)
{
	this->engine = engine;
	this->filename = filename;
	limitsX[0] = -200;
	limitsY[0] = -150;
	limitsX[1] = 200;
	limitsY[1] = 150;
}


Level::~Level()
{
}

float *Level::getLimitsX()
{
	return limitsX;
}
float *Level::getLimitsY()
{
	return limitsY;
}

void Level::load()
{
	TiXmlDocument *doc = new TiXmlDocument(filename);
	bool loadOkay = doc->LoadFile();
	if (!loadOkay) {
		//cout << "Couldn't load " << filename << " " << doc->ErrorDesc() << endl;
		exit(-8);
	}
	TiXmlNode* node = 0;

	node = doc->FirstChildElement("Level");
	//Parsing des params du niveau si besoin

	TiXmlNode* spawnLineNode;
	spawnLineNode = node->FirstChildElement("SpawnLine");
	while (spawnLineNode){
		SpawnLine *spawnLine = new SpawnLine(this);
		TiXmlElement* spawnPoolNode = 0;
		spawnPoolNode = spawnLineNode->FirstChildElement("SpawnPool");
		while (spawnPoolNode)
		{
			SpawnPool *spawnPool = new SpawnPool();
			TiXmlElement* gameObject = 0;
			gameObject = spawnPoolNode->FirstChildElement("GameObject");
			while (gameObject)
			{
				const char *className = gameObject->Attribute("class");
				int count = atoi(gameObject->Attribute("count"));
				GameObject **gameObjects = instantiateObjects(className, count);
				spawnPool->addObjects(gameObjects, count);
				delete[] gameObjects;
				gameObject = gameObject->NextSiblingElement();
			}
			spawnLine->addSpawnPool(spawnPool);
			spawnPoolNode = spawnPoolNode->NextSiblingElement();
		}
		spawnLines.push_back(spawnLine);
		spawnLineNode = spawnLineNode->NextSiblingElement();
	}
	delete doc;
	glGenTextures(1, &backgroundTextureId);
	IMAGE_DATA *backGroundTexture;
	backGroundTexture = ReadTGA("Textures/BackgroundLevel1.tga");
	glGenTextures(1, &backgroundTextureId);
	glBindTexture(GL_TEXTURE_2D, backgroundTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, backGroundTexture->u32Width, backGroundTexture->u32Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, backGroundTexture->pu8Pixels);
	//glTexEnvi(GL_TEXTURE, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete backGroundTexture;
}

void Level::init()
{
	for (list<SpawnLine *>::iterator s = spawnLines.begin(); s != spawnLines.end();)
	{
		(*s)->loadToEngine();
		++s;
	}
}

void Level::update()
{
	for (list<SpawnLine *>::iterator s = spawnLines.begin(); s != spawnLines.end();)
	{
		(*s)->update();
		++s;
	}
}

void Level::setGameEngine(GameEngine *engine)
{
	this->engine = engine;
}

unsigned int Level::getBackgroundTextureId()
{
	return backgroundTextureId;
}

GameEngine *Level::getGameEngine()
{
	return engine;
}

GameObject **Level::instantiateObjects(const char *className, unsigned int count)
{
	GameObject **gameObjects = new GameObject*[count];

	ObjectType objectType;

	if (strcmp(className, "Bacteria") == 0)
	{
		objectType = bacteriaType;
	}
	else if (strcmp(className, "Virus") == 0)
	{
		objectType = virusType;
	}
	else if (strcmp(className, "Cancer") == 0)
	{
		objectType = cancerType;
	}
	else if (strcmp(className, "Cell") == 0) {
		objectType = cellType;
	}else
	{
		objectType = gameObjectType;
	}

	for (int i = 0; i < count; i++)
	{
		gameObjects[i] = instantiateObject(objectType);
	}
	return gameObjects;
}

GameObject *Level::instantiateObject(ObjectType objectType)
{
	GameObject *gameObject;
	switch (objectType)
	{
	case cellType:gameObject = new Cell(engine);
		break;
	case bacteriaType:gameObject = new Bacteria(engine);
		break;
	case virusType:gameObject = new Virus(engine);
		break;
	case cancerType:gameObject = new Cancer(engine);
		break;
	default: return NULL;
		break;
	}
	float x = limitsX[0] + (1.*rand() / RAND_MAX) * (limitsX[1] - limitsX[0]);
	float y = limitsY[0] + (1.*rand() / RAND_MAX) * (limitsY[1] - limitsY[0]);
	gameObject->getPhysicalComponent()->setPosition(Vect4(x,y,0,1));
	return gameObject;
}