#include "iostream"
#include "string"

#include "conf_mgr.h"
#include "./base_code/string_util.h"
#include "./base_code/conf_load.h"
#include "./base_code/common.h"
#include "./base_code/sema.h"
#include "./base_code/LiLong_error.h"

#define CONF "./conf/main.conf"

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
    LiLong::Semaphore sema;
    sema.signal();
    sema.wait();
    int32_t ret = sema.wait(100);
    if(0 == ret){
        std::cout << "sema wait sucess" << std::endl;
    }
    else if(LiLong::E_LiLong_TIMEOUT == ret){
        std::cout << "time out" << std::endl;
    }
    else{
        std::cout << "other error" << std::endl;
    }
    return 0;
}
