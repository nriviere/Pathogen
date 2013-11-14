#pragma once
#ifndef Material_H
#define Material_H

#include "Vect4.h"

class Material
{
private:
	Vect4 ambient, diffuse, specular;
	float shininess;
	public:
	Material();
	Material(const Material &material);
	Material &operator=(const Material &material);
	Material(Vect4, Vect4, Vect4,float);
	Vect4 getAmbient();
	Vect4 getDiffuse();
	Vect4 getSpecular();
	float getShininess();
	~Material();
};
#endif