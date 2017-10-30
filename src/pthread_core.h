#ifndef _PTHREAD_CORE_H_
#define _PTHREAD_CORE_H_

#include <pthread.h>
#include <iostream>

#include "atomic.h"

#define  DEFAULT_STACKSIZE (2*1024*1024)

typedef void*(*taskfuncp)(void*);

typedef struct _task_t{
	taskfuncp taskf;
	void* taskpara;
}task_t;

class Pthread {

public:

	enum thrstu {UNINIT, WORKING, SUSPENDED, IDLE, ABORT};
	//the most ordinary sys default stack size = 2M
	Pthread(size_t stacksize = DEFAULT_STACKSIZE);
	~Pthread();
	void run(const task_t& task);
	void reset();
	void cancel();

	void setName(const std::string& name) { m_name = name; }
	std::string getName() { return m_name; }

private:

	std::string		m_name;
	pthread_attr_t	m_attr;
	size_t			m_stacksize;
	void *			mp_stackadd;
	atomic_t		m_thrstu;
	
	pthread_t		m_thread;
};








#endif //_PTHREAD_CORE_H_