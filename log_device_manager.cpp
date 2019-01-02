#include <iostream>
#include <sstream>

#include "common.h"
#include "log_device_manager.h"
#include "log_device.h"
#include "conf_load.h"
#include "conf_unit.h"
#include "bigpipe_error.h"
#include "string_util.h"

namespace bigpipe
{
    void load_default_device()
    {
        char buffer[BUFSIZ];
        int32_t ret;

        LogDeviceManager* manager = LogDeviceManager::get_instance();
        if(NULL == manager)
        {
            std::cerr << "Get LogDeviceManager singlton failed" << std::endl;
            exit(0);
        }

        ILogDevice* default_device = new(std::nothrow) FileLogDevice("./BigPipe.log", "bigpipe", LOGLEVEL_WARN, BIGPIPE_LOG_SPLIT_POLIT_BY_SIZE, 500*1024*1024, -1, "%D [%N] %T {%F(%L)} %C");
        if(NULL == default_device)
        {
            std::cerr << "Create default device 'bigpipe' failed." << std::endl;
            exit(0);
        }

        ret = default_device->open();
        if(0 != ret)
        {
            std::cerr << "Open default device failed: " << bigpipe_strerror_r(ret, buffer, BUFSIZ) << std::endl;
            delete default_device;
            exit(0);
        }

        if(0 != manager->add_device(default_device))
        {
            std::cerr << "Add device 'bigpipe' failed." <<std::endl;
            delete default_device;
            exit(0);
        }
    }

    static int32_t get_loglevel_from_logdev_confunit(bigpipe::ConfUnit& logdev)
    {
        std::string level_valstr = logdev["level"].to_string();

        int32_t level_value;
        if("TRACE" == level_valstr)
            level_value = LOGLEVEL_TRACE;
        else if("DEBUG" == level_valstr)
            level_value = LOGLEVEL_DEBUG;
        else if("NOTICE" == level_valstr)
            level_value = LOGLEVEL_NOTICE;
        else if("WARN" == level_valstr)
            level_value = LOGLEVEL_WARN;
        else if("FATAL" == level_valstr)
            level_value = LOGLEVEL_FATAL;
        else
        {
            std::cerr << "specify an invalid log level string " << level_valstr << std::endl;
            exit(-1);
        }
        return level_value;
    }

    static int32_t get_split_policy_from_logdev_confunit(bigpipe::ConfUnit& logdev)
    {
        std::string split_policy_valstr = logdev["split_polixy"].to_string();
        int32_t split_policy_value;

        if("SIZE" == split_policy_valstr)
            split_policy_value = BIGPIPE_LOG_SPLIT_POLIT_BY_SIZE;
        else if("TIME" == split_policy_valstr)
            split_policy_value = BIGPIPE_LOG_SPLIT_POLIT_BY_TIME;
        else
        {
            std::cerr << "specify an invalid log split policy string " << split_policy_value << std::endl;
            exit(-1);
        }
        return split_policy_value;
    }

    static int64_t get_maxsize_from_logdev_confunit(bigpipe::ConfUnit& logdev, int32_t split_policy)
    {
        int64_t maxsize_value = 0;
        if(split_policy == BIGPIPE_LOG_SPLIT_POLIT_BY_SIZE)
        {
            maxsize_value = logdev["max_size"].to_integer();
        }
        return maxsize_value;
    }

    static int32_t get_life_circle_from_logdev_confunit(bigpipe::ConfUnit& logdev, int32_t split_policy)
    {
        int32_t life_circle_value = 0;

        if(split_policy == BIGPIPE_LOG_SPLIT_POLIT_BY_TIME)
            life_circle_value = (int32_t)logdev["life_circle"].to_integer();
        return life_circle_value;
    }

    void load_conf_device(const char* conf_filepath)
    {
        int32_t ret;
        LogDeviceManager* manager = LogDeviceManager::get_instance();
        if(NULL == manager)
        {
            std::cerr << "Get LogDeviceManager singlton failed" << std::endl;
            exit(-1);
        }
    }
}
