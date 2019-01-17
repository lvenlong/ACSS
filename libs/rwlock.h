#ifndef RWLOCK_H_INCLUDED
#define RWLOCK_H_INCLUDED

#include "../base_code/common.h"

namespace LiLong
{
    class RWLock
    {
    public:
        //���캯��
        RWLock();
        //��������
        ~RWLock();
        //��ȡ����
        int32_t get_rdlock();
        //���Ի�ȡд��
        int32_t try_rdlock();
        //��ȡд��
        int32_t get_wlock();
        //���Ի�ȡд��
        int32_t try_wlock();
        //����
        int32_t unlock();
    private:
        pthread_rwlock_t _rwlock;
    };
}

#endif // RWLOCK_H_INCLUDED
