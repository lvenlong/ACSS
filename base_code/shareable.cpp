#include "guard.h"
#include "shareable.h"

namespace LiLong
{
    typedef Guard<Mutex> ScopedGuard;

    Shareable::Shareable() : _count(0){}

    void Shareable::inc()
    {
        ScopedGuard guard(&_mutex);
        ++_count;
    }

    int32_t Shareable::dec()
    {
        ScopedGuard guard(&_mutex);
        if(_count > 0)
            --_count;
        return _count;
    }

    int32_t Shareable::get_count()
    {
        ScopedGuard guard(&_mutex);
        return _count;
    }
}
