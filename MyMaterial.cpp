#include "MyMaterial.h"


MyMaterial::MyMaterial()
{
	shininess = 0;
}

MyMaterial::MyMaterial(Vect4 ambient, Vect4 diffuse, Vect4 specular, float shininess)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

MyMaterial::MyMaterial(const MyMaterial &material)
{
	this->ambient = material.ambient;
	this->diffuse = material.diffuse;
	this->specular = material.specular;
	this->shininess = material.shininess;
}
MyMaterial &MyMaterial::operator=(const MyMaterial &material)
{
	this->ambient = material.ambient;
	this->diffuse = material.diffuse;
	this->specular = material.specular;
	this->shininess = material.shininess;
	return *this;
}

Vect4 MyMaterial::getAmbient()
{
	return ambient;
}

Vect4 MyMaterial::getDiffuse()
{
	return diffuse;
}

Vect4 MyMaterial::getSpecular()
{
	return specular;
}

float MyMaterial::getShininess(){
	return shininess;
}

MyMaterial::~MyMaterial()
{

}
