#ifndef THREAD_MANAGER_H_INCLUDED
#define THREAD_MANAGER_H_INCLUDED

#include "thread.h"
#include "shared_pointer.h"
#include "runnable.h"

namespace LiLong
{
    //用于创建新的线程
    class ThreadManager
    {
    public:
        //创建新的线程;pr 线程执行的任务
        static SharedPointer<Thread> createThread(SharedPointer<Runnable> pr);

    private:
        ThreadManager(const ThreadManager&);
        ThreadManager& operator=(const ThreadManager&);
    };
}

#endif // THREAD_MANAGER_H_INCLUDED
