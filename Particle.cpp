#include "Particle.h"
#include "ParticleSystem.h"
#include "PhysicalEngine.h"
#include "MyEngine.h"

Particle::Particle(PhysicalComponent *physicalComponent, ParticleSystem * particleSystem, float lifeLength, float maxSize, float minSize)
{
	this->physicalComponent = physicalComponent;
	this->particleSystem = particleSystem;
	this->lifeLength = lifeLength;
	isAlive = true;
	this->maxSize = maxSize;
	this->minSize = minSize;
	currentLife = 0;
	textureId = 0;
}


Particle::~Particle()
{
}

void Particle::update(float fDt)
{
	currentLife += fDt;
	
	if (currentLife >= lifeLength)
	{
		destroy();
	}
	size = maxSize + ((minSize - maxSize) / lifeLength) * currentLife;
}

void Particle::destroy()
{
	isAlive = false;
}

void Particle::remove()
{
	//physicalComponent->destroy();
	physicalComponent->getEngine()->remove(physicalComponent->getEngineIndex());
}

bool Particle::isDead()
{
	return !isAlive;
}

void Particle::setPhysicalComponent(PhysicalComponent *physicalComponent)
{
	this->physicalComponent = physicalComponent;
}

PhysicalComponent *Particle::getPhysicalComponent()
{
	return physicalComponent;
}

unsigned int Particle::getTextureId()
{
	return textureId;
}

float Particle::getSize()
{
	return size;
}