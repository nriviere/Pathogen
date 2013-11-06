#pragma once
#ifndef MYMATERIAL_H
#define MYMATERIAL_H

#include "Vect4.h"

class MyMaterial
{
private:
	Vect4 ambient, diffuse, specular;
	float shininess;
	public:
	MyMaterial();
	MyMaterial(const MyMaterial &material);
	MyMaterial &operator=(const MyMaterial &material);
	MyMaterial(Vect4, Vect4, Vect4,float);
	Vect4 getAmbient();
	Vect4 getDiffuse();
	Vect4 getSpecular();
	float getShininess();
	~MyMaterial();
};
#endif