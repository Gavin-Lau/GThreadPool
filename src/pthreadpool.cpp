#include "pthreadpool.h"
#include "timer.h"

using std::cout;
using std::endl;


class Monitor
{

public:

	Monitor(PthreadPool& pthpool)
		: m_pthpool(pthpool)
	{
		m_timer = new pTimer(&pthpool.m_momitorloop , pTimer::loop);


		m_timetask.taskf = Monitor::monitordo;
		m_timetask.taskpara = (void*)&m_pthpool;
		m_timer->run(m_timetask);
	}

	~Monitor()
	{
		delete m_timer;
	}

	/**
	 * ��Ҫ��3����:
	 * 1.��ʧЧ���߳�����
	 * 2.��⵱ǰ���е��߳���Ŀ�ǲ��� > �ܵ��߳��� * 80%
	 *	������������ܵ��߳���
	 *	��⵱ǰ�����߳���Ŀ���ǲ��� < ���߳��� * 20% 
	 *  �����������߳���Ŀ����ʼ��Ŀ 
	 */
	static void* monitordo(void *para)
	{
		PthreadPool	*pthpool = (PthreadPool*)para;
		int thnum = pthpool->m_msta.size();
		for (std::map<Pthread*,Pthread::thrstu>::iterator itr 
			= pthpool->m_msta.begin();  itr != pthpool->m_msta.end(); ++itr)
		{
			if (Pthread::ABORT == itr->second)
			{
				itr->first->reset();
			}
			if (Pthread::IDLE == itr->second) pthpool->m_idlenum++;
		}

		if (PthreadPool::DYNAMIC == pthpool->m_policy &&
				pthpool->m_idlenum > pthpool->m_poolsize_dynamic * DYNAMIC_UP_LIMIT)
		{
			pthpool->m_poolsize_dynamic *= (1 + DYNAMIC_INCREASE_RATIO);
			pthpool->resize();
		}

		if (PthreadPool::DYNAMIC == pthpool->m_policy &&
			pthpool->m_idlenum < pthpool->m_poolsize_dynamic * DYNAMIC_DOWN_LIMIT)
		{
			pthpool->m_poolsize_dynamic *= (1 - DYNAMIC_INCREASE_RATIO);
			pthpool->resize();
		}

	}
	
private:

	PthreadPool&	m_pthpool;
	pTimer*			m_timer;
	task_t			m_timetask;
};
