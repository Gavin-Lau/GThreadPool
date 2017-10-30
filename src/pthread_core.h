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
	int*  taskRet;
	Pthread* handle;
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

	void setID(const int& id) { m_ID = id; }
	int getName() { return m_ID; }
	int getStatus() { return m_thrstu; }

	static void threadFunc();
private:

	int				m_ID;
	pthread_attr_t	m_attr;
	size_t			m_stacksize;
	void *			mp_stackadd;
	atomic_t		m_thrstu;
	
	pthread_t		m_thread;
};








#endif //_PTHREAD_CORE_H_