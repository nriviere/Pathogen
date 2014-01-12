#include "Enemy.h"

Enemy::Enemy(GameEngine *engine, float replicateTime) : ReplicableGameObject(engine, replicateTime)
{
	objectType = enemyType;
}

Enemy::Enemy(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent, float replicateTime) : ReplicableGameObject(engine, model, physicalComponent, replicateTime)
{
	objectType = enemyType;
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