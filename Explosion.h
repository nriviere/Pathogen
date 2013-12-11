#pragma once
#include "ParticleSystem.h"
#include "Vect4.h"
#include "Light.h"

class Explosion :
	public ParticleSystem
{
protected:
	Light *light;
	float maxLightLife, currentLightLife, maxLightRange,currentLightRange;
public:
	Explosion(Vect4 position = Vect4(0,0,0,1));
	~Explosion();
	virtual void update(float fDt);
	virtual void selfAdd();
	virtual void selfRemove();
};

