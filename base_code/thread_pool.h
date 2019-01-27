#ifndef THREAD_POOL_H_INCLUDED
#define THREAD_POOL_H_INCLUDED

#include "runnable.h"
#include "sync_vector.h"
#include "thread_group.h"
#include "shareable.h"

namespace LiLong
{
    //线程池维护一组预先创建好的线程及一个任务队列。线程依次执行任务队列中的任务。
    class ThreadPool : public Shareable
    {
    private:
        class ThreadPoolRunner;
    public:
        //线程池状态
        enum state_t
        {
            UNINITIALIZED,
            INITALIZED
        };

        //构造函数
        ThreadPool();
        //析构函数
        ~ThreadPool();

        /** 线程池中默认线程个数 */
        static const int DEFAULT_THREADS_NUM = 10;

        //初始化线程池，创建规定个数的线程;nThreads 创建线程的个数
        int init(int nThreads = DEFAULT_THREADS_NUM);

        //向任务队列中添加任务;pr 待添加的任务
        bool addTask(RunnableSharedPointer pr);

        //等待所有线程执行完毕。请不要调用此方法，线程池中的线程永远不会自动执行结束
        bool join();

        //获取线程个数
        size_t size();

        //终止所有线程的执行
        bool terminate();

    private:
        //向线程池中添加nWorker个线程
        int addWorker(int nWorker);
        friend class ThreadPoolRunner;
        /* 添加到线程池中的任务 */
        SyncVector<RunnableSharedPointer> _tasks;
        /* 线程组 */
        ThreadGroup _threadGroup;
        state_t _state;
    };
}

#endif // THREAD_POOL_H_INCLUDED
