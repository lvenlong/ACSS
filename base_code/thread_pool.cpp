#include <iostream>
#include "thread_pool.h"
#include "thread_manager.h"
#include "common.h"

namespace LiLong
{
    //线程池任务类型
    class ThreadPool::ThreadPoolRunner : public Runnable
    {
    public:
        //线程池构造函数;tp 线程池
        ThreadPoolRunner(ThreadPool* tp);
        //执行体
        virtual int32_t operator()(const bool isstopped, void* param = NULL);
    private:
        ThreadPool* _tp;
    };

    ThreadPool::ThreadPoolRunner::ThreadPoolRunner(ThreadPool* tp) : _tp(tp){}

    int32_t ThreadPool::ThreadPoolRunner::operator()(const bool isstopped, void* param)
    {
        while(!(isstopped)){
            RunnableSharedPointer pr;
            if(_tp->_tasks.get(pr, THREADPOOL_GET_TASK_TIMEOUT)){
                (*pr)(isstopped,param);
            }
        }
        return 1;
    }

    ThreadPool::ThreadPool() : _state(UNINITIALIZED){}

    ThreadPool::~ThreadPool()
    {
        terminate();
    }

    int ThreadPool::init(int nThreads)
    {
        int ret = 0;
        if(UNINITIALIZED == _state){
            _state = INITALIZED;
            ret = addWorker(nThreads);
        }
        return ret;
    }

    bool ThreadPool::addTask(RunnableSharedPointer pr)
    {
        return 0 == _tasks.put(pr);
    }

    bool ThreadPool::join()
    {
        return _threadGroup.join();
    }

    bool ThreadPool::terminate()
    {
        return _threadGroup.terminateAll();
    }

    size_t ThreadPool::size()
    {
        return _threadGroup.size();
    }

    int ThreadPool::addWorker(int nWorker)
    {
        int ret = 0;
        for(int i = 0; i < nWorker; ++i){
            SharedPointer<Thread> workerThread = ThreadManager::createThread(RunnableSharedPointer(new ThreadPoolRunner(this)));
            if(workerThread.is_valid()){
                _threadGroup.addThread(workerThread);
                ++ret;
            }
        }
        return ret;
    }
}
