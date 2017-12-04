#include "pthread_core.h"

#include <cstdio>
#include <cstdlib>

Pthread::Pthread(size_t stacksize)
	: m_stacksize(stacksize)
{
	pthread_attr_init(&m_attr);
	size_t defaultsize = 0;
	pthread_attr_setstacksize(&m_attr, m_stacksize);
	m_pstackadd = (void*)malloc(m_stacksize);
	if (NULL == m_pstackadd)
		ATOMIC_ASSIGN(m_thrstu, UNINIT);
	else
	{
		pthread_attr_setstackaddr(&m_attr, m_pstackadd);
	}

	ATOMIC_ASSIGN(m_thrstu, WORKING);

	if (pthread_create(&m_thread, &m_attr, Pthread::threadFunc, ))
	{
		ATOMIC_ASSIGN(m_thrstu, IDLE);
		return;
	}
}

Pthread::~Pthread()
{
	pthread_attr_destroy(&m_attr);
	free(m_pstackadd);
	m_pstackadd = NULL;
}



//reset the thread while it's in not working status
void Pthread::reset()
{
	switch (m_thrstu)
	{
		case UNINIT:
			pthread_attr_setstacksize(&m_attr, m_stacksize);
			m_pstackadd = (void*)malloc(m_stacksize);
			if (NULL == m_pstackadd)
				ATOMIC_ASSIGN(m_thrstu, UNINIT);
			else
				pthread_attr_setstackaddr(&m_attr, m_pstackadd);
			break;

		case ABORT:
			cancel();
			break;
	}
}

void Pthread::cancel()
{
	if ( pthread_cancel(m_thread))
	{
		ATOMIC_ASSIGN(m_thrstu, IDLE);
	} else {
		ATOMIC_ASSIGN(m_thrstu, ABORT);
	}
}

void* Pthread::threadFunc(void* para)
{
	Pthread* handle = (Pthread*)para;
	while (handle->m_switchor)
	{

	}
}
