#ifndef RWLOCK_H_INCLUDED
#define RWLOCK_H_INCLUDED

#include "../base_code/common.h"

namespace LiLong
{
    class RWLock
    {
    public:
        //构造函数
        RWLock();
        //析构函数
        ~RWLock();
        //获取读锁
        int32_t get_rdlock();
        //尝试获取写锁
        int32_t try_rdlock();
        //获取写锁
        int32_t get_wlock();
        //尝试获取写锁
        int32_t try_wlock();
        //解锁
        int32_t unlock();
    private:
        pthread_rwlock_t _rwlock;
    };
}

#endif // RWLOCK_H_INCLUDED
