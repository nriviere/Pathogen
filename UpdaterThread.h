#pragma once
#ifndef UPDATERTHREAD_H
#define UPDATERTHREAD_H
#include "Thread.h"
#include "PhysicalComponent.h"
#include <list>



class UpdaterThreadParameters : public Parameters
{
private : 
	bool running;
	unsigned int step, stepX,stepY, offset, nX, nY;
	pthread_mutex_t param_locker, finish_locker, wait_locker;
	
	std::list<PhysicalComponent*> **components,*toReassign;
public :
	
	void init()
	{
		pthread_mutex_init(&param_locker, NULL);
		pthread_mutex_init(&finish_locker, NULL);
		pthread_mutex_init(&wait_locker, NULL);
		toReassign = new std::list<PhysicalComponent*>();
	};

	UpdaterThreadParameters() : Parameters()
	{
		running = false;
		step = offset = nX = nY = 0;
		components = NULL;
		init();
	};

	UpdaterThreadParameters(unsigned int step, unsigned int offset, unsigned int nX, unsigned int nY, unsigned int stepX, unsigned int stepY, std::list<PhysicalComponent*> **components) : Parameters()
	{
		running = false;
		this->step = step;
		this->offset = offset;
		this->nX = nX;
		this->nY = nY;
		this->stepX = stepX;
		this->stepY = stepY;
		this->components = components;
		init();
	};

	~UpdaterThreadParameters()
	{
		delete[] components;
		delete toReassign;
	}

	bool isRunning(){
		return running;
	}

	unsigned int getOffset()
	{
		return offset;
	}

	unsigned int getStep()
	{
		return step;
	}

	unsigned int getNx()
	{
		return nX;
	}
	unsigned int getNy()
	{
		return nY;
	}

	unsigned int  getStepX(){
		return stepY;
	}

	unsigned int  getStepY(){
		return stepX;
	}

	std::list<PhysicalComponent*> **getComponents()
	{
		return components;
	}
	
	std::list<PhysicalComponent*> *getReassignList(){
		return toReassign;
	}

	pthread_mutex_t *getFinishLocker()
	{
		return &finish_locker;
	}

	pthread_mutex_t *getWaitLocker()
	{
		return &wait_locker;
	}

	void setRunning(bool running)
	{
		pthread_mutex_lock(&param_locker);
		this->running = running;
		pthread_mutex_unlock(&param_locker);
	}
};

class UpdaterThread :
	public Thread
{
protected:
		
public:
	static pthread_cond_t init_cond;
	static pthread_mutex_t mutex_init;
	static pthread_cond_t start_update;
	static pthread_mutex_t mutex_start;
	static pthread_cond_t finish_cond;
	static pthread_mutex_t mutex_finish;
	static pthread_mutex_t counter_locker;
	static pthread_mutex_t test;
	static unsigned int counter;
	static unsigned int counter_init;

	static void startUpdate();
	static void startWaiting();
	static void waitFinish();

	UpdaterThread();
	UpdaterThread(UpdaterThreadParameters *params);
	~UpdaterThread();

	void *fonction();
	void update();
	void stop();

	void lockWait();
	void unlockWait();

	std::list<PhysicalComponent*> *getReassignList();


	virtual void join(void **retval);
};

#endif