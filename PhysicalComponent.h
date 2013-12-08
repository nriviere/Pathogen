#pragma once
#include "stdafx.h"
#include "Vect4.h"
#include "Matrx44.h"
#include <list>


class GameObject;


class PhysicalComponent
{
private :
	unsigned int getNewID();
	std::list<unsigned int> unusedIDs;
	static unsigned int PhysicalComponent::currentID;
protected :
	int ID;
	unsigned int engineIndex;
	Matrx44 transform;
	Vect4 speed,position,verticalSpeed,horizontalSpeed;
	float acceleration,verticalAcceleration,horizontalAcceleration,maxSpeed;
	float baseAcceleration, baseDeceleration;
	float radius;
	float currentAngle,rotationSpeed,rotationAcceleration;
	GameObject *gameObject;
	std::list<PhysicalComponent*>::iterator gridPosition;
	unsigned int gridX, gridY;

public:
	static unsigned int PhysicalComponent::MAX_COMPONENTS_COUNT;
	PhysicalComponent(GameObject *gameObject = NULL);
	PhysicalComponent(const PhysicalComponent &physicalComponent);
	PhysicalComponent &operator=(const PhysicalComponent &physicalComponent);
	~PhysicalComponent();

	Matrx44 getTransform();
	Vect4 getSpeed();
	Vect4 &getPosition();
	float getAcceleration();
	float getRadius();
	std::list<PhysicalComponent*>::iterator getGridPosition();
	unsigned int getGridX();
	unsigned int getGridY();
	unsigned int getEngineIndex();
	unsigned int getID();
	GameObject *getGameObject();
	
	void setTransform(Matrx44 transform);
	void setSpeed(Vect4 speed);
	void setPosition(Vect4 position);
	void setAcceleration(float acceleration);
	void setGameObject(GameObject *object);
	void setGridPosition(std::list<PhysicalComponent*>::iterator gridPosition, unsigned int x, unsigned int y);

	virtual void setHeading(Vect4 v);

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

	void setEngineIndex(unsigned int index);

	virtual PhysicalComponent *clone();
};

