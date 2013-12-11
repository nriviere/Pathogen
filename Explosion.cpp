#include "Explosion.h"
#include "ExplosionParticle.h"
#include "SelfMovingPhysicalComponent.h"
#include "Vect4.h"
#include "Force.h"
#include "MyEngine.h"

Explosion::Explosion(Vect4 position)
{
	maxParticleCount = (1.*rand() / RAND_MAX) * 10 + 20;
	particles = new Particle*[maxParticleCount];
	for (int i = 0; i < maxParticleCount; i++)
	{
		particles[i] = NULL;
	}
	float lifeLength = 0;
	float maxSize = 0, minSize =  0;
	float speed = 0;
	SelfMovingPhysicalComponent *physicalComponent;
	Force speedf;
	//MyEngine::errlog << "Explosion : " << position[0] << " " << position[1] << " " << position[2] << " " << position[3] << endl;
	float maxLife = 0;
	for (int i = 0; i < maxParticleCount; i++)
	{
		lifeLength = ((1.*rand() / RAND_MAX) + 0.5);
		if (lifeLength > maxLife) maxLife = lifeLength;
		maxSize = (1.*rand() / RAND_MAX)*100 + 1;
		minSize = (1.*rand() / RAND_MAX) * 1 + 2;
		speed = (1.*rand() / RAND_MAX)*3 + 1;
		speedf[0] = (1.*rand() / RAND_MAX);
		speedf[1] = (1.*rand() / RAND_MAX);
		speedf[2] = 0;
		speedf[3] = 1;
		speedf.normalize();
		speedf = speedf * speed;
		speedf.setAcceleration(/*(1.*rand() / RAND_MAX) * 0.1 + */0.0001);

		physicalComponent = new SelfMovingPhysicalComponent();
		physicalComponent->setInnerForce(speedf);
		physicalComponent->setPosition(position);
		physicalComponent->setRadius(2);
		//physicalComponent->update();
		//MyEngine::errlog << speedf[0] << "  " << speedf[1] << " " << speedf[2] << " " << speedf[3] << " " << speedf.getAcceleration() << endl;
		particles[i] = new ExplosionParticle(physicalComponent, this, lifeLength, maxSize, minSize);
	}
	int count = 0;
	for (int i = 0; i < maxParticleCount; i++)
	{
		if (particles[i] != NULL)
		{
			count++;
		}
	}
	if (count != maxParticleCount)
	{
		MyEngine::errlog << "LOL !" << endl;
		MyEngine::errlog.close();
		exit(-25);
	}
	currentLightRange = maxLightRange = 150;
	currentParticleCount = maxParticleCount;
	light = new Light(Matrx44(
		1, 1, 1, 1,
		1, 1, 1, 1,
		1, 1, 1, 1,
		1, 1, 1, 1),
		maxLightRange,
		0.5);
	light->setPosition(position);
	maxLightLife = maxLife;
	currentLightLife = 0;
}


Explosion::~Explosion()
{
}

void Explosion::update(float fDt)
{
	ParticleSystem::update(fDt);
	currentLightLife += fDt;
	
	currentLightRange = maxLightRange - (currentLightLife / maxLightLife)* maxLightRange;
	if (currentLightRange <= 0) currentLightRange = 0.1;
	light->setRange(currentLightRange);
}

void Explosion::selfAdd()
{
	engine->getParentEngine()->getRenderer()->addLight(light);
}

void Explosion::selfRemove()
{
	engine->getParentEngine()->getRenderer()->removeLight(light);
	light = NULL;
}