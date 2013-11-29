#include "Light.h"


Light::Light()
{
	this->light = Matrx44(0.1,0.1,0.1,1.,0.5,0.5,0.5,1.,1.,1.,1.,1.,0.,0.,0.,1);
	attenuation = 0;
	range = 0;
}

Light::Light(Matrx44 light, float range, float attenuation)
{
	this->light = light;
	this->range = range;
	this->attenuation = attenuation;
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

float Light::getRange()
{
	return range;
}
float Light::getAttenuation()
{
	return attenuation;
}

void Light::setRange(float range)
{
	this->range = range;
}
void Light::setAttenuation(float attenuation)
{
	this->attenuation = attenuation;
}

std::list<Light*>::iterator Light::getId()
{
	return id;
}

void Light::setId(std::list<Light*>::iterator id)
{
	this->id = id;
}

void Light::setPosition(Vect4 position)
{
	light.setPos(position);
}

Light::~Light()
{
}
