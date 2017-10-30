#ifndef _PTHREAD_LOCK_H_
#define _PTHREAD_LOCK_H_

#include <pthread.h>
#include <assert.h>
#include "atomic.h"

class Locker {

public:

	Locker()
	{
		ATOMIC_ASSIGN(errNo, pthread_rwlock_init(RWlock, NULL));
	}

	~Locker() 
	{ 
		assert(count == 0);
		pthread_rwlock_destroy(RWlock);
	}

	int writeLock()
	{
		ATOMIC_INC(count);
		if (errNo == 0)
		{
			ATOMIC_ASSIGN(errNo, pthread_rwlock_init(RWlock, NULL));
			return errNo;
		}
		else
			return errNo;
	}

	int readLock()
	{
		ATOMIC_INC(count);
		if (errNo == 0)
			ATOMIC_ASSIGN(errNo, pthread_rwlock_rdlock(RWlock));
		else
			return errNo;
	}

	int lock() { return writeLock(); }

	int unlock()
	{
		ATOMIC_DEC(count);
		if (errNo == 0)
			ATOMIC_ASSIGN(errNo, pthread_rwlock_unlock(RWlock));
		else
			return errNo;
	}

private:

	pthread_rwlock_t* RWlock;
	atomic_t		errNo;
	atomic_t		count;

};

#endif //_PTHREAD_LOCK_H_
