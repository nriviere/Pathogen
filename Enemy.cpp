#include "Enemy.h"

Enemy::Enemy(GameEngine *engine) : ReplicableGameObject(engine)
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