#ifndef LOG_DEVICE_H_INCLUDED
#define LOG_DEVICE_H_INCLUDED

#include "common.h"
#include "time_util.h"
#include "mutex.h"

#define MAX_DEVICE_NAME_LEN 512
#define MAX_FILE_PATH_LEN 512
#define MAX_LOG_FORMAT_LEN 512

#define BIGPIPE_LOG_SPLIT_POLIT_BY_TIME 0x0
#define BIGPIPE_LOG_SPLIT_POLIT_BY_SIZE 0x1

namespace bigpipe
{
    struct log_message_t //用于表示传输到日志设备的日志信息
    {
        int32_t loglevel; //日志级别
        const char* content; //日志内容，在格式串中用%c表示
        const char* loglevel_name; //日志级别名称，在格式串中用%N表示
        const char* filename; //日志所在文件的文件名，在格式串中%F表示
        const char* line; //日志所在文件的行号，在格式串中用%L表示
        const char* func_name; //日志所在函数名
        struct ::timeval tv; //日志产生的日期时间，在格式串中%D表示
        long long tid; //线程ID，在格式串中用%T表示
    };

    /*日志设备接口。此类规定了日志设备所具有的公共方法*/
    class ILogDevice{
    public:
        //日志设备接口析构函数
        virtual ~ILogDevice(){}
        //判断日志设备是否已打开,若日志设备已打开则返回true；否则返回false
        virtual bool is_opened() const = 0;
        //打开日志设备
        virtual int32_t open(void* param = NULL) = 0;
        //关闭日志设备
        virtual int32_t close(void* param = NULL) = 0;
        //写日志,log_message 日志信息
        virtual int32_t write(const struct log_message_t& log_message) = 0;
        //返回日志设备级别
        virtual int32_t get_loglevel() const = 0;
        //返回日志设备分割策略
        virtual int32_t get_split_policy() const = 0;
        //返回日志设备文件最大值（单位为字节）
        virtual off_t get_max_size() const = 0;
        //返回日志设备文件记录最大时长（单位为秒）
        virtual int32_t get_max_record_interval() const = 0;
        //获取日志设备的日志格式控制串
        virtual const char* get_log_format() const = 0;
    };

    /*日志设备的抽象类。此类定义的日志设备的通用方法*/
     class AbstractLogDevice : public ILogDevice
     {
     public:
        //构造函数，name 日志设备名，loglevel 设备日志级别，split_policy 设备分割策略，max_size 日志文件最大字节数，max_record_interval 日志文件记录最大时长，log_format 日志格式控制串
        AbstractLogDevice(const char* name, int32_t loglevel, int32_t split_policy, off_t max_size, int32_t max_record_interval, const char* log_format);
        //析构函数
        virtual ~AbstractLogDevice();
        //返回日志设备名称
        virtual const char* get_name() const;
        //返回日志设备级别
        virtual int32_t get_loglevel() const;
        //返回日志设备分割策略
        virtual int32_t get_split_policy() const;
        //返回日志设备文件最大值（单位为字节）
        virtual off_t get_max_size() const;
        //返回日志设备文件记录最大时长（单位为秒）
        virtual int32_t get_max_record_interval() const;
        //获取日志设备的日志格式控制串
        virtual const char* get_log_format() const;
     protected:
        char    _name[MAX_DEVICE_NAME_LEN]; /** 设备名称*/
        int32_t _loglevel;                  /** 设备日志等级*/
        int32_t _split_policy;              /** 分割策略*/
        int32_t _max_size;                  /** 文件最大长度(单位字节)*/
        int32_t _max_record_interval;       /** 文件最大记录周期(单位秒)*/
        char    _log_format[MAX_LOG_FORMAT_LEN]; /** 日志设备的日志格式控制串*/
     };

     /*文件日志设备类*/
     class FileLogDevice : public AbstractLogDevice
     {
     public:
        //构造函数:文件日志设备文件路径,日志设备名,设备日志级别,设备分割策略,日志文件最大字节数,日志文件记录最大时长,日志格式控制串
         FileLogDevice(const char* file_path, const char* name, int32_t loglevel, int32_t split_policy, off_t max_size, int32_t max_record_interval, const char* log_format);
         virtual ~FileLogDevice();
         //判断日志设备是否已打开
         virtual bool is_opened() const;
         //打开日志设备
         virtual int32_t open(void* param = NULL);
         //关闭日志设备
         virtual int32_t close(void* param = NULL);
         //写日志
         virtual int32_t write(const struct log_message_t& log_message);
     private:
        std::string create_filename_suffix();

        char _file_path[MAX_FILE_PATH_LEN]; //文件全路径名
        FILE* _fp; //文件指针
        Mutex _mutex;
        struct ::timeval _create_time; //文件的创建时间，用于time日志分割策略，采用此成员的原因是通过fstat得到的stat变量无法表示文件创建时间
        off_t _file_size; //存放当前日志文件大小
     };
}

#endif // LOG_DEVICE_H_INCLUDED
