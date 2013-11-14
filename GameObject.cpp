#include "GameObject.h"
#include <iostream>
#include "RenderableComponent.h"

GameObject::GameObject()
{
	this->model = NULL;
	this->physicalComponent = NULL;
}

GameObject::GameObject(const GameObject &gameObject)
{
	model = gameObject.model;
	physicalComponent = gameObject.physicalComponent;
}
GameObject &GameObject::operator=(const GameObject &gameObject)
{
	model = gameObject.model;
	physicalComponent = gameObject.physicalComponent;
	return (*this);
}

GameObject::~GameObject()
{

}

GameObject::GameObject(RenderableComponent *model, PhysicalComponent *physicalComponent)
{
	this->model = model;
	this->physicalComponent = physicalComponent;
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