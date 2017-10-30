#include "pthread_core.h"

#include <cstdio>
#include <cstdlib>

Pthread::Pthread(size_t stacksize)
	: m_stacksize(stacksize)
{
	pthread_attr_init(&m_attr);
	size_t defaultsize = 0;
	pthread_attr_setstacksize(&m_attr, m_stacksize);
	mp_stackadd = (void*)malloc(m_stacksize);
	if (NULL == mp_stackadd)
		ATOMIC_ASSIGN(m_thrstu, UNINIT);
	else
	{
		pthread_attr_setstackaddr(&m_attr, mp_stackadd);
	}

	ATOMIC_ASSIGN(m_thrstu, WORKING);

	if (pthread_create(&m_thread, &m_attr, , ))
	{
		ATOMIC_ASSIGN(m_thrstu, IDLE);
		return;
	}
}

Pthread::~Pthread()
{
	pthread_attr_destroy(&m_attr);
	free(mp_stackadd);
	mp_stackadd = NULL;
}

void Pthread::run(const task_t& task)
{
}

	ATOMIC_ASSIGN(m_thrstu, IDLE);
}

//reset the thread while it's in not working status
void Pthread::reset()
{
	switch (m_thrstu)
	{
		case UNINIT:
			pthread_attr_setstacksize(&m_attr, m_stacksize);
			mp_stackadd = (void*)malloc(m_stacksize);
			if (NULL == mp_stackadd)
				ATOMIC_ASSIGN(m_thrstu, UNINIT);
			else
				pthread_attr_setstackaddr(&m_attr, mp_stackadd);
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

void Pthread::threadFunc()
{
	while
}

