#ifndef SYNC_VECTOR_H_INCLUDED
#define SYNC_VECTOR_H_INCLUDED

#include <queue>
#include "mutex.h"
#include "sema.h"
#include "guard.h"
#include "bigpipe_error.h"
#include "shareable.h"
#include "libs/rwlock.h"
#include "log.h"

//线程安全vector
namespace bigpipe
{
    template<typename ElemType>
    class SyncVector : public Shareable
    {
        SyncVector()
        {
            _psem = new Semaphore();
        }

        ~SyncVector()
        {
            if(_psem != NULL)
                delete _psem;
        }

        typedef Guard<Mutex> ScopedGuard;

        //向同步vector中添加元素（允许重复）。同时触发信号量
        int32_t put(ElemType elem)
        {
            ScopedGuard guard(&_mutex);
            if(guard.is_locked()){
                try
                {
                    _queue.push(elem);
                }
                catch(std::bad_alloc &)
                {
                    return E_BIGPIPE_NOMEM;
                }
            }else{
                return E_BIGPIPE_SYSERROR;
            }

            _psem->signal();
            return 0;
        }

        //从同步vector中取元素。如果同步vector为空，将阻塞指定时长;BGCC_SEMA_WAIT_INFINITE表示无限阻塞
        int32_t get(ElemType& elem, int millisecond)
        {
            _rwlock_clear.get_rdlock()
        }
    };
}

#endif // SYNC_VECTOR_H_INCLUDED
