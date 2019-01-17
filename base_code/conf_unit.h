#ifndef CONF_UNIT_H_
#define CONF_UNIT_H_

#include <string>
#include <map>
#include <vector>
#include "common.h"

namespace LiLong {
class ConfUnit {
public:
    typedef std::vector<ConfUnit*>::const_iterator const_iterator;
    typedef std::vector<ConfUnit*>::iterator iterator;

    /*配置单元的类型标识*/
    enum unit_type_t {
        UT_NULL,
        UT_BOOL,
        UT_INTEGER,
        UT_INT32,
        UT_INT64,
        UT_DOUBLE,
        UT_STRING,
        UT_ARRAY,
        UT_GROUP
    };
    ConfUnit(); //默认构造函数
    explicit ConfUnit(unit_type_t type); //构造函数。通过类型标识构造
    explicit ConfUnit(bool b); //构造bool类型配置单元
    explicit ConfUnit(int32_t i); //构造int32_t类型配置单元
    explicit ConfUnit(int64_t l); //构造int64_t类型配置单元
    explicit ConfUnit(double d); //构造double类型配置单元
    explicit ConfUnit(const char* str); //构造string类型配置单元
    explicit ConfUnit(const std::string& str); //构造string类型配置单元
    ~ConfUnit();
    int32_t get_type() const; //获取配置单元类型
    bool is_bool() const; //判断配置单元是否为bool类型
    bool is_int32() const; //判断配置单元是否为int32类型
    bool is_int64() const; //判断配置单元是否为int64类型
    bool is_double() const; //判断配置单元是否为dobule类型
    bool is_string() const; //判断配置单元是否为string类型
    bool is_array() const; //判断配置单元是否为array类型
    bool is_group() const; //判断配置单元是否为group类型
    bool to_bool() const; //取出配置单元中的bool值
    int64_t to_integer() const; //取出配置单元中的int64值
    int32_t to_int32() const; //取出配置单元中的int32值
    int64_t to_int64() const; //取出配置单元中的int64值
    double to_double() const; //取出配置单元中的double值
    std::string to_string() const; //取出配置单元中的string值
    void set_bool(bool b); //设置bool类型配置的bool值
    void set_int32(int32_t i); //设置int32类型配置的int32值
    void set_int64(int64_t l); //设置int64类型配置的int64值
    void set_double(double d); //设置double类型配置单元的double值
    void set_string(const std::string& str); //设置string类型配置单元的string值
    const_iterator begin() const; //取出array类型的首迭代器
    const_iterator end() const; //取出array类型的尾迭代器
    ConfUnit* operator[](const std::string& index); //取出对应下标上的配置单元指针
    ConfUnit* push_back(ConfUnit* punit); //将新元素插入array中
    void pop_back(); //从array中弹出元素
    void insert(const std::string& key, ConfUnit* punit); //将新元素作为属性key插入group中
    void erase(const std::string& key); //从group中删除属性名key对应的配置单元
    void clear(); //清空array或group
    int32_t size() const; //返回配置单元元素个数
private:
    unit_type_t _type;
    union {
        bool b;
        int32_t i;
        int64_t l;
        double d;
    } _union;

    std::string _string;
    std::vector<ConfUnit*> _vector;
    std::map<std::string, ConfUnit*> _map;
};
}
#endif //_CONF_UNIT_H_
