#include "UpdaterThread.h"


pthread_cond_t UpdaterThread::init_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t UpdaterThread::mutex_init = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t UpdaterThread::start_update = PTHREAD_COND_INITIALIZER;
pthread_mutex_t UpdaterThread::mutex_start = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t UpdaterThread::finish_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t UpdaterThread::mutex_finish = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t UpdaterThread::counter_locker = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t UpdaterThread::test = PTHREAD_MUTEX_INITIALIZER;


unsigned int UpdaterThread::counter = 0;
unsigned int UpdaterThread::counter_init = 0;
void UpdaterThread::startUpdate()
{
	pthread_cond_broadcast(&start_update);
}


UpdaterThread::UpdaterThread()
{
	params = NULL;
}

UpdaterThread::UpdaterThread(UpdaterThreadParameters *params) : Thread(params)
{

}
UpdaterThread::~UpdaterThread()
{
	delete params;
}

void *UpdaterThread::fonction()
{
	
	UpdaterThreadParameters * p = static_cast<UpdaterThreadParameters*>(params);
	p->setRunning(true);
	//pthread_mutex_lock(p->getWaitLocker());
	unsigned int start = p->getOffset(), step = p->getStep(), stopX = p->getNx(), stopY = p->getNy();
	unsigned int pos = 0, nX = p->getNx(), nY = p->getNy(), stepX = p->getStepX(), stepY = p->getStepY();
	unsigned int stop = ceil(1.*(nY - start) / step);
	Vect4 position;
	float fx = 0, fy = 0, minX = 0, maxX = 0, minY = 0, maxY = 0;
	PhysicalComponent* comp = NULL;
	std::list<PhysicalComponent*> *toReassign = p->getReassignList();

/*	pthread_mutex_lock(&UpdaterThread::counter_locker);
/*		UpdaterThread::counter_init++;

	if (counter_init == step)
	{
		pthread_mutex_lock(&UpdaterThread::mutex_init);
		pthread_cond_signal(&UpdaterThread::init_cond);
		pthread_mutex_unlock(&UpdaterThread::mutex_init);
	}

	pthread_mutex_unlock(&UpdaterThread::counter_locker);
	
	

	while (p->isRunning())
	{
	
		pthread_cond_wait(&start_update, p->getWaitLocker());

		pthread_mutex_lock(&UpdaterThread::counter_locker);
		UpdaterThread::counter++;
		pthread_mutex_unlock(&UpdaterThread::counter_locker);
		
		pthread_mutex_lock(&test);*/

		std::list<PhysicalComponent*> **components = p->getComponents();
		std::list<PhysicalComponent*> newComponents, reassign;
		for (int y = 0; y < stop; y += step)
		{
			for (int x = 0; x < stopX; x++)
			{
				minX = x*stepX; maxX = (x + 1)*stepX; minY = y*stepY; maxY = (y + 1)*stepY;
				
				for (std::list<PhysicalComponent*>::iterator ite = components[pos]->begin();
					ite != components[pos]->end();)
				{
					comp = (*ite);
					position = comp->getPosition();
					if (position[0] < minX || position[0] > maxX ||
						position[1] < minY || position[1] > maxY)
					{
						toReassign->push_back(*ite);
						ite = components[pos]->erase(ite);
					}
					else
					{
						++ite;
					}
				}
				pos++;
			}
		}
		
	
		/*


		pthread_mutex_lock(&UpdaterThread::counter_locker);
		UpdaterThread::counter--;
		if (counter == 0){
			pthread_mutex_lock(&UpdaterThread::mutex_finish);
			pthread_cond_broadcast(&UpdaterThread::finish_cond);
			pthread_mutex_unlock(&UpdaterThread::mutex_finish);
		}
		pthread_mutex_unlock(&UpdaterThread::counter_locker);

	}*/
	return NULL;
}

void UpdaterThread::join(void **retval)
{
	pthread_join(thread, retval);
}

void UpdaterThread::stop()
{
	static_cast<UpdaterThreadParameters*>(params)->setRunning(false);
}

void UpdaterThread::lockWait()
{
	pthread_mutex_lock(static_cast<UpdaterThreadParameters*>(params)->getWaitLocker());
}

void UpdaterThread::unlockWait()
{
	pthread_mutex_unlock(static_cast<UpdaterThreadParameters*>(params)->getWaitLocker());
}

std::list<PhysicalComponent*> *UpdaterThread::getReassignList(){
	return static_cast<UpdaterThreadParameters *>(params)->getReassignList();
}


void UpdaterThread::startWaiting()
{
	pthread_mutex_lock(&UpdaterThread::mutex_finish);
}

void UpdaterThread::waitFinish()
{
	pthread_cond_wait(&UpdaterThread::finish_cond, &UpdaterThread::mutex_finish);
}

