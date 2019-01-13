#ifndef TIME_UTIL_H_
#define TIME_UTIL_H_

#include <string>
#include "common.h"


namespace bigpipe {
class TimeUtil {
public:
    static uint64_t get_timestamp_s(); //获取时间戳（秒）
    static uint64_t get_timestamp_ms(); //获取时间戳（毫秒）
    static uint64_t get_timestamp_us(); //获取微秒级时间戳
    static void safe_sleep_s(uint32_t second); //支持中断的sleep（秒）
    static void safe_sleep_ms(uint32_t millisecond); //safe_sleep_ms 支持中断的sleep（毫秒）
    static std::string format_datetime_str(uint64_t millisecond); //将时间戳格式化
    static int32_t strftimeval(char* buffer, int32_t buflen, const struct timeval* tv); //将struct timeval转换为字符串形式，格式为"YYYY-MM-DD HH:mm::SS.xxx"
    static std::string get_date(); //获取日期串 "YYYYMMDD"
    static std::string get_time(); //获取时间串 "HHmmSS.xxx"
    static int32_t get_day(); //获取当前星期几
    static int32_t get_day(time_t time);   //获取指定日期的星期几
    static std::string format_time(const char * fmt = NULL); //格式化当前时间，默认格式为【%Y%m%d-%H:%M:%S】
    static std::string format_time(time_t time, const char * fmt = NULL); //格式化指定时间，默认格式为【%Y%m%d-%H:%M:%S】
    static std::string format_time(const struct timeval* tv, const char * fmt = NULL); //格式化指定时间，默认格式为【%Y%m%d-%H:%M:%S】
    static int32_t gettimeofday(struct ::timeval *tv, struct timezone *tz); //格式化指定时间，默认格式为【%Y%m%d-%H:%M:%S】
    static int32_t get_abs_timespec(struct timespec* ts, int32_t millisecond); //获取从当前时间后 milliSeconds 毫秒后的绝对时间
};
}
#endif
