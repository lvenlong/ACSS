#include "thread_group.h"

namespace LiLong
{
    ThreadGroup::ThreadGroup(){}
    ThreadGroup::~ThreadGroup(){}

    bool ThreadGroup::addThread(SharedPointer<Thread> thread)
    {
        try
        {
            _threads.push_back(thread);
        }
        catch(std::bad_alloc&)
        {
            return false;
        }
        return true;
    }

    bool ThreadGroup::join()
    {
        citr_type citr;
        for(citr = _threads.begin(); citr != _threads.end(); ++citr){
            (*citr)->join();
        }
        _threads.clear();
        return true;
    }

    size_t ThreadGroup::size()
    {
        return _threads.size();
    }

    bool ThreadGroup::terminateAll()
    {
        citr_type citr;
        for(citr = _threads.begin(); citr != _threads.end(); ++citr){
            (*citr)->stop();
        }
        return true;
    }
}
