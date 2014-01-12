#include "ReplicableGameObject.h"
#include "GameEngine.h"


ReplicableGameObject::ReplicableGameObject() : GameObject()
{
	objectType = replicableGameObjectType;
	replicateTime = 3;
	replicateTimer = new Timer(replicateTime);
}

ReplicableGameObject::ReplicableGameObject(GameEngine *engine, float replicateTime) : GameObject(engine)
{
	objectType = replicableGameObjectType;
	replicateTimer = new Timer(replicateTime);
	this->replicateTime = replicateTime;
}

ReplicableGameObject::ReplicableGameObject(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent, float replicateTime) : GameObject(engine,model, physicalComponent)
{
	objectType = replicableGameObjectType;
	replicateTimer = new Timer(replicateTime);
	this->replicateTime = replicateTime;
}

ReplicableGameObject::ReplicableGameObject(const ReplicableGameObject &object) : GameObject(object)
{
	objectType = replicableGameObjectType;
	replicateTime = object.replicateTime;
	replicateTimer = new Timer(object.replicateTime);
}

ReplicableGameObject &ReplicableGameObject::operator=(const ReplicableGameObject &object)
{
	delete replicateTimer;
	GameObject::GameObject(object);
	objectType = replicableGameObjectType;
	return (*this);
}

ReplicableGameObject::~ReplicableGameObject()
{
	delete replicateTimer;
}


void ReplicableGameObject::update()
{
	replicateTimer->update(engine->getDeltaTime());
	if (replicateTimer->hasTicked())
	{
		replicate();
	}
}

void ReplicableGameObject::selfAdd()
{
	GameObject::selfAdd();
}
void ReplicableGameObject::selfRemove()
{
	GameObject::selfRemove();
}