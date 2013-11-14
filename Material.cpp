#include "Material.h"


Material::Material()
{
	shininess = 0;
}

Material::Material(Vect4 ambient, Vect4 diffuse, Vect4 specular, float shininess)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

Material::Material(const Material &material)
{
	this->ambient = material.ambient;
	this->diffuse = material.diffuse;
	this->specular = material.specular;
	this->shininess = material.shininess;
}
Material &Material::operator=(const Material &material)
{
	this->ambient = material.ambient;
	this->diffuse = material.diffuse;
	this->specular = material.specular;
	this->shininess = material.shininess;
	return *this;
}

Vect4 Material::getAmbient()
{
	return ambient;
}

Vect4 Material::getDiffuse()
{
	return diffuse;
}

Vect4 Material::getSpecular()
{
	return specular;
}

float Material::getShininess(){
	return shininess;
}

Material::~Material()
{

}
