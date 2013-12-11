#pragma once
#include "PhysicalComponent.h"
#include "RenderableComponent.h"

class ParticleSystem;
class Particle
{
protected:
	PhysicalComponent *physicalComponent;
	ParticleSystem * particleSystem;
	RenderableComponent *model;
	float lifeLength, size, maxSize, minSize,currentLife;
	bool isAlive;
	unsigned int textureId;
public:
	Particle(PhysicalComponent *physicalComponent = NULL, ParticleSystem * particleSystem = NULL, float lifeLength = 1, float maxSize = 1, float minSize = 1);
	~Particle();
	virtual void update(float fDt);
	void destroy();
	void remove();
	bool isDead();
	void setPhysicalComponent(PhysicalComponent *physicalComponent);
	PhysicalComponent *getPhysicalComponent();
	unsigned int getTextureId();
	float getSize();
};

