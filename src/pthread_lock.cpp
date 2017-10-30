#include "pthread_lock.h"

#define ACCESS_ONCE(x) (*(volatile typeof(x) *)&(x))


void *reader_thread(void *arg)
{
	int i;
	int newx, oldx;
	newx = oldx = -1;

	pthread_rwlock_t *p = (pthread_rwlock_t *)arg;

	if (pthread_rwlock_rdlock(p) != 0) {
		perror("reader_thread: pthread_rwlock_rdlock error");
		exit(__LINE__);
	}

	for (i = 0; i < 100; i++) {
		newx = ACCESS_ONCE(x);
		if (newx != oldx) {
			printf("reader_lock: x: %d\n", x);
		}
		oldx = newx;
		poll(NULL, 0, 1);
	}

	if (pthread_rwlock_unlock(p) != 0) {
		perror("reader thread: pthred_rwlock_unlock error");
		exit(__LINE__);
	}

	return NULL;
}

void *writer_thread(void *arg)
{
	int i;
	pthread_rwlock_t *p = (pthread_rwlock_t *)arg;

	if (pthread_rwlock_wrlock(p) != 0) {
		perror("writer thread: pthread_rwlock_wrlock error");
		exit(__LINE__);
	}

	for (i = 0; i < 3; i++) {
		ACCESS_ONCE(x)++;
		poll(NULL, 0, 5);
	}

	if (pthread_rwlock_unlock(p) != 0) {
		perror("writer thread: pthread_rwlock_unlock error");
		exit(__LINE__);
	}

	return NULL;
}

int main(void)
{
	pthread_t tid1, tid2;
	void *vp;
	if (pthread_create(&tid1, NULL, reader_thread, &lock_rw) != 0) {
		perror("pthread_create error");
		exit(__LINE__);
	}

	if (pthread_create(&tid2, NULL, writer_thread, &lock_rw) != 0) {
		perror("pthread_create error");
		exit(__LINE__);
	}

	//wait for the thread to complete
	if (pthread_join(tid1, &vp) != 0) {
		perror("pthread_join error");
		exit(__LINE__);
	}

	if (pthread_join(tid2, &vp) != 0) {
		perror("pthread_join error");
		exit(__LINE__);
	}

	printf("Parent process sees x: %d\n", x);
	return 0;
}


