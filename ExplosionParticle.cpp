#include "ExplosionParticle.h"
#include "SelfMovingPhysicalComponent.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "Renderer.h"

#include <ctime>

ExplosionParticle::ExplosionParticle(PhysicalComponent *physicalComponent, ParticleSystem *particleSystem, float lifeLength, float maxSize, float minSize)
: Particle(physicalComponent, particleSystem, lifeLength, maxSize, minSize)
{
	physicalComponent->setPriority(-1);
	textureId = Renderer::EXPLOSION_PARTICLE_TEXTURE_ID;
}


ExplosionParticle::~ExplosionParticle()
{
}
