#include "Thread.h"
#include "time_util.h"

namespace LiLong
{
    Thread::Thread(const RunnableSP& runner, bool detached) : _use_functor(true), _functor(runner), _func_ptr(NULL), _func_arg(NULL), _detached(detached), _state(INIT), _isstopped(false)
    {    }

    Thread::Thread(run_func_t func, void* arg, bool detached) : _use_functor(false), _func_ptr(func), _func_arg(arg), _detached(detached), _state(INIT), _isstopped(false)
    {    }

    Thread::~Thread()
    {
        join();
        _state = STOP;
    }

    bool Thread::start()
    {
        if(INIT != _state){
            return false;
        }
        int ret;
        pthread_attr_t attr;
        ret = pthread_attr_init(&attr);
        if(0 != ret){
            return false;
        }

        ret = pthread_attr_setdetachstate(&attr, _detached ? PTHREAD_CANCELED : PTHREAD_CREATE_JOINABLE);
        if(0 != ret){
            pthread_attr_destroy(&attr);
            return false;
        }

        ret = pthread_create(&_thread, &attr, thread_start_func, (void*)this);
        if(0 == ret){
            _sema.wait();
        }

        ret = pthread_attr_destroy(&attr);
        if(0 != ret){
            return false;
        }

        _isstopped = false;
        _state = START;
        return true;
    }

    bool Thread::join()
    {
        if(START != _state && STOP != _state){
            return false;
        }
        bool ret = false;
        if(!pthread_equal(pthread_self(), _thread)){
            if(!_detached){
                int r = pthread_join(_thread, NULL);
                if(0 == r){
                    _state = JOINED;
                }
                ret = (0 == r);
            }
        }
        else{
            ret = false;
        }
        return ret;
    }

    bool Thread::stop()
    {
        bool ret = false;
        if (_state != STOP && _state >= START)
        {
            _isstopped = true;
            _state = STOP;
            ret = true;
        }
        return ret;
    }

    pthread_t Thread::get_thread_id() const {
        return _thread;
    }

    void* Thread::thread_start_func(void *arg) {
        Thread* me = (Thread*)arg;
        RunnableSharedPointer runner = me->_functor;
        bool use_functor = me->_use_functor;
        run_func_t func = me->_func_ptr;
        void* func_arg = me->_func_arg;
        me->_sema.signal();

        if (use_functor) {
                if (runner.is_valid()) {
                (*runner)(&me->_isstopped);
            }
        }
        else {
            if (func) {
                func(&me->_isstopped, func_arg);
            }
        }
        return NULL;
    }
}
