#ifndef CONF_H_
#define CONF_H_
#include <string>
#include <vector>
#include "common.h"
#include "conf_unit.h"

namespace bigpipe {

class ConfUnit;

class ConfLoader {
public:
    static const int32_t MAX_LINE_LEN; //行最大长度
    //static bool load_conf(const std::string& conf_file, ConfUnit& conf_unit); //从配置文件conf_file中加载配置到conf_unit中
    static ConfUnit* load_conf(const char* conf_filename);

//class ConfigureParser {
private:
    //void parse(const std::string& conf_filename, ConfUnit& conf_unit); //从配置文件中解析配置
    //void parse(std::ifstream& conf_file, ConfUnit& conf_unit); //从配置文件中解析配置

//private:

    static bool is_white_line(const char* line); // 判断line是否为空白行
    static bool is_comment_line(const char* line); //判断line是否为注释行----以'#'开关的行
    static int32_t handle_line(const char* line, ConfUnit* root, ConfUnit*& current); //处理line行
    static int32_t handle_as_section(const char* line, std::vector<std::string>& paths); //处理标签
    static int32_t handle_as_item(const char* line, std::string& key, std::string& value); //处理配置
    static ConfUnit* push_section(ConfUnit* root, const std::vector<std::string>& paths); //存标签
    static int32_t push_item(ConfUnit* current, const std::string& key, const std::string& value); //存解析结果

private:
    std::string _filename;
};
}
#endif //BAIDU_ASP-QA_BIGPIPE-TOOL_DEV_CONF_H_
