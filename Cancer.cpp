#include "Cancer.h"
#include "Enemy.h"
#include "Renderer.h"
#include "MyEngine.h"
#include "Renderer.h"
#include "GameEngine.h"
#include "CellPhysicalComponent.h"
#include "Explosion.h"


Cancer::Cancer(GameEngine *engine) : Enemy(engine)
{
	objectType = cancerType;
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::CANCER_MODEL_INDEX];
	physicalComponent = new CellPhysicalComponent();
	physicalComponent->setGameObject(this);
	physicalComponent->setPriority(1);
	physicalComponent->setRadius(7);
}

Cancer::Cancer(GameEngine *engine, PhysicalComponent *physicalComponent) : Enemy(engine, NULL, physicalComponent, 3)
{
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::CANCER_MODEL_INDEX];
	objectType = cancerType;
	physicalComponent->setPriority(1);
}

Cancer::Cancer(const Cancer &cancer) : Enemy(cancer)
{
	objectType = cancerType;
}

Cancer &Cancer::operator=(const Cancer &cancer)
{
	Cancer::Cancer(cancer);
	objectType = cancerType;
	return *this;
}

Cancer::~Cancer()
{
}

void Cancer::replicate()
{

}

void Cancer::destroy()
{
	Explosion *explosion = new Explosion(physicalComponent->getPosition());
	engine->addParticleSystem(explosion);
	Enemy::destroy();
}

void Cancer::selfRemove()
{
	Enemy::selfRemove();

}

void Cancer::hitBy(ObjectType objectType)
{
	switch (objectType){

	case lymphocyteTagCancer:

		destroy();
		break;

	default: break;


	}
}