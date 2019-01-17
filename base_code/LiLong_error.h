#ifndef LiLong_ERROR_H_INCLUDED
#define LiLong_ERROR_H_INCLUDED

#include "common.h"

#define LiLongGetLastError() errno
#define LiLongSockGetLastError() errno

namespace LiLong
{
    enum{
        S_LiLong_SUCESS,
        E_LiLong_NULL_POINTER = -10000,
        E_LiLong_CONF_ERROR,
        E_LiLong_NOMEM,
        E_LiLong_INVALID_PARAM,
        E_LiLong_SYSERROR,
        E_LiLong_TIMEOUT,
        E_LiLong_SERVER_ALREADY_INIT,
        E_LiLong_SERVER_NEED_INIT,
        E_LiLong_SERVER_CRATER_LISTENFD_FAILED,
        E_LiLong_SERVICE_NOT_FOUND,
        E_LiLong_OUT_MAY_TRY_COUNT
    };

    char* LiLong_strerror_r(int32_t errcode, char* buffer = NULL, int32_t buflen = -1);
}


#endif // LiLong_ERROR_H_INCLUDED
