#include "GameObject.h"
#include <iostream>
#include "RenderableComponent.h"
#include "GameEngine.h"

GameObject::GameObject(GameEngine *engine)
{
	this->engine = engine;
	this->model = NULL;
	this->physicalComponent = NULL;
	gameEngineIndex = UINT_MAX;
}

GameObject::GameObject(const GameObject &gameObject)
{
	model = gameObject.model;
	physicalComponent = gameObject.physicalComponent->clone();
	physicalComponent->setGameObject(this);
	this->engine = gameObject.engine;
	gameEngineIndex = UINT_MAX;
}
GameObject &GameObject::operator=(const GameObject &gameObject)
{
	delete physicalComponent;
	GameObject::GameObject(gameObject);
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
}

void GameObject::update()
{

}

void GameObject::destroy()
{
	engine->setToRemove(gameEngineIndex);
}
RenderableComponent *GameObject::getModel()
{
	return model;
}

PhysicalComponent *GameObject::getPhysicalComponent()
{
	return physicalComponent;
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

unsigned int GameObject::getGameEngineIndex()
{
	return gameEngineIndex;
}

GameEngine *GameObject::getGameEngine()
{
	return engine;
}