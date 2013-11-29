#include "Projectile.h"
#include "GameEngine.h"
#include "MyEngine.h"
#include "ProjectilePhysicalComponent.h"

Projectile::Projectile(GameEngine *engine) : LightingGameObject(engine)
{
	physicalComponent = new ProjectilePhysicalComponent(this);
	if (engine != NULL){
		this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::PROJECTILE_MODEL_INDEX];
	}
	else
	{
		model = NULL;
	}
	light->setPosition(physicalComponent->getPosition());
	light->setRange(40.);
	light->setAttenuation(0.1);
}

Projectile::~Projectile()
{
}

void Projectile::setHeading(Vect4 v)
{
	physicalComponent->setHeading(v);
}

void Projectile::update()
{
	LightingGameObject::update();
}