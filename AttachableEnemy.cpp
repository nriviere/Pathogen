#include "AttachableEnemy.h"
#include "AttachablePhysicalComponent.h"
#include "GameEngine.h"


AttachableEnemy::AttachableEnemy(GameEngine *engine, float replicateTime) : Enemy(engine, replicateTime)
{
	attachedState = new AttachedEnemyState(this);
	unattachedState = new UnattachedEnemyState(this);
	currentState = unattachedState;
	physicalComponent = attachablePhysicalComponent = new AttachablePhysicalComponent(NULL,this, engine->getParentEngine()->getPhysicalEngine());
}

AttachableEnemy::AttachableEnemy(GameEngine *engine, RenderableComponent *model, AttachablePhysicalComponent *physicalComponent, float replicateTime)
: Enemy(engine, model, physicalComponent, 3)
{
	attachedState = new AttachedEnemyState(this);
	unattachedState = new UnattachedEnemyState(this);
	currentState = unattachedState;
	attachablePhysicalComponent = physicalComponent;
	if (physicalComponent == NULL)
	{
		physicalComponent = attachablePhysicalComponent = new AttachablePhysicalComponent(NULL, this, engine->getParentEngine()->getPhysicalEngine());
	}
	
}

AttachableEnemy::AttachableEnemy(const AttachableEnemy &enemy) : Enemy(enemy)
{
	attachedState = new AttachedEnemyState(this);
	unattachedState = new UnattachedEnemyState(this);
	currentState = unattachedState;
	//physicalComponent = attachablePhysicalComponent = new AttachablePhysicalComponent(NULL, this, engine->getParentEngine()->getPhysicalEngine());
	physicalComponent->setPosition(enemy.getPhysicalComponent()->getPosition());
}

AttachableEnemy::~AttachableEnemy()
{
	delete attachedState;
	delete unattachedState;
}


void AttachableEnemy::replicate()
{
	currentState->replicate();
}

void AttachableEnemy::hitBy(GameObject *object)
{
	currentState->hitBy(object);
}

void AttachableEnemy::attachedReplicate()
{

}

void AttachableEnemy::attachedHitBy(GameObject *object)
{

}

void AttachableEnemy::unattachedReplicate()
{

}

void AttachableEnemy::unattachedHitBy(GameObject *object)
{

}


void AttachableEnemy::attachedSelfRemove()
{

}

void AttachableEnemy::unattachedSelfRemove()
{

}

void AttachableEnemy::selfRemove()
{
	currentState->selfRemove();
}