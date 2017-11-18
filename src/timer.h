#ifndef _TIMER_H_
#define _TIMER_H_
#include <cstdio>
#include <ctime>

#ifdef _WIN32
# include <windows.h>
#else
# include <sys/select.h>
# include <sys/time.h>
#endif

inline void msleep(long msec)
{
#ifdef _WIN32
	Sleep(msec);
#else
	select(0, NULL, NULL, NULL, msec);
#endif
}

class pTimer{

public:

	enum workmode { ONCE = 0, LOOP};

	pTimer(long delay_, long intev_, workmode mode_ = LOOP) :
		mode(mode),
		delay(delay_),
		inteval(intev_)
	{ }

	~pTimer() {}

	void run(const task_t& task)
	{
		msleep(delay);
		do
		{
			msleep(inteval);
			task.taskf(task.taskpara);
		} while (mode);
	}

private:
	
	int			mode;
	long		delay;
	long		inteval;

};

#endif //_TIMER_H_
