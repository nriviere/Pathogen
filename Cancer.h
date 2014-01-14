#pragma once
#include "Enemy.h"
#include "SelfMovingPhysicalComponent.h"
#include "CancerPhysicalComponent.h"

class CancerState;
class UndeclaredCancerState;
class DeclaredCancerState;

class Cancer :
	public Enemy
{
protected:
	CancerState *currentCancerState;
	UndeclaredCancerState *undeclaredCancerState;
	DeclaredCancerState *declaredCancerState;
	float cancerProbability;
	CancerPhysicalComponent *cancerPhysicalComponent;
public:
	Cancer(GameEngine *engine = NULL);
	Cancer(GameEngine *engine, CancerPhysicalComponent *physicalComponent);
	Cancer(const Cancer &cell);
	Cancer &operator=(const Cancer &cell);
	~Cancer();
	virtual void update();
	virtual void replicate();
	virtual void destroy();
	virtual void selfRemove();
	virtual void hitBy(ObjectType objectType);
	virtual void undeclaredHitBy(ObjectType objectType);
	virtual void declaredHitBy(ObjectType objectType);
	virtual void undeclaredUpdate();
	virtual void declaredUpdate();
	virtual void undeclaredReplicate();
	virtual void declaredReplicate();

	void setDeclaredState();
	void setCancerPhysicalComponent(CancerPhysicalComponent *component);
	
};

class CancerState
{
protected:
	Cancer *cancer;
public:
	CancerState(Cancer *cancer = NULL) : cancer(cancer)
	{}
	virtual void hitBy(ObjectType objectType)=0;
	virtual void update()=0;
	virtual void replicate()=0;
};

class UndeclaredCancerState : public CancerState
{
public:
	UndeclaredCancerState(Cancer *cancer = NULL) : CancerState(cancer)
	{}
	virtual void hitBy(ObjectType objectType);
	virtual void update();
	virtual void replicate();
};

class DeclaredCancerState : public CancerState
{
public :
	DeclaredCancerState(Cancer *cancer = NULL) : CancerState(cancer)
	{}
	virtual void hitBy(ObjectType objectType);
	virtual void update();
	virtual void replicate();
};

