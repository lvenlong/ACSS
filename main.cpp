#include "iostream"
#include "string"

#include "conf_mgr.h"
#include "./base_code/string_util.h"
#include "./base_code/conf_load.h"
#include "./base_code/common.h"
#include "./base_code/sema.h"
#include "./base_code/LiLong_error.h"
#include "./base_code/sync_vector.h"
#include "./base_code/Thread.h"
#include "./base_code/runnable.h"
#include "./base_code/time_util.h"
#include "./base_code/thread_pool.h"

#define CONF "./conf/main.conf"

LiLong::SyncVector<int32_t> numbers;

//void* coco(void* arg)
//{
//    int ret;
//    ret = numbers.put(1);
//    if(ret == 0){
//        std::cout << "first right" << std::endl;
//    }
//    ret =numbers.put(2);
//     if(ret == 0){
//        std::cout << "second right" << std::endl;
//    }
//    ret = numbers.put(3);
//     if(ret == 0){
//        std::cout << "third right" << std::endl;
//    }
//    return NULL;
//}

class coco : public LiLong::Runnable
{
public:
    virtual int32_t operator()(const bool isstopped, void* param)
    {
        int ret;
        ret = numbers.put(1);
        if(ret == 0)
        {
            std::cout << "first right" << std::endl;
        }
        ret =numbers.put(2);
        if(ret == 0)
        {
            std::cout << "second right" << std::endl;
        }
        ret = numbers.put(3);
        if(ret == 0)
        {
            std::cout << "third right" << std::endl;
        }
        return 1;
    }
};

class cocoRunner : public LiLong::Runnable
{
public:
    virtual int32_t operator()(const bool isstopped, void* param)
    {
        int32_t num;
        int32_t ret;
        while(true){
            ret = numbers.get(num, 10000);
            if(0 == ret){
                std::cout << num << std::endl;
            }
            else if(LiLong::E_LiLong_TIMEOUT == ret){
                    std::cout << "BREAK" << std::endl;
                break;
            }
            else{
                std::cout << "error" << std::endl;
                break;
            }
        }
        return 1;
    }
};

int main()
{
    LiLong::log_open(CONF);
    bigpipe::ConfInfo config;
    if(bigpipe::ConfMgr::Instance().init(CONF) != true  || bigpipe::ConfMgr::Instance().GetConfig(config) != true)
    {
        std::cout<< "ERROR " << CONF << std::endl;
    }
    std::cout << config.getter.tostring()<<std::endl;
    std::cout << config.disp.tostring() <<std::endl;

    ss_trace("This is test");

//    LiLong::Semaphore sema;
//    sema.signal();
//    sema.wait();
//    int32_t ret = sema.wait(100);
//    if(0 == ret)
//    {
//        std::cout << "sema wait sucess" << std::endl;
//    }
//    else if(LiLong::E_LiLong_TIMEOUT == ret)
//    {
//        std::cout << "time out" << std::endl;
//    }
//    else
//    {
//        std::cout << "other error" << std::endl;
//    }

//    LiLong::Thread t1((LiLong::run_func_t)coco);
    LiLong::ThreadPool tp;
    LiLong::ThreadPool tp1;
//    t1.start();
    //LiLong::TimeUtil::safe_sleep_s(10);

    bool b0k = tp.addTask(LiLong::SharedPointer<LiLong::Runnable>(new coco));
    bool b1k = tp1.addTask(LiLong::SharedPointer<LiLong::Runnable>(new cocoRunner));
    int ret1 = tp.init(1);
    int ret2 = tp1.init(1);
    if(ret1==0 || b0k != true || b1k != true){
        std::cout << "add task error" << std::endl;
    }

    //LiLong::Thread t2(LiLong::SharedPointer<LiLong::Runnable>(new cocoRunner));

    //t2.start();
    return 0;
}
