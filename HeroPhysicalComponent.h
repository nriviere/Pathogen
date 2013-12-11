#pragma once
#include "PhysicalComponent.h"
#include "Cursor.h"
class GameObject;
class HeroPhysicalComponent :
	public PhysicalComponent
{
private:
	float angle,angleAim;
	Cursor *cursor;
public:
	HeroPhysicalComponent(Cursor *cursor = NULL, GameObject *object = NULL, PhysicalEngine *engine = NULL);
	HeroPhysicalComponent(const HeroPhysicalComponent &heroPhysicalComponent);
	HeroPhysicalComponent &operator=(const HeroPhysicalComponent &heroPhysicalComponent);
	~HeroPhysicalComponent();

	void collision(Vect4 axis);
	void collision(PhysicalComponent *physicalComponent);
	void align(Vect4 position);

	void update();

	HeroPhysicalComponent *clone();
};

