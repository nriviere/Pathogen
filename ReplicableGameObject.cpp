#include "ReplicableGameObject.h"
#include "GameEngine.h"


ReplicableGameObject::ReplicableGameObject() : GameObject()
{
	replicateTime = 3;
	replicateTimer = new Timer(replicateTime);
}

ReplicableGameObject::ReplicableGameObject(GameEngine *engine, float replicateTime) : GameObject(engine)
{
	replicateTimer = new Timer(replicateTime);
}

ReplicableGameObject::ReplicableGameObject(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent, float replicateTime) : GameObject(engine,model, physicalComponent)
{
	replicateTimer = new Timer(replicateTime);
	this->replicateTime = replicateTime;
}

ReplicableGameObject::ReplicableGameObject(const ReplicableGameObject &object) : GameObject(object)
{
	replicateTime = object.replicateTime;
	replicateTimer = new Timer(object.replicateTime);
}

ReplicableGameObject &ReplicableGameObject::operator=(const ReplicableGameObject &object)
{
	delete replicateTimer;
	GameObject::GameObject(object);
	return (*this);
}

ReplicableGameObject::~ReplicableGameObject()
{
	delete replicateTimer;
}


void ReplicableGameObject::update()
{
	replicateTimer->update();
	if (replicateTimer->hasTicked())
	{
		replicate();
	}
	
}