#pragma once

#include "AttachableEnemy.h"
#include "VirusPhysicalComponent.h"

class Virus :
	public AttachableEnemy
{
protected:
	float attachmentProbability;
public:
	Virus(GameEngine *engine = NULL);
	Virus(GameEngine *engine, VirusPhysicalComponent *physicalComponent);
	Virus(const Virus &cell);
	Virus &operator=(const Virus &cell);

	virtual void destroy();

	virtual void attachedReplicate();
	virtual void attachedHitBy(GameObject *object);
	virtual void unattachedReplicate();
	virtual void unattachedHitBy(GameObject *object);

	virtual void attachedSelfRemove();
	virtual void unattachedSelfRemove();
	~Virus();
};

