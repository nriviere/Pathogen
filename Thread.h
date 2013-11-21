#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#include <iostream>

//Nimp

class Parameters
{
	private :
		
	public :	
};

class Thread 
{
	protected : 
		pthread_t thread;
		Parameters *params;
	public :

		static unsigned int Thread::concurrentThreadsSupported;
		Thread(){};

		Thread(Parameters *params)
		{
			this->params = params;
		}
		
		virtual void *fonction() = 0;	

		const Parameters *getParams()
		{
			return params;
		}

		static void *threadFonction(void *thread_instance)
		{
			Thread *thread = static_cast<Thread *>(thread_instance);
			return thread->fonction();
		}

		void run()
		{
			pthread_create(&thread,NULL,threadFonction,(void*)this);
		}

		virtual void join(void **retval)
		{
			pthread_join(thread,retval);
		}	
};

#endif
