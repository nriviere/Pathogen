#pragma once
#include "PhysicalComponent.h"
#include <list>
class BacteriaWastePhysicalComponent :
	public PhysicalComponent
{
protected:
	std::list<PhysicalComponent*> slowedList;
public:
	BacteriaWastePhysicalComponent(GameObject *gameObject = NULL, PhysicalEngine *engine = NULL);
	BacteriaWastePhysicalComponent(const BacteriaWastePhysicalComponent &physicalComponent);
	~BacteriaWastePhysicalComponent();

	virtual void update();
	virtual void collision(Vect4 axis);
	virtual void collision(PhysicalComponent *physicalComponent);
	virtual void destroy();
	virtual void slow(PhysicalComponent *physicalComponent);

	virtual void sendDestroyed(PhysicalComponent *component);
};

