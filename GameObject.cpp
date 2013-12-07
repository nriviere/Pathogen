#include "GameObject.h"
#include <iostream>
#include "RenderableComponent.h"
#include "GameEngine.h"
#include "SpawnPool.h"

GameObject::GameObject(GameEngine *engine)
{
	this->engine = engine;
	this->model = NULL;
	this->physicalComponent = NULL;
	gameEngineIndex = UINT_MAX;
	spawnPool = NULL;
	objectType = gameObjectType;
	spawnPool = NULL;
}

GameObject::GameObject(const GameObject &gameObject)
{
	model = gameObject.model;
	physicalComponent = gameObject.physicalComponent->clone();
	physicalComponent->setGameObject(this);
	this->engine = gameObject.engine;
	gameEngineIndex = UINT_MAX;
	objectType = gameObjectType;
	spawnPool = NULL;
}
GameObject &GameObject::operator=(const GameObject &gameObject)
{
	delete physicalComponent;
	GameObject::GameObject(gameObject);
	objectType = gameObjectType;
	spawnPool = gameObject.spawnPool;
	return (*this);
}

GameObject::~GameObject()
{

}

GameObject::GameObject(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent)
{
	this->engine = engine;
	this->model = model;
	this->physicalComponent = physicalComponent;
	this->physicalComponent->setGameObject(this);
	spawnPool = NULL;
}

void GameObject::update()
{

}

void GameObject::destroy()
{
	engine->setToRemove(gameEngineIndex);
}


void GameObject::selfRemove()
{
	if (spawnPool != NULL)
	{
		spawnPool->removeObject(this);
	}
}

void GameObject::selfAdd()
{

}

RenderableComponent *GameObject::getModel()
{
	return model;
}

PhysicalComponent *GameObject::getPhysicalComponent()
{
	return physicalComponent;
}

ObjectType GameObject::getObjectType()
{
	return objectType;
}

unsigned int GameObject::getGameEngineIndex()
{
	return gameEngineIndex;
}

GameEngine *GameObject::getGameEngine()
{
	return engine;
}

SpawnPool *GameObject::getSpawnPool()
{
	return spawnPool;
}

void GameObject::setPhysicalComponent(PhysicalComponent *physicalComponent)
{
	this->physicalComponent = physicalComponent;
}

void GameObject::setModel(RenderableComponent *model)
{
	this->model = model;
}

void GameObject::setGameEngineIndex(unsigned int index)
{
	gameEngineIndex = index;
}

void GameObject::setSpawnPool(SpawnPool *spawnPool)
{
	this->spawnPool = spawnPool;
}

void GameObject::setGameEngine(GameEngine *engine)
{
	this->engine = engine;
}

void GameObject::hitBy(GameObject *gameObject)
{
	//oh really ?
	hitBy(gameObject->getObjectType());
}

void GameObject::hitBy(ObjectType type)
{

}