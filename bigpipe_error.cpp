#include "bigpipe_error.h"

namespace bigepipe
{
    char* bigpipe_strerror_r(int32_t errcode, char* buffer, int32_t buflen)
    {
        if(NULL == buffer || -1 == buflen)
            return NULL;
        return strerror_r(errcode, buffer, buflen);
    }
}
