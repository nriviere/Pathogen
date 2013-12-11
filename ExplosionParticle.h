#pragma once
#include "Particle.h"
class ParticleSystem;
class ExplosionParticle :
	public Particle
{
public:
	ExplosionParticle(PhysicalComponent *physicalComponent = NULL, ParticleSystem *particleSystem = NULL,
		float lifeLength = 1, float maxSize = 1,float minSize = 1);
	~ExplosionParticle();
};

