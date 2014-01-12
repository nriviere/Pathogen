#pragma once
#include "Enemy.h"

class AttachableEnemyState;
class AttachedEnemyState;
class UnattachedEnemyState;
class AttachablePhysicalComponent;

class AttachableEnemy :
	public Enemy
{
protected:
	AttachableEnemyState *currentState;
	AttachedEnemyState *attachedState;
	UnattachedEnemyState *unattachedState;
	AttachablePhysicalComponent *attachablePhysicalComponent;
public:
	AttachableEnemy(GameEngine *engine = NULL, float replicateTime = 3);
	AttachableEnemy(GameEngine *engine, RenderableComponent *model, AttachablePhysicalComponent *physicalComponent, float replicateTime = 3);
	AttachableEnemy(const AttachableEnemy &enemy);
	~AttachableEnemy();

	virtual void replicate();
	virtual void hitBy(GameObject *object);

	virtual void attachedReplicate();
	virtual void attachedHitBy(GameObject *object);
	virtual void attachedSelfRemove();

	virtual void unattachedReplicate();
	virtual void unattachedHitBy(GameObject *object);
	virtual void unattachedSelfRemove();

	virtual void selfRemove();
};

class AttachableEnemyState
{
protected : 
	AttachableEnemy *attachableEnemy;
public : 
	AttachableEnemyState(AttachableEnemy *attachableEnemy = NULL) : attachableEnemy(attachableEnemy)
	{}
	virtual void replicate(){};
	virtual void hitBy(GameObject *object){};
	virtual void selfRemove(){};
};

class AttachedEnemyState : public AttachableEnemyState
{
public:
	AttachedEnemyState(AttachableEnemy *attachableEnemy = NULL) : AttachableEnemyState(attachableEnemy)
	{

	}
	virtual void replicate()
	{
		attachableEnemy->attachedReplicate();
	}

	virtual void hitBy(GameObject *object)
	{
		attachableEnemy->attachedHitBy(object);
	}

	virtual void selfRemove()
	{
		attachableEnemy->attachedSelfRemove();
	}
};

class UnattachedEnemyState : public AttachableEnemyState
{
public:
	UnattachedEnemyState(AttachableEnemy *attachableEnemy = NULL) : AttachableEnemyState(attachableEnemy)
	{

	}
	virtual void replicate()
	{
		attachableEnemy->unattachedReplicate();
	}

	virtual void hitBy(GameObject *object)
	{
		attachableEnemy->unattachedHitBy(object);
	}

	virtual void selfRemove()
	{
		attachableEnemy->unattachedSelfRemove();
	}
};
