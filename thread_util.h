#ifndef THREAD_UTIL_H_INCLUDED
#define THREAD_UTIL_H_INCLUDED
#include "common.h"

namespace bigpipe
{
    class ThreadUtil
    {
    public:
        static int64_t self_id();
    };
}


#endif // THREAD_UTIL_H_INCLUDED
