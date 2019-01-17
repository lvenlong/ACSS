#include <errno.h>

#include "sema.h"
#include "time_util.h"
#include "LiLong_error.h"

namespace LiLong
{
    Semaphore::Semaphore(int nint)
    {
        if(nint < 0)
            nint = 0;
        sem_init(&_sem, 0, nint);
    }

    Semaphore::~Semaphore()
    {
        sem_destroy(&_sem);
    }

    int32_t Semaphore::wait(uint32_t millisecond)
    {
        int32_t ret = 0;
        if(LiLong_SEMA_WAIT_INFINITE == millisecond){
            while((ret = sem_wait(&_sem)) == -1 && EINTR == errno);
        }
        else{
            struct timespec ts = {0, 0};
            TimeUtil::get_abs_timespec(&ts, millisecond);
            while((ret = sem_timedwait(&_sem, &ts)) == -1 && EINTR == errno);
        }

        if(0 != ret)
        {
            if(LiLongGetLastError() == ETIMEDOUT){
                return E_LiLong_TIMEOUT;
            }
            else{
                return E_LiLong_SYSERROR;
            }
        }
        return 0;
    }

    bool Semaphore::try_wait()
    {
        int32_t ret = 0;
        while((ret = sem_trywait(&_sem)) == -1 && EINTR == errno);
        return (0 == ret);
    }

    int32_t Semaphore::signal()
    {
        int32_t ret = 0;
        while((ret = sem_post(&_sem)) == -1 && EINTR == errno);
        return (0 == ret ? 0 : E_LiLong_SYSERROR);
    }
}
