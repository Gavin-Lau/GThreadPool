#include "pthreadpool.h"
#include "pthread_core.h"
#include "pthread_sync.h"

#include <assert.h>

using std::cout;
using std::endl;


PthreadPool::PthreadPool(std::size_t poolsize)
	: m_Poolsize(poolsize)
{
	for (int i = 0; i < m_Poolsize ; ++i)
	{
		Pthread* curThread = new Pthread();
		curThread->setID(i);
		m_mThreads.insert(std::make_pair(i, curThread));
		assert(curThread->getStatus() == Pthread::IDLE);
	}
}

PthreadPool::~PthreadPool()
{

}

void PthreadPool::PostTask()
{

}

float PthreadPool::GetLoad()
{

}