#include <stdlib.h>
#include <stdio.h>
#include "rwlock.h"

namespace bigpipe
{
    //���캯��
    RWLock::RWLock()
    {
        pthread_rwlock_init(&_rwlock, NULL);
    }

    //��������
    RWLock::~RWLock()
    {
        pthread_rwlock_unlock(&_rwlock);
    }

    //��ȡ����
    int32_t RWLock::get_rdlock()
    {
        return pthread_rwlock_rdlock(&_rwlock);
    }

    //��ȡд��
    int32_t RWLock::get_wlock()
    {
        return pthread_rwlock_wrlock(&_rwlock);
    }

    //���Ի�ȡ����
    int32_t RWLock::try_rdlock()
    {
        return pthread_rwlock_trywrlock(&_rwlock);
    }

    //���Ի�ȡ����
    int32_t RWLock::try_wlock()
    {
        return pthread_rwlock_tryrdlock(&_rwlock);
    }

    int32_t RWLock::unlock()
    {
        return pthread_rwlock_unlock(&_rwlock);
    }
}
