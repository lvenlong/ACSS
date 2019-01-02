#ifndef CONF_MGR_H_
#define CONF_MGR_H_

#include <set>
#include "common.h"
#include "string"
#include <iostream>
#include <sstream>
#include "conf_unit.h"
#include "string_util.h"
#include "conf_load.h"

namespace bigpipe {

class IconfLoader {
public:
    virtual int32_t load(bigpipe::ConfUnit *loader) = 0;
    virtual std::string tostring() = 0;
protected:
    int32_t get_str_default(bigpipe::ConfUnit *loader, const char *key, const char *def, std::string &out);
    int32_t get_str(bigpipe::ConfUnit *loader, const char *key, std::string &out);
    int32_t get_int32_default(bigpipe::ConfUnit *loader, const char *key, int32_t def, int32_t &out);
    int32_t get_int32(bigpipe::ConfUnit *loader, const char *key, int32_t &out);
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
    int32_t load(bigpipe::ConfUnit* loader);
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

class ConfInfo {
public:
    ConfGetter getter;

    std::string Dump() {
        std::ostringstream oss;
        oss << getter.tostring();
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
