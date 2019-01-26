#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include "shareable.h"
#include "runnable.h"
#include "shared_pointer.h"
#include "sema.h"

namespace LiLong
{
    typedef void* (*run_func_t)(const bool*, void*);
    typedef SharedPointer<Runnable> RunnableSharedPointer;
    typedef SharedPointer<Runnable> RunnableSP;
    //操作系统线程模型的抽象，负责线程的创建、执行、等待、休眠以及销毁
    class Thread : public Shareable
    {
    private:
        enum state_t
        {
            INIT,
            START,
            JOINED,
            STOP
        };
    public:
        //构造函数;runner 线程执行的任务;detached 是否分离
        Thread(const RunnableSP& runner, bool detached = false);
        //构造函数;func 线程执行的任务;detached 是否分离
        Thread(run_func_t func, void* arg = NULL, bool detached = false);
        //析构函数
        ~Thread();
        //启动线程的执行
        bool start();
        //等待线程执行结束
        bool join();
        //终止线程的执行
        bool stop();
        //返回线程ID，仅在Linux下使用
        pthread_t get_thread_id() const;
    private:
        bool setDetached();
        static void* thread_start_func(void* arg);
    private:
        bool _use_functor;
        RunnableSP _functor;
        run_func_t _func_ptr;
        void * _func_arg;
        Semaphore _sema;
        volatile bool _detached;
        state_t _state;
    public:
        bool _isstopped;
        pthread_t _thread;
    };
}


#endif // THREAD_H_INCLUDED
