#include "Projectile.h"
#include "GameEngine.h"
#include "MyEngine.h"
#include "ProjectilePhysicalComponent.h"

Projectile::Projectile(GameEngine *engine) : GameObject(engine)
{
	physicalComponent = new ProjectilePhysicalComponent(this);
	if (engine != NULL){
		this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::PROJECTILE_MODEL_INDEX];
	}
	else
	{
		model = NULL;
	}
}

Projectile::~Projectile()
{
}

void Projectile::setHeading(Vect4 v)
{
	physicalComponent->setHeading(v);
}