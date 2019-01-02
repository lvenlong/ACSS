# ifndef MUTEX_H_
# define MUTEX_H_

#include "common.h"
#include <pthread.h>

namespace bigpipe{
    class Mutex{
    public:
	Mutex();
	~Mutex();
	int32_t lock(uint32_t millisecond = UINT_MAX);
	int32_t try_lock();
	int32_t unlock();

    protected:
	Mutex(const Mutex&);
	Mutex& operator=(const Mutex&);

    private:
	pthread_mutex_t _mutex;
    };
}
#endif
