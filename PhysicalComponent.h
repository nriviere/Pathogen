#pragma once
#include "stdafx.h"
#include "Vect4.h"
#include "Matrx44.h"
#include <list>



class PhysicalComponent
{
private :
	unsigned int getNewID();
	std::list<unsigned int> unusedIDs;
	static unsigned int PhysicalComponent::currentID;
protected :
	int ID;
	Matrx44 transform;
	Vect4 speed,position,verticalSpeed,horizontalSpeed;
	float acceleration,verticalAcceleration,horizontalAcceleration,maxSpeed;
	float baseAcceleration, baseDeceleration;
	float radius;

public:
	static unsigned int PhysicalComponent::MAX_COMPONENTS_COUNT;
	PhysicalComponent();
	PhysicalComponent(const PhysicalComponent &physicalComponent);
	PhysicalComponent &operator=(const PhysicalComponent &physicalComponent);
	~PhysicalComponent();

	Matrx44 getTransform();
	Vect4 getSpeed();
	Vect4 getPosition();
	float getAcceleration();
	float getRadius();
	unsigned int getID();
	
	void setTransform(Matrx44 transform);
	void setSpeed(Vect4 speed);
	void setPosition(Vect4 position);
	void setAcceleration(float acceleration);

	virtual void update();
	virtual void collision(Vect4 axis);
	virtual void collision(PhysicalComponent *physicalComponent);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void stopMoveUp();
	void stopMoveDown();
	void stopMoveRight();
	void stopMoveLeft();
};

