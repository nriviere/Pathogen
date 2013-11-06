#include "GameObject.h"
#include <iostream>
#include "Model3D.h"

GameObject::GameObject()
{
	model = NULL;
}
GameObject::GameObject(Model3D *model)
{
	this->model = model;
}

GameObject::~GameObject()
{
}

Model3D *GameObject::getModel()
{
	return model;
}