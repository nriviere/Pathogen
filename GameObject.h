#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <stdio.h>
#include "PhysicalComponent.h"

class RenderableComponent;

class GameObject
{
protected : 
	RenderableComponent *model;
	PhysicalComponent *physicalComponent;
public:
	GameObject();
	GameObject(const GameObject &gameObject);
	GameObject &operator=(const GameObject &gameObject);
	~GameObject();

	GameObject(RenderableComponent *model, PhysicalComponent *physicalComponent);
	RenderableComponent *getModel();
	PhysicalComponent *getPhysicalComponent();
	void setModel(RenderableComponent *model);
	void setPhysicalComponent(PhysicalComponent *physicalComponent);
	
};
#endif
