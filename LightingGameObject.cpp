#include "LightingGameObject.h"
#include "GameEngine.h"
#include "MyEngine.h"

LightingGameObject::LightingGameObject(GameEngine *engine) : GameObject(engine)
{
	light = new Light();
	objectType = lightingGameObjectType;
}


LightingGameObject::~LightingGameObject()
{
	delete light;
}

Light *LightingGameObject::getLight()
{
	return light;
}

void LightingGameObject::setLight(Light *light)
{
	this->light = light;
}

void LightingGameObject::update()
{
	light->setPosition(physicalComponent->getPosition());
}

void LightingGameObject::selfAdd()
{
	GameObject::selfAdd();
	this->engine->getParentEngine()->getRenderer()->addLight(light);
}

void LightingGameObject::selfRemove()
{
	GameObject::selfRemove();
	this->engine->getParentEngine()->getRenderer()->removeLight(light);
}