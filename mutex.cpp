#include "mutex.h"
#include "time_util.h"
#include <pthread.h>

namespace bigpipe{
    Mutex::Mutex(){
	int32_t ret = 0;
	pthread_mutexattr_t attr;
	ret = pthread_mutexattr_init(&attr);
	if(0 != ret){
	    ret = pthread_mutex_init(&this->_mutex, NULL);
	}else{
	    ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK_NP);
	    ret = pthread_mutex_init(&_mutex, &attr);
	    pthread_mutexattr_destroy(&attr);
	}
    }
    Mutex::~Mutex(){
	pthread_mutex_destroy(&_mutex);
    }
    int32_t Mutex::lock(uint32_t millisecond){
	int32_t ret = 0;
	if(UINT_MAX == millisecond){
	    ret = pthread_mutex_lock(&_mutex);
	}
	else{
	    struct timespec ts = {0, 0};
	    TimeUtil::get_abs_timespec(&ts, millisecond);
	    ret = pthread_mutex_timedlock(&_mutex, &ts);
	}
	if(0 != ret){
	    return false;
	}
	return 0;
    }

    int32_t Mutex::try_lock(){
	int32_t ret = 0;
	ret = pthread_mutex_trylock(&_mutex);
	return (0 == ret ? 0 : -1);
    }

    int32_t Mutex:: unlock(){
	int32_t ret = 0;
	ret = pthread_mutex_unlock(&_mutex);
	return (0 == ret ? 0 : -1);
    }
}
