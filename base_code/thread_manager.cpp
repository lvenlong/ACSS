#include "thread_manager.h"

namespace LiLong
{
    SharedPointer<Thread> ThreadManager::createThread(SharedPointer<Runnable> pr)
    {
        SharedPointer<Thread> t(new Thread(pr));
        bool b0k = t->start();
        return b0k ? t : SharedPointer<Thread>(NULL);
    }
}
