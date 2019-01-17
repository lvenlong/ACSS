#include <iostream>
#include <sys/stat.h>

#include "file_util.h"

#include <unistd.h>
#include <errno.h>

#define MKDIR(a) mkdir((a), 0755)

namespace LiLong
{
    int32_t FileUtil::close_r(int32_t fd)
    {
        int32_t ret;

        do
        {
            ret = close(fd);
        }while(-1 == ret && EINTR == errno);
        return ret;
    }

    int32_t FileUtil::create_directories(const char* path)
    {
        int i = 0;
        int ret;
        int len;
        char* path_copy;

        if(NULL == path)
        {
            return 0;
        }

        path_copy = strdup(path);
        len = strlen(path_copy);

        for(i = 0; i < len; i++)
        {
            if('\\' == path_copy[i] || '/' == path_copy[i])
            {
                path_copy[i] = '\0';

                ret = access(path_copy, 0);
                if(ret != 0)
                {
                    ret = MKDIR(path_copy);
                    if( 0 != ret)
                    {
                        return -1;
                    }
                }

                path_copy[i] = '/';
            }
        }

        ret = access(path_copy, 0);
        if(0 != ret)
            ret = MKDIR(path_copy);

        free(path_copy);
        return ret;
    }

    const char FileUtil::SEP = '/';
}
