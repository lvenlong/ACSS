#ifndef THREAD_GROUP_H_INCLUDED
#define THREAD_GROUP_H_INCLUDED

#include <vector>
#include "Thread.h"
#include "shared_pointer.h"

namespace LiLong
{
    //ThreadGroup是Thread的集合，方便管理一组相关线程
    class ThreadGroup
    {
    public:
        ThreadGroup();
        ~ThreadGroup();
        //添加新线程
        bool addThread(SharedPointer<Thread> thread);
        //等待线程组中的所有线程执行结束
        bool join();
        //获取线程组中的线程个数
        size_t size();
        //终止线程组中的所有线程的执行
        bool terminateAll();
    private:
        ThreadGroup(const ThreadGroup&);
        ThreadGroup& operator=(const ThreadGroup&);

        std::vector<SharedPointer<Thread>> _threads;
        typedef std::vector<SharedPointer<Thread>>::const_iterator citr_type;
    };
}

#endif // THREAD_GROUP_H_INCLUDED
