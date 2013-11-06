#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class Model3D;

class GameObject
{
private : 
	Model3D *model;
public:
	GameObject();
	GameObject(Model3D *model);
	Model3D *getModel();
	void setModel(Model3D *model);
	~GameObject();
};
#endif
