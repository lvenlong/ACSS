#ifndef STRING_UTIL_H_
#define STRING_UTIL_H_

#include <vector>   // for std::vector
#include <string>   // for std::string
#include <sstream>  // for std::stringstream

#include "common.h"
#include "mutex.h"

namespace LiLong {
class StringUtil {
public:
    static void toupper_inplace(char* str); //将C风格字符串str转换为大写，原字符串被改写
    static std::string toupper(const char* str); //将C风格字符串str转换为大写，原字符串保持不变
    static std::string toupper(const std::string& str); //将字符串str转换为大写，原字符串保持不变
    static void tolower_inplace(char* str); //将C风格字符串str转换为小写，原字符串被改写
    static std::string tolower(const char* str); //将C风格字符串str转换为小写，原字符串保持不变
    static std::string tolower(const std::string& str); //将字符串str转换为小写，原字符串保持不变
    static void ltrim_inplace(char* str); //去除字符串左端的空白，原地修改
    static std::string ltrim(const char* str); //去除字符串左端的空白，原字符串保持不变
    static std::string ltrim(const std::string& str); //去除字符串左端的空白，原字符串保持不变
    static void rtrim_inplace(char* str); //去除字符串右端的空白，原地修改
    static std::string rtrim(const char* str); //去除字符串右端的空白
    static std::string rtrim(const std::string& str); //去除字符串右端的空白
    static void trim_inplace(char* str); //去除C风格字符串两端空白，原地修改
    static std::string trim(const char* str); //去除C风格字符串两端空白
    static std::string trim(const std::string& str); //去除字符串两端空白
    static void split_string(const std::string& str, const std::string& separator, std::vector<std::string>& container, bool filter_empty = false); //切分子串
    static std::string replace_string(const std::string& str, const std::string& target, const std::string& replacement); //替换字串
    static bool str2uint32(const char* str, uint32_t& number); //将数字字符串转化为32位无符号整数
    static bool str2int32(const char* str, int32_t& number); //将数字字符串转化为32位有符号整数
    static bool str2uint64(const char* str, uint64_t& number); //将数字字符串转化为64位无符号整数
    static bool str2int64(const char* str, int64_t& number); //将数字字符串转化为64位有符号整数
    static int32_t xstrncpy(char* dest, const char* src, int32_t n); //功能同strncpy。区别在于xstrncpy返回值为成功复制的字节数
    static std::string rand_string(); //取得一个随机数的字符串形式
    /*将数字字符串转换成为T型的数字*/
    template <typename T> static bool str2integer(const char* str, T& number) {
        if (NULL == str) {
            return false;
        }
        std::stringstream ss;
        T tmp;
        bool ret = false;
        ss << StringUtil::trim(str);
        if (ss.str().length() > 0) {
            try {
                ss >> tmp;
                if (ss.eof() && !ss.fail()) {
                    ret = true;
                    number = tmp;
                }
            } catch (std::ios_base::failure&) {
            }
        }
        return ret;
    }
    /*将T型数字转换为字符串*/
    template<typename T> static std::string integer2str(const T& number) {
        std::stringstream ss;
        ss << number;
        return ss.str();
    }
private:
    static std::string rtrim(const char*str, int32_t len); //去除字符串右端空白
    static Mutex stMutex;
};
}
#endif
