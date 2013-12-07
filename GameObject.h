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
class SpawnPool;
class Projectile;

enum ObjectType{
	gameObjectType,
	cellType,
	enemyType,
	heroType,
	projectileType,
	lightingGameObjectType,
	replicableGameObjectType,
	bacteriaType,
	virusType,
	cancerType
};

class GameObject
{
protected : 
	RenderableComponent *model;
	PhysicalComponent *physicalComponent;
	GameEngine *engine;
	unsigned int gameEngineIndex;
	SpawnPool *spawnPool;
	ObjectType objectType;

public:
	GameObject(GameEngine *engine = NULL);
	GameObject(const GameObject &gameObject);
	GameObject &operator=(const GameObject &gameObject);
	~GameObject();

	GameObject(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent);
	RenderableComponent *getModel();
	PhysicalComponent *getPhysicalComponent();
	ObjectType getObjectType();
	void setModel(RenderableComponent *model);
	void setPhysicalComponent(PhysicalComponent *physicalComponent);
	void setSpawnPool(SpawnPool *spawnPool);
	void setGameEngine(GameEngine *engine);
	virtual void update();
	virtual void destroy();

	void setGameEngineIndex(unsigned int index);
	unsigned int getGameEngineIndex();
	SpawnPool *getSpawnPool();

	GameEngine *getGameEngine();
	virtual void selfAdd();
	virtual void selfRemove();

	virtual void hitBy(GameObject *gameObject);
	virtual void hitBy(ObjectType objectType);
	
};
#endif
