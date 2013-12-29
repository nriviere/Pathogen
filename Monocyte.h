#pragma once
#include "Projectile.h"
#include "HomingPhysicalComponent.h"

class Monocyte;

class MonocyteState
{
protected:
	Monocyte *monocyte;
public:
	MonocyteState(Monocyte *m = NULL) :monocyte(m){}
	virtual void hitBy(ObjectType objectType)=0;
};

class SeekNStrike : public MonocyteState
{
public:
	SeekNStrike(Monocyte *m = NULL) :MonocyteState(m){}
	void hitBy(ObjectType objectType);
};

class Comeback : public MonocyteState
{
private:
	ObjectType lymphocyteTag;
public:
	Comeback(Monocyte *m = NULL) :MonocyteState(m){}
	void setLymphocyteTag(ObjectType lymphocyteTag){ this->lymphocyteTag = lymphocyteTag; }
	ObjectType getLymphocyteTag(){ return lymphocyteTag; }
	void hitBy(ObjectType objectType);
};

class Monocyte :
	public Projectile
{
public:
	Monocyte(GameEngine *engine = NULL, GameObject *target = NULL);
	~Monocyte();

	virtual void hitBy(ObjectType objectType);
	void setTarget(GameObject *target);
	GameObject *getTarget();
	void setCurrentState(MonocyteState *state);
	Comeback *getComebackState();
	void comeback(ObjectType lymphocyteTag);
protected:
	GameObject *target;
	MonocyteState *currentState;
	SeekNStrike *seekNStrikeState;
	Comeback *comebackState;
	HomingPhysicalComponent *homingPhysicalComponent;
};

