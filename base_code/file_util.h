#ifndef FILE_UTIL_INCLUDED
#define FILE_UTIL_INCLUDED

#include "common.h"

namespace LiLong
{
    class FileUtil
    {
    public:
        //确保close在遇到中断信号后继续被调用
        static int32_t close_r(int32_t fd);

        //创建级联目录
        static int32_t create_directories(const char* path);

        //路径分隔符
        static const char SEP;
    };
}


#endif // FILE_UTIL_INCLUDED
