#ifndef _PTHREAD_POOL_H_
#define _PTHREAD_POOL_H_

#include <iostream>
#include <map>
#include <ctime>
#include "pthread_core.h"

typedef time_t oper_time;

#define DYNAMIC_UP_LIMIT (0.8)
#define DYNAMIC_DOWN_LIMIT (0.2)
#define DYNAMIC_INCREASE_RATIO (0.2)

class Monitor;

class PthreadPool {
	friend class Monitor;
public:
	enum sizepolicy {STATIC , DYNAMIC};
	PthreadPool(std::size_t poolsize, sizepolicy policy = PthreadPool::STATIC);
	~PthreadPool();

private:

	sizepolicy								m_policy;
	std::size_t								m_poolsize_default;
	volatile std::size_t					m_poolsize_dynamic;
	volatile std::size_t					m_idlenum;
	std::map<Pthread*, oper_time>			m_mltime;
	std::map<Pthread*, Pthread::thrstu>		m_msta;
	struct timeval							m_momitorloop;
};

#endif //_PTHREAD_POOL_H_