#ifndef _PTHREAD_LOCK_H_
#define _PTHREAD_LOCK_H_

#include <pthread.h>
#include <assert.h>
#include "atomic.h"

class Locker {

public:

	Locker() { pthread_mutex_init(m_lock, NULL); }
	Locker(pthread_mutex_t*	lock) : m_lock(lock) { }
	
	~Locker() { pthread_mutex_destroy(m_lock); }

	int Lock() { pthread_mutex_lock(m_lock); }

	int unLock() { pthread_mutex_unlock(m_lock); }

	pthread_mutex_t* getMutex() { return m_lock; }

private:
	pthread_mutex_t*	m_lock;

};


#include <pthread.h>

class Condition{

public:
	Condition(Locker& lock)
	{
		m_mutex = lock.getMutex();
		pthread_cond_init(m_cond, NULL);
	}

	Condition(pthread_mutex_t* mutex_)
	{
		m_mutex = mutex_;
		pthread_cond_init(m_cond, NULL);
	}

	~Condition() { pthread_cond_destroy(m_cond); }

	void Wait()
	{
		pthread_mutex_lock(m_mutex);
		while (!m_signal)
		{
			pthread_cond_wait(m_cond, m_mutex);
		}
		m_signal = false;
		pthread_mutex_unlock(m_mutex);
	}

	void notifyOne()
	{
		pthread_mutex_lock(m_mutex);
		m_signal = true;
		pthread_mutex_unlock(m_mutex);
		pthread_cond_signal(m_cond);
	}

private:
	pthread_mutex_t* m_mutex;
	pthread_cond_t*  m_cond;
	bool			 m_signal;
};


#endif //_PTHREAD_LOCK_H_
