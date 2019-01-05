#include "thread_util.h"

namespace bigpipe
{
    int64_t ThreadUtil::self_id()
    {
        return (int64_t)syscall(__NR_getid);
    }
}
