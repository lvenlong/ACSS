#ifndef SHAREABLE_H_INCLUDED
#define SHAREABLE_H_INCLUDED

#include "mutex.h"

namespace bigpipe
{
    //提供具有原子增减的通用计数器功能，可被多个智能指针对象共享
    class Shareable
    {
    public:
        //析构函数
        ~Shareable(){};
        //增加引用计数
        void inc();
        //减少引用计数
        int32_t dec();
        //获取当前引用计数
        int32_t get_count();
    protected:
        //禁用显式构造，仅可通过子类构造
        Shareable();
    private:
        int32_t _count;
        Mutex _mutex;
    private:
        //禁用拷贝构造功能
        Shareable(const Shareable&);
        //禁用赋值运算符
        Shareable& operator=(const Shareable&);
    };
}


#endif // SHAREABLE_H_INCLUDED
