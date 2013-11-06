#pragma once
#ifndef MY3DENGINE_H
#define MY3DENGINE_H
#include "3DEngine.h"
#include "Renderer.h"
#include "GameObject.h"
#include "list"

struct lightSource{
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float position[4];
};
class My3DEngine :
	public C3DEngine
{
public:
	My3DEngine(void);
	~My3DEngine(void);
	void Setup(HWND hWnd);
	void Update(float fDT);
	void Render(unsigned int u32Width, unsigned int u32Height);
	void MouseWheel(float fIncrement);
	void MouseMove(POINT Pos);
	void load(const char** fileNames, unsigned int count);
	unsigned int gameobject_count;
	GameObject **getGameObjects();

private:
	Renderer *renderer;
	GameObject **gameobjects;

};

#endif