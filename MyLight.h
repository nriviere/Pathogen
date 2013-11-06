#pragma once
#include "stdafx.h"

#include "Matrx44.h"

class MyLight
{
private:
	Matrx44 light;
public:

	MyLight();
	MyLight(Matrx44 light);
	Matrx44 getMatrix();
	Vect4 getAmbient();
	Vect4 getDiffuse();
	Vect4 getSpecular();
	Vect4 getPosition();
	~MyLight();
};

