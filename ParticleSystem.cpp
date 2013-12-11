#include "ParticleSystem.h"
#include "GameEngine.h"



ParticleSystem::ParticleSystem(GameEngine *engine)
{
	currentParticleCount = maxParticleCount = 0;
	gameEngineIndex = UINT_MAX;
}

ParticleSystem::ParticleSystem(const ParticleSystem &particleSystem)
{
	currentParticleCount = particleSystem.currentParticleCount;
	maxParticleCount = particleSystem.maxParticleCount;
	particles = new Particle*[particleSystem.maxParticleCount];
	for (int i = 0; i < maxParticleCount; i++)
	{
		particles[i] = particleSystem.particles[i];
	}
}
ParticleSystem &ParticleSystem::operator=(const ParticleSystem &particleSystem)
{
	delete [] particles;
	ParticleSystem::ParticleSystem(particleSystem);
	return *this;
}

ParticleSystem::~ParticleSystem()
{
	delete [] particles;
}

void ParticleSystem::selfAdd()
{

}

void ParticleSystem::selfRemove()
{

}

void ParticleSystem::update(float fDT)
{
	int count = 0;
	for (int i = 0; i < maxParticleCount; i++)
	{
		if (particles[i] != NULL)
		{
			Particle *particle = particles[i];
			particle->update(fDT);
			if (particle->isDead())
			{
				particle->remove();
				delete particle;
				particles[i] = NULL;
				currentParticleCount--;
				MyEngine::errlog << currentParticleCount << endl;
			}
		}
	}
	if (currentParticleCount == 0)
	{
		engine->setParticleSystemToRemove(this);
	}
}

void ParticleSystem::setGameEngine(GameEngine *engine)
{
	this->engine = engine;
}

void ParticleSystem::setGameEngineIndex(unsigned int index)
{
	this->gameEngineIndex = index;
}

unsigned int ParticleSystem::getEngineIndex()
{
	return gameEngineIndex;
}

unsigned int ParticleSystem::getMaxParticleCount()
{
	return maxParticleCount;
}

unsigned int ParticleSystem::getCurrentParticleCount()
{
	return currentParticleCount;
}

Particle **ParticleSystem::getParticles()
{
	return particles;
}
