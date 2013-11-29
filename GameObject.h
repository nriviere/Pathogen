#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "stdafx.h"
#include <stdio.h>
#include <list>
#include "PhysicalComponent.h"
#include "RenderableComponent.h"

class GameEngine;
class RenderableComponent;

class GameObject
{
protected : 
	RenderableComponent *model;
	PhysicalComponent *physicalComponent;
	GameEngine *engine;
	unsigned int gameEngineIndex;

public:
	GameObject(GameEngine *engine = NULL);
	GameObject(const GameObject &gameObject);
	GameObject &operator=(const GameObject &gameObject);
	~GameObject();

	GameObject(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent);
	RenderableComponent *getModel();
	PhysicalComponent *getPhysicalComponent();
	void setModel(RenderableComponent *model);
	void setPhysicalComponent(PhysicalComponent *physicalComponent);
	virtual void update();
	void destroy();

	void setGameEngineIndex(unsigned int index);
	unsigned int getGameEngineIndex();

	GameEngine *getGameEngine();
	
};
#endif
