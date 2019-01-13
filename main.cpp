#include "string_util.h"
#include "iostream"
#include "string"
#include "conf_load.h"
#include "conf_mgr.h"
#include "common.h"

int main()
{
    bigpipe::log_open(CONF);
    bigpipe::ConfInfo config;
    if(bigpipe::ConfMgr::Instance().init(CONF) != true  || bigpipe::ConfMgr::Instance().GetConfig(config) != true){
        std::cout<< "ERROR " << CONF << std::endl;
    }
        /*std::cout << "  _conf_dir     : " << config.getter._conf_dir << std::endl;
        std::cout << "  _conf_file   : " << config.getter._conf_file << std::endl;
        std::cout << "  _pipe   : " <<config.getter._pipe << std::endl;
        std::cout << "  _user   : " << config.getter._user << std::endl;
        std::cout << "  _token   : " << config.getter._token << std::endl;
        std::cout << "  _user_output_dir   : " << config.getter._user_output_dir << std::endl;
        std::cout << "  _persisted_file   : " << config.getter._persisted_file << std::endl;
        std::cout << "  _pipelet   : " << config.getter._pipelet << std::endl;
        std::cout << "  _bundler_record_num   : " <<config.getter._bundler_record_num << std::endl;
        std::cout << "  _bundler_timeout   : " << config.getter._bundler_timeout << std::endl;*/
        std::cout << config.getter.tostring()<<std::endl;
        ss_trace("This is test");
    return 0;
}
