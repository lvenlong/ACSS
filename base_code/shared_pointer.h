#ifndef SHARED_POINTER_H_INCLUDED
#define SHARED_POINTER_H_INCLUDED

#include "common.h"

namespace LiLong
{
template <typename ElementType>
class SharedPointer
{
public:
    //构造函数;ptr 资源指针
    explicit SharedPointer(ElementType* ptr = NULL) : _pointer(ptr)
    {
        if(NULL != _pointer)
        {
            _pointer->inc();
        }
    }

    //拷贝构造函数;other SharedPointer引用
    SharedPointer(const SharedPointer &other) : _pointer(other._pointer)
    {
        if(NULL != _pointer)
        {
            _pointer->inc();
        }
    }

    //拷贝构造函数;U为SharedPointer子类型;other持有ElementType派生类的指针
    template<typename U>
    SharedPointer(const SharedPointer<U> &other) : _pointer(NULL)
    {
        _pointer = other.get();
        if(NULL != _pointer)
        {
            _pointer->inc();
        }
    }

    //构造函数，如果引用计数减为0，则释放资源
    ~SharedPointer()
    {
        if (NULL != _pointer)
        {
            if (_pointer->dec() == 0)
            {
                delete _pointer;
                _pointer = NULL;
            }
        }
    }

    //赋值运算符
    SharedPointer & operator=(const SharedPointer& r)
    {
        if(_pointer != r._pointer)   //已经判断(this != &r)
        {
            if (NULL != r._pointer)
            {
                r._pointer->inc();
            }

            ElementType *ptr = _pointer;
            _pointer = r._pointer;
            if (NULL != ptr)
            {
                if(ptr->dec() == 0)
                {
                    delete ptr;
                    ptr = NULL;
                }
            }
        }

        return *this;
    }

    //获取底层资源指针
    ElementType* get() const
    {
        return _pointer;
    }

    //返回底层资源指针
    ElementType* operator->() const
    {
        return _pointer;
    }

    //返回底层资源引用
    ElementType& operator*() const
    {
        return *_pointer;
    }

    //判断本智能指针是否持有合法的资源
    bool is_valid() const
    {
        return _pointer ? true : false;
    }

private:
    ElementType* _pointer;  /** 底层资源指针*/
};
}

#endif // SHARED_POINTER_H_INCLUDED
