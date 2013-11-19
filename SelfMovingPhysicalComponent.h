#pragma once
#include "Force.h"
#include "PhysicalComponent.h"
#include <list>



class SelfMovingPhysicalComponent :
	public PhysicalComponent
{
private:
	Force innerForce;
	std::list<Force> forces;
	float baseSpeed;
public:
	SelfMovingPhysicalComponent();
	~SelfMovingPhysicalComponent();

	Force getInnerForce();
	void setInnerForce(Force f);

	void collision(Vect4 axis);

	void update();
};

