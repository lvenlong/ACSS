#ifndef CONF_MGR_H_
#define CONF_MGR_H_

#include <set>
#include <iostream>
#include <sstream>

#include "string"
#include "./base_code/common.h"
#include "./base_code/conf_unit.h"
#include "./base_code/string_util.h"
#include "./base_code/conf_load.h"

namespace bigpipe {

class IconfLoader {
public:
    virtual int32_t load(LiLong::ConfUnit *loader) = 0;
    virtual std::string tostring() = 0;
protected:
    int32_t get_str_default(LiLong::ConfUnit *loader, const char *key, const char *def, std::string &out);
    int32_t get_str(LiLong::ConfUnit *loader, const char *key, std::string &out);
    int32_t get_int32_default(LiLong::ConfUnit *loader, const char *key, int32_t def, int32_t &out);
    int32_t get_int32(LiLong::ConfUnit *loader, const char *key, int32_t &out);
};

class ConfGetter : public IconfLoader {
public:
    std::string _conf_dir;
    std::string _conf_file;
    std::string _pipe;
    std::string _user;
    std::string _token;
    std::string _user_output_dir;
    std::string _persisted_file;
    std::string _pipelet;
    std::string _bundler_record_num;
    std::string _bundler_timeout;
    int32_t load(LiLong::ConfUnit* loader);
    virtual std::string tostring() {
        std::ostringstream oss;
        oss << "nGETTER CONFIG" << std::endl;
        oss << "  _conf_dir     : " << _conf_dir << std::endl;
        oss << "  _conf_file   : " << _conf_file << std::endl;
        oss << "  _pipe   : " << _pipe << std::endl;
        oss << "  _user   : " << _user << std::endl;
        oss << "  _token   : " << _token << std::endl;
        oss << "  _user_output_dir   : " << _user_output_dir << std::endl;
        oss << "  _persisted_file   : " << _persisted_file << std::endl;
        oss << "  _pipelet   : " << _pipelet << std::endl;
        oss << "  _bundler_record_num   : " << _bundler_record_num << std::endl;
        oss << "  _bundler_timeout   : " << _bundler_timeout << std::endl;

        return oss.str();
    }
    virtual ~ConfGetter() {}
};

class ConfDisp : public IconfLoader
{
public:
    int32_t count;
    int32_t queue_len;
    int32_t load(LiLong::ConfUnit* loader);
    virtual std::string tostring()
    {
        std::ostringstream oss;
        oss << "DISPATCHER CONFIG" << std::endl;
        oss << "  queue_len   : " << queue_len << std::endl;
        oss << "  count       : " << count << std::endl;
        return oss.str();
    }
public:
    virtual ~ConfDisp(){};
};

class ConfInfo {
public:
    ConfGetter getter;
    ConfDisp disp;

    std::string Dump() {
        std::ostringstream oss;
        oss << getter.tostring();
        oss << disp.tostring();
        return oss.str();
    }
};

class ConfMgr {
public:
    static ConfMgr& Instance() {
        static ConfMgr mgr;
        return mgr;
    }
    int32_t init(const char* conf_file);
    int32_t GetConfig(ConfInfo &c);
private:
    int32_t _init;
    ConfInfo _info;
    ConfMgr(): _init(0) {}
};
}
#endif //BAIDU_ASP-QA_BIGPIPE-TOOL_DEV_CONF_MGR_H_
