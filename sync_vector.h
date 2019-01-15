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

//�̰߳�ȫvector
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

        //��ͬ��vector�����Ԫ�أ������ظ�����ͬʱ�����ź���
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

        //��ͬ��vector��ȡԪ�ء����ͬ��vectorΪ�գ�������ָ��ʱ��;BGCC_SEMA_WAIT_INFINITE��ʾ��������
        int32_t get(ElemType& elem, int millisecond)
        {
            _rwlock_clear.get_rdlock()
        }
    };
}

#endif // SYNC_VECTOR_H_INCLUDED
