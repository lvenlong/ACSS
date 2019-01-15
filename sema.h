#ifndef SEMA_H_INCLUDED
#define SEMA_H_INCLUDED

#include "common.h"

#define BIGPIPE_SEMA_WAIT_INFINITE UINT_MAX
#define bigpipe_sem_t sem_t

namespace bigpipe
{
    //实现线程间任务同步
    class Semaphore
    {
    public:
        //构造函数；ninit 信号量的初始值
        Semaphore(int32_t ninit = 0)
        //析构函数
        ~Semaphore();
        //等待信号量;millisecond 超时时长（毫秒）
        int32_t wait(uint32_t millisecond = BIGPIPE_SEMA_WAIT_INFINITE);
        bool try_wait();
        //触发信号量
        int32_t signal();
    protected:
        //禁用拷贝构造函数
        Semaphore(const Semaphore&);
        //禁用赋值运算符
        Semaphore& operator=(const Semaphore&);
    private:
        bigpipe_sem_t _sem;
    };
}

#endif // SEMA_H_INCLUDED
