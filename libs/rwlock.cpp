#include <stdlib.h>
#include <stdio.h>
#include "rwlock.h"

namespace bigpipe
{
    //构造函数
    RWLock::RWLock()
    {
        pthread_rwlock_init(&_rwlock, NULL);
    }

    //析构函数
    RWLock::~RWLock()
    {
        pthread_rwlock_unlock(&_rwlock);
    }

    //获取读锁
    int32_t RWLock::get_rdlock()
    {
        return pthread_rwlock_rdlock(&_rwlock);
    }

    //获取写锁
    int32_t RWLock::get_wlock()
    {
        return pthread_rwlock_wrlock(&_rwlock);
    }

    //尝试获取读锁
    int32_t RWLock::try_rdlock()
    {
        return pthread_rwlock_trywrlock(&_rwlock);
    }

    //尝试获取读锁
    int32_t RWLock::try_wlock()
    {
        return pthread_rwlock_tryrdlock(&_rwlock);
    }

    int32_t RWLock::unlock()
    {
        return pthread_rwlock_unlock(&_rwlock);
    }
}
