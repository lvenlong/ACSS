#ifndef SEMA_H_INCLUDED
#define SEMA_H_INCLUDED

#include "common.h"

#define BIGPIPE_SEMA_WAIT_INFINITE UINT_MAX
#define bigpipe_sem_t sem_t

namespace bigpipe
{
    //ʵ���̼߳�����ͬ��
    class Semaphore
    {
    public:
        //���캯����ninit �ź����ĳ�ʼֵ
        Semaphore(int32_t ninit = 0)
        //��������
        ~Semaphore();
        //�ȴ��ź���;millisecond ��ʱʱ�������룩
        int32_t wait(uint32_t millisecond = BIGPIPE_SEMA_WAIT_INFINITE);
        bool try_wait();
        //�����ź���
        int32_t signal();
    protected:
        //���ÿ������캯��
        Semaphore(const Semaphore&);
        //���ø�ֵ�����
        Semaphore& operator=(const Semaphore&);
    private:
        bigpipe_sem_t _sem;
    };
}

#endif // SEMA_H_INCLUDED
