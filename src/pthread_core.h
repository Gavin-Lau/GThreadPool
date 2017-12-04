#ifndef _PTHREAD_CORE_H_
#define _PTHREAD_CORE_H_

#include <pthread.h>
#include <iostream>

#include "atomic.h"
#include "pthread_sync.h"

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
	void reset();
	void cancel();

	void setID(const int& id) { m_ID = id; }
	int getName() { return m_ID; }
	int getStatus() { return m_thrstu; }

	static void* threadFunc(void* para);
private:

	int				m_ID;
	pthread_attr_t	m_attr;
	size_t			m_stacksize;
	void *			m_pstackadd;
	atomic_t		m_thrstu;
	int				m_switchor; //线程开关
	
	pthread_t		m_thread;
	Syncer			m_sync;
};








#endif //_PTHREAD_CORE_H_