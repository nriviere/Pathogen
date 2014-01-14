#pragma once
#include "SelfMovingPhysicalComponent.h"

class CancerPhysicalComponentState;
class CancerPhysicalComponentDeclaredState;
class CancerPhysicalComponentUndeclaredState;
class Cancer;

class CancerPhysicalComponent :
	public SelfMovingPhysicalComponent
{
protected:
	CancerPhysicalComponentState *currentState;
	CancerPhysicalComponentDeclaredState *declaredState;
	CancerPhysicalComponentUndeclaredState *undeclaredState;
	float movementProbability;
public:
	CancerPhysicalComponent(Cancer *object = NULL, PhysicalEngine *engine = NULL);
	CancerPhysicalComponent(const CancerPhysicalComponent& component);
	~CancerPhysicalComponent();

	virtual void update();
	virtual void declaredUpdate();
	virtual void undeclaredUpdate();
	virtual void collision(Vect4 axis);
	virtual void collision(PhysicalComponent *component);
	virtual void declaredCollision(Vect4 axis);
	virtual void undeclaredCollision(Vect4 axis);
	virtual void declaredCollision(PhysicalComponent *component);
	virtual void undeclaredCollision(PhysicalComponent *component);

	void setDeclaredState();
};

class CancerPhysicalComponentState
{
protected:
	CancerPhysicalComponent *cancerPhysicalComponent;
public:
	CancerPhysicalComponentState(CancerPhysicalComponent *cancerPhysicalComponent=NULL)
		: cancerPhysicalComponent(cancerPhysicalComponent)
	{}
	virtual void update()
	{}
	virtual void collision(Vect4 axis)
	{}
	virtual void collision(PhysicalComponent *component)
	{}
};

class CancerPhysicalComponentDeclaredState : public CancerPhysicalComponentState
{
public:
	CancerPhysicalComponentDeclaredState(CancerPhysicalComponent *cancerPhysicalComponent=NULL)
		:CancerPhysicalComponentState(cancerPhysicalComponent)
	{}
	virtual void update();
	virtual void collision(Vect4 axis);
	virtual void collision(PhysicalComponent *component);

};


class CancerPhysicalComponentUndeclaredState : public CancerPhysicalComponentState
{
public:
	CancerPhysicalComponentUndeclaredState(CancerPhysicalComponent *cancerPhysicalComponent = NULL)
		:CancerPhysicalComponentState(cancerPhysicalComponent)
	{}
	virtual void update();
	virtual void collision(Vect4 axis);
	virtual void collision(PhysicalComponent *component);
	
};
