#include <iostream>

#include "time_util.h"
#include "string_util.h"
#include <errno.h>
#include <sys/time.h>

namespace bigpipe {
static struct tm* localtime_r(const time_t* timep, struct tm* result = NULL) {
    return ::localtime_r(timep, result);
}

int32_t TimeUtil::gettimeofday(struct ::timeval *tv, struct timezone *tz)
{
    return ::gettimeofday(tv,(__timezone_ptr_t)tz);
}

uint64_t TimeUtil::get_timestamp_s()
{
    struct ::timeval tv = {0, 0};
    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}

uint64_t TimeUtil::get_timestamp_ms()
{
    struct ::timeval tv = {0, 0};
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

uint64_t TimeUtil::get_timestamp_us()
{
    struct ::timeval tv = {0, 0};
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000000 + tv.tv_usec;
}

void TimeUtil::safe_sleep_s(uint32_t second)
{
    struct timespec interval;
    struct timespec remainder;
    int32_t ret;

    interval.tv_sec = second;
    interval.tv_nsec = 0;

    ret = nanosleep(&interval, &remainder);
    if (-1 == ret) {
        while (EINTR == errno && -1 == ret) {
            ret = nanosleep(&remainder, &remainder);
        }
    }
}

void TimeUtil::safe_sleep_ms(uint32_t millisecond)
{
    struct timespec interval, remainder;
    int32_t ret;

    interval.tv_sec = millisecond / 1000U;
    interval.tv_nsec = (uint64_t)millisecond % 1000UL * 1000UL * 1000UL;

    ret = nanosleep(&interval, &remainder);
    if (-1 == ret) {
        while (EINTR == errno && -1 == ret) {
            ret = nanosleep(&remainder, &remainder);
        }
    }
}

std::string TimeUtil::format_datetime_str(uint64_t millisecond)
{
    time_t time = (time_t)(millisecond / 1000);
    struct tm t;
    struct tm *pt = NULL;
    char buffer[24] = {0};

    pt = bigpipe::localtime_r(&time, &t);
    if (NULL != pt) {
        t = *pt;
        snprintf(buffer, 24, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
                t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, (int32_t)(millisecond % 1000));
    }
    return std::string(buffer);
}
int32_t TimeUtil::get_abs_timespec(struct timespec* ts, int32_t millisecond)
{
    struct timeval tv;
    int32_t ret;

    if (NULL == ts) {
        return false;
    }

    ret = gettimeofday(&tv, NULL);
    if (0 != ret) {
        return ret;
    }

    ts->tv_sec = tv.tv_sec;
    ts->tv_nsec = tv.tv_usec * 1000UL;

    ts->tv_sec += millisecond / 1000UL;
    ts->tv_nsec += millisecond % 1000UL * 1000000UL;

    ts->tv_sec += ts->tv_nsec / (1000UL * 1000UL * 1000UL);
    ts->tv_nsec %= (1000UL * 1000UL * 1000UL);

    return 0;
}

int32_t TimeUtil::strftimeval(char* buffer, int32_t buflen, const struct timeval* tv)
{
    if (NULL == buffer || NULL == tv) {
        return -1;
    }

    time_t time = tv->tv_sec;
    struct tm t;
    struct tm *pt = NULL;

    pt = bigpipe::localtime_r(&time, &t);
    if (NULL == pt) {
        return -1;
    }
    t = *pt;
    return snprintf(buffer, buflen, "%04d-%02d-%02d %02d:%02d:%02d.%03d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, (int32_t)tv->tv_usec / 1000);
}

std::string TimeUtil::get_date()
{
    time_t t = time(NULL);
    struct tm result;
    struct tm *presult = NULL;
    char buffer[20] = {0};
    presult = bigpipe::localtime_r(&t, &result);
    if (NULL != presult) {
        result = *presult;
        strftime(buffer, 20, "%Y%m%d", &result);
    }

    return std::string(buffer);
}

std::string TimeUtil::get_time()
{
    time_t t = time(NULL);
    struct tm result;
    struct tm *presult = NULL;
    char buffer[20] = {0};
    presult = bigpipe::localtime_r(&t, &result);
    if (NULL != presult) {
        result = *presult;
        strftime(buffer, 20, "%H%M%S", &result);
    }

    return std::string(buffer);
}

int32_t TimeUtil::get_day()
{
    time_t t = time(NULL);
    struct tm result;
    struct tm *presult = NULL;
    presult = bigpipe::localtime_r(&t, &result);
    if (NULL == presult) {
        return -1;
    }
    result = *presult;
    return result.tm_wday;
}

int32_t TimeUtil::get_day(time_t time)
{
    struct tm result;
    struct tm *presult = NULL;
    presult = bigpipe::localtime_r(&time, &result);
    if (NULL == presult) {
        return -1;
    }
    result = *presult;
    return result.tm_wday;
}

std::string TimeUtil::format_time(const char * fmt)
{
    //获取时间
    struct ::timeval tv = {0, 0};
    gettimeofday(&tv, NULL);

    return format_time(&tv, fmt);
}

std::string TimeUtil::format_time(time_t time, const char * fmt)
{
    struct ::timeval tv = {0, 0};
    tv.tv_sec = static_cast <long>(time);

    return format_time(&tv, fmt);
}

std::string TimeUtil::format_time(const struct timeval* tv, const char * fmt)
{
    struct tm result;
    struct tm  *presult = NULL;
    time_t t = tv->tv_sec;
    char buffer[50] = {0};
    char tmp[8];
    if (NULL == fmt) {
        //格式化当前时间
        presult = bigpipe::localtime_r(&t, &result);
        if (NULL != presult) {
            result = *presult;
            strftime(buffer, sizeof(buffer), "%Y%m%d-%H:%M:%S", &result);
        }
    } else {
        std::string str_fmt(fmt);
        std::string str_tmp;
        if (std::string::npos != str_fmt.find("[m]")) {
            //替换毫秒时间
            snprintf(tmp, 8, "%03d", (int)(tv->tv_usec / 1000));
            str_tmp.assign(tmp);
            str_fmt = StringUtil::replace_string(str_fmt, "[m]", str_tmp);
        }
        if (std::string::npos != str_fmt.find("[u]")) {
            //替换微秒时间
            snprintf(tmp, 8, "%06d", (int)(tv->tv_usec));
            str_tmp.assign(tmp);
            str_fmt = StringUtil::replace_string(str_fmt, "[u]", str_tmp);
        }
        if (std::string::npos != str_fmt.find("[U]")) {
            //替换微秒时间
            snprintf(tmp, 8, "%03d", (int)(tv->tv_usec % 1000));
            str_tmp.assign(tmp);
            str_fmt = StringUtil::replace_string(str_fmt, "[U]", str_tmp);
        }
        presult = bigpipe::localtime_r(&t, &result);
        if (NULL != presult) {
            result = *presult;
            strftime(buffer, sizeof(buffer), str_fmt.c_str(), &result);
        }
    }
    return std::string(buffer);
}
}
