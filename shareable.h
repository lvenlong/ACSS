#ifndef SHAREABLE_H_INCLUDED
#define SHAREABLE_H_INCLUDED

#include "mutex.h"

namespace bigpipe
{
    //�ṩ����ԭ��������ͨ�ü��������ܣ��ɱ��������ָ�������
    class Shareable
    {
    public:
        //��������
        ~Shareable(){};
        //�������ü���
        void inc();
        //�������ü���
        int32_t dec();
        //��ȡ��ǰ���ü���
        int32_t get_count();
    protected:
        //������ʽ���죬����ͨ�����๹��
        Shareable();
    private:
        int32_t _count;
        Mutex _mutex;
    private:
        //���ÿ������칦��
        Shareable(const Shareable&);
        //���ø�ֵ�����
        Shareable& operator=(const Shareable&);
    };
}


#endif // SHAREABLE_H_INCLUDED
