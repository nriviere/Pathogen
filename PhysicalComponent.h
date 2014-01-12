#pragma once
#include "stdafx.h"
#include "Vect4.h"
#include "Matrx44.h"
#include <list>


class GameObject;
class PhysicalEngine;

class PhysicalComponent
{
private :
	unsigned int getNewID();
	std::list<unsigned int> unusedIDs;
	static unsigned int PhysicalComponent::currentID;
protected :
	unsigned int engineIndex;
	Matrx44 transform;
	Vect4 speed,position,verticalSpeed,horizontalSpeed;
	float acceleration,verticalAcceleration,horizontalAcceleration,maxSpeed;
	float baseAcceleration, baseDeceleration;
	float radius;
	float currentAngle,rotationSpeed,rotationAcceleration;
	GameObject *gameObject;
	PhysicalEngine *engine;
	std::list<PhysicalComponent*>::iterator gridPosition;
	unsigned int gridX, gridY;
	int priority;
	PhysicalComponent *attachment;

public:
	static unsigned int PhysicalComponent::MAX_COMPONENTS_COUNT;
	PhysicalComponent(GameObject *gameObject = NULL,PhysicalEngine *engine = NULL);
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
	GameObject *getGameObject();
	PhysicalEngine *getEngine();
	int getPriority();
	PhysicalComponent *getAttachment();
	
	void setTransform(Matrx44 transform);
	void setSpeed(Vect4 speed);
	void setRadius(float radius);
	void setPosition(Vect4 position);
	void setAcceleration(float acceleration);
	void setGameObject(GameObject *object);
	void setGridPosition(std::list<PhysicalComponent*>::iterator gridPosition, unsigned int x, unsigned int y);
	void setEngine(PhysicalEngine *engine);
	void setPriority(int priority);
	void setAttachment(PhysicalComponent *component);

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
	void destroy();

	virtual PhysicalComponent *clone();
};

