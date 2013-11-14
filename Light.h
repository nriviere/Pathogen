#pragma once
#include "stdafx.h"

#include "Matrx44.h"

class Light
{
private:
	Matrx44 light;
public:

	Light();
	Light(Matrx44 light);
	Matrx44 getMatrix();
	Vect4 getAmbient();
	Vect4 getDiffuse();
	Vect4 getSpecular();
	Vect4 getPosition();
	~Light();
};

