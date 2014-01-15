#include "Cancer.h"
#include "Enemy.h"
#include "Renderer.h"
#include "MyEngine.h"
#include "Renderer.h"
#include "GameEngine.h"
#include "CellPhysicalComponent.h"
#include "Explosion.h"
#include "CancerPhysicalComponent.h"


Cancer::Cancer(GameEngine *engine) : Enemy(engine)
{
	objectType = cancerTypeUndeclared;
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::CELL_MODEL_INDEX];
	physicalComponent = selfMovingPhysicalComponent = cancerPhysicalComponent = new CancerPhysicalComponent(this,engine->getParentEngine()->getPhysicalEngine());
	physicalComponent->setGameObject(this);
	physicalComponent->setPriority(1);
	physicalComponent->setRadius(10);
	declaredCancerState = new DeclaredCancerState(this);
	undeclaredCancerState = new UndeclaredCancerState(this);
	currentCancerState = undeclaredCancerState;
	cancerProbability = (1. / 60) / 7.;
	replicateTime = 10;
}

Cancer::Cancer(GameEngine *engine, CancerPhysicalComponent *physicalComponent) : Enemy(engine, NULL, physicalComponent, 10)
{
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::CELL_MODEL_INDEX];
	objectType = cancerTypeUndeclared;
	physicalComponent->setPriority(1);
	cancerProbability = (1. / 60) / 7.;
	declaredCancerState = new DeclaredCancerState(this);
	undeclaredCancerState = new UndeclaredCancerState(this);
	currentCancerState = undeclaredCancerState;
	cancerPhysicalComponent = physicalComponent;
	physicalComponent->setRadius(10);
}

Cancer::Cancer(const Cancer &cancer) : Enemy(cancer.engine, cancer.model, new CancerPhysicalComponent(this,NULL), cancer.replicateTime)
{
	objectType = cancerTypeUndeclared;
	cancerProbability = (1. / 60) / 7.;
	physicalComponent->setPriority(1);
	physicalComponent->setRadius(10);
	declaredCancerState = new DeclaredCancerState(this);
	undeclaredCancerState = new UndeclaredCancerState(this);
	currentCancerState = undeclaredCancerState;
}

Cancer &Cancer::operator=(const Cancer &cancer)
{
	Cancer::Cancer(cancer);
	objectType = cancer.objectType;
	return *this;
}

Cancer::~Cancer()
{
	delete declaredCancerState;
	delete undeclaredCancerState;
}

void Cancer::update()
{
	Enemy::update();
	currentCancerState->update();
}

void Cancer::replicate()
{
	currentCancerState->replicate();
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
	engine->getDebriefingState()->updateStatistics(this->objectType, objectType);

	currentCancerState->hitBy(objectType);
}

void Cancer::undeclaredHitBy(ObjectType objectType)
{

}
void Cancer::declaredHitBy(ObjectType objectType)
{
	switch (objectType){

	case lymphocyteTagCancer:
		destroy();
		break;

	default: break;
	}
}

void Cancer::undeclaredUpdate()
{
	float proba = 1. * rand() / RAND_MAX;
	if (proba < cancerProbability){
		setDeclaredState();
	}
}
void Cancer::declaredUpdate()
{

}

void Cancer::undeclaredReplicate()
{
	
}

void Cancer::declaredReplicate()
{
	Cancer *cancer = new Cancer(*this);
	cancer->getPhysicalComponent()->setPosition(physicalComponent->getPosition());
	cancer->setDeclaredState();
	engine->addObject(cancer);
}

void Cancer::setDeclaredState()
{
	objectType = cancerTypeDeclared;
	currentCancerState = declaredCancerState;
	model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::CANCER_MODEL_INDEX];
	/*Force newInnerForce = selfMovingPhysicalComponent->getInnerForce();
	newInnerForce.setAcceleration(0.7);
	selfMovingPhysicalComponent->setInnerForce(newInnerForce);*/
	cancerPhysicalComponent->setDeclaredState();

}

void Cancer::setCancerPhysicalComponent(CancerPhysicalComponent *component)
{
	cancerPhysicalComponent = component;
}

void UndeclaredCancerState::hitBy(ObjectType objectType)
{
	cancer->undeclaredHitBy(objectType);
}

void DeclaredCancerState::hitBy(ObjectType objectType)
{
	cancer->declaredHitBy(objectType);
}

void DeclaredCancerState::update()
{
	cancer->declaredUpdate();
}

void UndeclaredCancerState::update()
{
	cancer->undeclaredUpdate();
}

void DeclaredCancerState::replicate()
{
	cancer->declaredReplicate();
}

void UndeclaredCancerState::replicate()
{
	cancer->undeclaredReplicate();
}