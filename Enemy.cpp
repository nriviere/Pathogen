#include "Enemy.h"

Enemy::Enemy(GameEngine *engine, float replicateTime) : ReplicableGameObject(engine, replicateTime)
{
	objectType = enemyType;
	selfMovingPhysicalComponent = NULL;
}

Enemy::Enemy(GameEngine *engine, RenderableComponent *model, SelfMovingPhysicalComponent *physicalComponent, float replicateTime) : ReplicableGameObject(engine, model, physicalComponent, replicateTime)
{
	objectType = enemyType;
	selfMovingPhysicalComponent = physicalComponent;
}

Enemy::~Enemy()
{
}

void Enemy::selfAdd()
{
	ReplicableGameObject::selfAdd();
}
void Enemy::selfRemove()
{
	ReplicableGameObject::selfRemove();
}