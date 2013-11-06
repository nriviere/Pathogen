#include "MyLight.h"


MyLight::MyLight()
{

}

MyLight::MyLight(Matrx44 light)
{
	this->light = light;
}

Matrx44 MyLight::getMatrix()
{
	return light;
}

Vect4 MyLight::getAmbient()
{
	return light.getX();
}

Vect4 MyLight::getDiffuse(){
	return light.getY();
}

Vect4 MyLight::getSpecular(){
	return light.getZ();
}

Vect4 MyLight::getPosition(){
	return light.getW();
}

MyLight::~MyLight()
{
}
