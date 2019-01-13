#ifndef LOG_DEVICE_MANAGER_H_INCLUDED
#define LOG_DEVICE_MANAGER_H_INCLUDED

#include <vector>
#include "common.h"
#include "log_device.h"

#define STR(x) STR2(x)
#define STR2(x) #x

//log level definition
#define LOGLEVEL_TRACE 0x0
#define LOGLEVEL_DEBUG 0x1
#define LOGLEVEL_NOTICE 0x2
#define LOGLEVEL_WARN 0x3
#define LOGLEVEL_FATAL 0x4
#define LOGLEVEL_NOLOG 0x10

namespace bigpipe
{
    //加载配置文件，打开日志对象；加载内置日志对象
    void log_open(const char* conf_filepath = NULL);

    //关闭日志对象，在main函数结束之前调用
    int32_t log_close();

    class ILogDevice;
    //class FileLogDevice;

    //日志对象
    class LogDeviceManager
    {
    public:
        //获取日志对象单例
        static LogDeviceManager* get_instance();

        //析构函数
        ~LogDeviceManager();

        //判定指定设备device_name是否存在
        bool is_device_exist(const char* device_name);

        //获取指定设备的日志级别
        int32_t get_device_loglevel(const char* device_name);

        //将日志写入设备device_name中
        int32_t write(const char* device_name, const struct log_message_t& log_manage);

        void device_close();

    private:
        //将新设备添加到设备列表中
        int32_t add_device(ILogDevice* device);

        //根据设备名称获取设备
        ILogDevice* get_device(const char* device_name);

        std::vector<ILogDevice*> _devices;

        //禁用显示构造
        LogDeviceManager();

        //禁用拷贝构造
        LogDeviceManager& operator=(const LogDeviceManager&);

    private:
        friend void load_default_device();
        friend void load_conf_device(const char*);
    };
}

#endif // LOG_DEVICE_MANAGER_H_INCLUDED
