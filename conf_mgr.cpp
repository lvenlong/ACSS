#include <fstream>

#include "conf_mgr.h"
#include "./base_code/conf_load.h"

namespace bigpipe {
int32_t ConfMgr::init(const char* conf_file)
{
    int32_t ret = false;
    LiLong::ConfUnit *root = LiLong::ConfLoader::load_conf(conf_file);
    if (!root) {
        ss_warn("load conf file %s failed", conf_file);
        //printf("ERROR_1\n");
        return ret;
    }
    if (_info.getter.load((*root)["getter"]) != true || _info.disp.load((*root)["dispatcher"]) != true) {
        ss_warn("load getter conf failed");
        if (root) {
            delete root;
            root = NULL;
        }
        return ret;
    }
    ret = true;
    _init = 1;
    if (root) {
        delete root;
        root = NULL;
    }
    return ret;
}

int32_t ConfMgr::GetConfig(ConfInfo &c)
{
    if (!_init) {
        return false;
    }

    c = _info;
    return true;
}

int32_t IconfLoader::get_int32(LiLong::ConfUnit *loader, const char *key, int32_t &out)
{
    std::string out_s;
    if (get_str(loader, key, out_s) != true) {
        return false;
    }

    if (!LiLong::StringUtil::str2int32(out_s.c_str(), out)) {
        return true;
    }

    return true;
}

int32_t IconfLoader::get_int32_default(LiLong::ConfUnit *loader, const char *key, int32_t def, int32_t &out)
{
    if (get_int32(loader, key, out) != true)	{
        out = def;
    }

    return true;
}

int32_t IconfLoader::get_str_default(LiLong::ConfUnit *loader, const char *key, const char *def, std::string &out)
{
    if (get_str(loader, key, out) == -1) {
        out = def;
    }

    return true;
}

int32_t IconfLoader::get_str(LiLong::ConfUnit *loader, const char *key, std::string &out)
{
    LiLong::ConfUnit	*val	= NULL;
    std::string tmp_str;

    if (!loader || !(loader->is_group()) || !key || !(val = (*loader)[key])) {
        //ss_warn("get_str failed key=%s loader_type=%d", (key ? key : ""), (loader ? loader->get_type() : -1));
        return false;
    }

    if (val->is_string()) {
        tmp_str = val->to_string();
        out = LiLong::StringUtil::trim(tmp_str);
        if (out.size()) {
            return true;
        }
    }

    return false;
}

int32_t ConfGetter::load(LiLong::ConfUnit* loader)
{
    get_str(loader, "_conf_dir", _conf_dir);
    get_str(loader, "_conf_file", _conf_file);
    get_str(loader, "_pipe", _pipe);
    get_str(loader, "_user", _user);
    get_str(loader, "_token", _token);
    get_str(loader, "_user_output_dir", _user_output_dir);
    get_str(loader, "_persisted_file", _persisted_file);
    get_str(loader, "_pipelet", _pipelet);
    get_str(loader, "_bundler_record_num", _bundler_record_num);
    get_str(loader, "_bundler_timeout", _bundler_timeout);

    return true;
}

int32_t ConfDisp::load(LiLong::ConfUnit* loader)
{
    get_int32_default(loader, "queue_len", 10000, queue_len);
    get_int32_default(loader, "count", 1, count);
    return true;
}

}
