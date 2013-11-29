#pragma once
#include "stdafx.h"
#include <list>

#include "Matrx44.h"

class Light
{
private:
	Matrx44 light;
	std::list<Light*>::iterator id;
	float range, attenuation;

public:

	Light();
	Light(Matrx44 light,float range, float attenuation);
	Matrx44 getMatrix();
	Vect4 getAmbient();
	Vect4 getDiffuse();
	Vect4 getSpecular();
	Vect4 getPosition();
	float getRange();
	float getAttenuation();

	void setRange(float range);
	void setAttenuation(float attenuation);
	void setPosition(Vect4 position);
	std::list<Light*>::iterator getId();
	void setId(std::list<Light*>::iterator id);
	~Light();
};

