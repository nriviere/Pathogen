#include "Projectile.h"
#include "GameEngine.h"
#include "MyEngine.h"
#include "ProjectilePhysicalComponent.h"


Projectile::Projectile() : LightingGameObject(NULL)
{

}

Projectile::Projectile(GameEngine *engine) : LightingGameObject(engine)
{
	type = 0;
	if (engine != NULL){
		this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::PROJECTILE_MODEL_INDEX];
	}
	else
	{
		model = NULL;
	}

	PhysicalEngine *physicalEngine = NULL;
	if (engine != NULL)
	{
		physicalEngine = engine->getParentEngine()->getPhysicalEngine();
	}
	this->physicalComponent = new ProjectilePhysicalComponent(this, physicalEngine);

	if (this->physicalComponent != NULL)
	{
		light->setPosition(this->physicalComponent->getPosition());
		light->setRange(40.);
		light->setAttenuation(0.8);
	}
	objectType = projectileType;
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

void Projectile::hit(GameObject *gameObject)
{
	gameObject->hitBy(this);
}
