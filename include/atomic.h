#ifndef _ATOMIC_H_
#define _ATOMIC_H_

typedef volatile long atomic_t;
typedef volatile long long atomic64_t;

#ifdef _MSC_VER

# include <windows.h>

# define ATOMIC_INC(var) 		InterlockedIncrement(&var)
# define ATOMIC_DEC(var) 		InterlockedDecrement(&var)
# define ATOMIC_ASSIGN(tar,val) InterlockedExchange(&tar,val)
# define ATOMIC_ADD(tar,val)	InterlockedExchangeAdd(&tar,val)
# define ATOMIC_SUB(tar,val)	InterlockedExchangeAdd(&tar,(-val))

  
# define ATOMIC64_INC(var)			InterlockedIncrement64(&var)
# define ATOMIC64_DEC(var) 			InterlockedDecrement64(&var)
# define ATOMIC64_ASSIGN(tar,val)	InterlockedExchange64(&tar,val)
# define ATOMIC64_ADD(tar,val)		InterlockedExchangeAdd64(&tar,val)
# define ATOMIC64_SUB(tar,val)		InterlockedExchangeAdd64(&tar,(-val))	

#elif defined(__GNUC__)

# define ATOMIC_INC(var) 		__sync_add_and_fetch (&var, 1)
# define ATOMIC_DEC(var) 		__sync_sub_and_fetch(&var,-1)
# define ATOMIC_ASSIGN(tar,val) __sync_lock_test_and_set(&tar,val)
# define ATOMIC_ADD(tar,val)	__sync_add_and_fetch (&tar, val)
# define ATOMIC_SUB(tar,val)	__sync_sub_and_fetch(&tar,val)

  
# define ATOMIC64_INC(var)			__sync_add_and_fetch (&var, 1)
# define ATOMIC64_DEC(var) 			__sync_sub_and_fetch(&var,-1)
# define ATOMIC64_ASSIGN(tar,val)	__sync_lock_test_and_set(&tar,val)
# define ATOMIC64_ADD(tar,val)		__sync_add_and_fetch (&tar, val)
# define ATOMIC64_SUB(tar,val)		__sync_sub_and_fetch(&tar,val)

#else
# error current platform isn't supported
#endif

#endif //_ATOMIC_H_
