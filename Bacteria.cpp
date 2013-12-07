#include "Bacteria.h"
#include "Enemy.h"
#include "Renderer.h"
#include "MyEngine.h"
#include "Renderer.h"
#include "GameEngine.h"
#include "CellPhysicalComponent.h"


Bacteria::Bacteria(GameEngine *engine) : Enemy(engine)
{
	objectType = bacteriaType;
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::BACTERIA_MODEL_INDEX];
	physicalComponent = new CellPhysicalComponent();
	physicalComponent->setGameObject(this);
}

Bacteria::Bacteria(GameEngine *engine, PhysicalComponent *physicalComponent) : Enemy(engine,NULL, physicalComponent, 3)
{
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::BACTERIA_MODEL_INDEX];
	objectType = bacteriaType;
}

Bacteria::Bacteria(const Bacteria &bacteria) : Enemy(bacteria)
{
	objectType = bacteriaType;
}

Bacteria &Bacteria::operator=(const Bacteria &bacteria)
{
	Bacteria::Bacteria(bacteria);
	objectType = bacteriaType;
	return *this;
}

Bacteria::~Bacteria()
{
}

void Bacteria::replicate()
{

}

void Bacteria::hitBy(Projectile *projectile)
{
	destroy();
}

void Bacteria::hitBy(ObjectType objectType)
{
	switch (objectType){
		
	case projectileType: 
		destroy();
		break;

	default: break;


	}
}