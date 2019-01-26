#ifndef RUNNABLE_H_INCLUDED
#define RUNNABLE_H_INCLUDED

#include "common.h"
#include "shareable.h"

namespace LiLong
{
    class Runnable : public Shareable
    {
    public:
        virtual int32_t operator()(const bool isstopped, void* param = NULL) = 0;
        virtual ~Runnable() { }
    };
}


#endif // RUNNABLE_H_INCLUDED
