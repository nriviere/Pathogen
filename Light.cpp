#include "Light.h"


Light::Light()
{

}

Light::Light(Matrx44 light)
{
	this->light = light;
}

Matrx44 Light::getMatrix()
{
	return light;
}

Vect4 Light::getAmbient()
{
	return light.getOx();
}

Vect4 Light::getDiffuse(){
	return light.getOy();
}

Vect4 Light::getSpecular(){
	return light.getOz();
}

Vect4 Light::getPosition(){
	return light.getPos();
}

Light::~Light()
{
}
