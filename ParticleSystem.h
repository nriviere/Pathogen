#pragma once
#include "Particle.h"
#include "Timer.h"

class GameEngine;
class ParticleSystem
{
protected:
	Particle **particles;
	unsigned int maxParticleCount, currentParticleCount, gameEngineIndex;
	GameEngine *engine;
public:
	ParticleSystem(GameEngine *engine=NULL);
	ParticleSystem(const ParticleSystem &ParticleSystem);
	ParticleSystem &operator=(const ParticleSystem &ParticleSystem);
	~ParticleSystem();
	virtual void update(float fDT);
	void setGameEngine(GameEngine *engine);
	void setGameEngineIndex(unsigned int index);
	virtual void selfAdd();
	virtual void selfRemove();
	unsigned int getEngineIndex();
	unsigned int getMaxParticleCount();
	unsigned int getCurrentParticleCount();
	Particle **getParticles();

};

