#ifndef _PTHREAD_POOL_H_
#define _PTHREAD_POOL_H_

#include <iostream>
#include <map>
#include "pthread_core.h"
#include "pthread_sync.h"

class PthreadPool {

public:
	PthreadPool(std::size_t poolSize);
	~PthreadPool();
	void PostTask();

private:
	float GetLoad(); //ªÒ»°∏∫‘ÿ0~1

private:
	std::size_t								m_Poolsize;
	std::map<int, Pthread*>					m_mThreads;
	Locker									m_locker;
};

#endif //_PTHREAD_POOL_H_
