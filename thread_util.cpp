#include "thread_util.h"
#include <sys/syscall.h>
 #include <unistd.h>

namespace bigpipe
{
    int64_t ThreadUtil::self_id()
    {
        return (int64_t)syscall(__NR_gettid);
    }
}
