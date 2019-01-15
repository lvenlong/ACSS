#ifndef BIGPIPE_ERROR_H_INCLUDED
#define BIGPIPE_ERROR_H_INCLUDED

#include "common.h"

#define BigpipeGetLastError() errno
#define BigpipeSockGetLastError() errno

namespace bigpipe
{
    enum{
        S_BIGPIPE_SUCESS,
        E_BIGPIPE_NULL_POINTER = -10000,
        E_BIGPIPE_CONF_ERROR,
        E_BIGPIPE_NOMEM,
        E_BIGPIPE_INVALID_PARAM,
        E_BIGPIPE_SYSERROR,
        E_BIGPIPE_TIMEOUT,
        E_BIGPIPE_SERVER_ALREADY_INIT,
        E_BIGPIPE_SERVER_NEED_INIT,
        E_BIGPIPE_SERVER_CRATER_LISTENFD_FAILED,
        E_BIGPIPE_SERVICE_NOT_FOUND,
        E_BIGPIPE_OUT_MAY_TRY_COUNT
    };

    char* bigpipe_strerror_r(int32_t errcode, char* buffer = NULL, int32_t buflen = -1);
}


#endif // BIGPIPE_ERROR_H_INCLUDED
