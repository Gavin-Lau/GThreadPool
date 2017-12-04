#ifndef _PTHREAD_LOCK_H_
#define _PTHREAD_LOCK_H_

#include <pthread.h>
#include <assert.h>
#include "atomic.h"

/**
 * 锁和条件变量类
 */
class Syncer {

public:

	Syncer() : m_signal(false)
	{ 
		pthread_mutex_init(m_mutex, NULL);
		pthread_cond_init(m_cond, NULL);
	}

	~Syncer() 
	{ 
		pthread_cond_destroy(m_cond);
		pthread_mutex_destroy(m_mutex); 
	}


	int Lock() { pthread_mutex_lock(m_mutex); }

	int unLock() { pthread_mutex_unlock(m_mutex); }

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

	void notifyAll() //Todo:多消费者模型，使用单个m_signal有问题
	{
		pthread_mutex_lock(m_mutex);
		m_signal = true;
		pthread_mutex_unlock(m_mutex);
		pthread_cond_broadcast(m_cond);
	}

private:
	pthread_mutex_t*	m_mutex;
	pthread_cond_t*  m_cond;
	bool			 m_signal;

};

#endif //_PTHREAD_LOCK_H_
