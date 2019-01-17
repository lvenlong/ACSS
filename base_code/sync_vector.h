#ifndef SYNC_VECTOR_H_INCLUDED
#define SYNC_VECTOR_H_INCLUDED

#include <queue>
#include "mutex.h"
#include "sema.h"
#include "guard.h"
#include "LiLong_error.h"
#include "shareable.h"
#include "libs/rwlock.h"
#include "log.h"

//线程安全vector
namespace LiLong
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
                    return E_LiLong_NOMEM;
                }
            }else{
                return E_LiLong_SYSERROR;
            }

            _psem->signal();
            return 0;
        }

        //从同步vector中取元素。如果同步vector为空，将阻塞指定时长;BGCC_SEMA_WAIT_INFINITE表示无限阻塞
        int32_t get(ElemType& elem, int millisecond)
        {
            _rwlock_clear.get_rdlock();
            int32_t ret = _psem->wait(millisecond);

            if(0 == ret){
                {
                    ScopedGuard guard(&_mutex);
                    if(guard.is_locked()){
                        elem = _queue.front();
                        _queue.pop();
                    }
                    else{
                        _relock_clear.unlock();
                        return E_LiLong_SYSERROR;
                    }
                }
                _rwlock_clear.unlock();
                return 0;
            }
            else{
                _rwlock_clear.unlock();
                return ret;
            }
        }

        int32_t size()
        {
            return (int32_t)_queue.size();
        }

        //清空
        void clear()
        {
            sc_trace("vector clear");
            _rwlock_clear.get_wrlock();
            ScopedGuard guard(&_mutex);
            std::vector<ElemType> tmp;
            while(_queue.size()){
                _queue.pop();
            }
            delete _psem;
            _psem = new Semaphore();
            _rwlock_clear.unlock();
        }

    protected:
        SyncVector(const SyncVector&);
        SyncVector& operator=(const SyncVector&);
    private:
        std::vector<ElemType> _queue;
        Mutex _mutex;
        RWLock _rwlock_clear;
        Semaphore *_psem;
    };
}

#endif // SYNC_VECTOR_H_INCLUDED
