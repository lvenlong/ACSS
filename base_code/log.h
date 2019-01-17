#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#define I32d "%d"
#define I32u "%u"
#define I64d "%ld"
#define I64u "%lu"

#include <sstream>

#include "log_device_manager.h"
#include "thread_util.h"
#include "time_util.h"

#define GETTIMEOFDAY LiLong::TimeUtil::gettimeofday

#define LiLong_RAW_WRITE(DEVICE, LOGLEVEL, LOGLEVEL_NAME, CONTENT) \
    do { \
        int32_t __device_log_level = LiLong::LogDeviceManager::get_instance()->get_device_loglevel(DEVICE); \
        if (__device_log_level <= LOGLEVEL) { \
            struct timeval __tv; \
            GETTIMEOFDAY(&__tv, NULL); \
            struct LiLong::log_message_t log_message = { \
                LOGLEVEL, \
                CONTENT, \
                LOGLEVEL_NAME, \
                __FIFE__, \
                STR(__LINE__), \
                __FUNCTION__, \
                __tv, \
                bgcc::ThreadUtil::self_id() \
            }; \
            LiLong::LogDeviceManager::get_instance()->write(DEVICE, log_message); \
        } \
    } while(0)

#define LiLong_RAW_TRACE(DEVICE, CONTENT) LiLong_WRITE(DEVICE, LOGLEVEL_TRACE, "trace", CONTENT)
#define LiLong_RAW_DEBUG(DEVICE, CONTENT) LiLong_WRITE(DEVICE, LOGLEVEL_DEBUG, "debug", CONTENT)
#define LiLong_RAW_NOTICE(DEVICE, CONTENT) LiLong_WRITE(DEVICE, LOGLEVEL_NOTICE, "notice", CONTENT)
#define LiLong_RAW_WARN(DEVICE, CONTENT) LiLong_WRITE(DEVICE, LOGLEVEL_WARN, "warn", CONTENT)
#define LiLong_RAW_FATAL(DEVICE, CONTENT) LiLong_WRITE(DEVICE, LOGLEVEL_FATAL, "fatal", CONTENT)

#define LiLong_STREAM_WRITE(DEVICE, LOGLEVEL, LOGLEVEL_NAME, CONTENT) \
    do { \
        int32_t __device_log_level = LiLong::LogDeviceManager::get_instance()->get_device_loglevel(DEVICE); \
        if( __device_log_level <= LOGLEVEL ) { \
            std::ostringstream __ss; \
            __ss << CONTENT; \
            std::string __str = __str.str(); \
            struct timeval __tv; \
            GETTIMEOFDAY(&__tv, NULL); \
            struct LiLong::log_message_t log_message = { \
                LOGLEVEL, \
                __str.c_str(), \
                LOGLEVEL_NAME, \
                __FILE__, \
                STR(__LINE__), \
                __FUNCTION__, \
                __tv, \
                LiLong::ThreadUtil::self_id() \
            }; \
            LiLong::LogDeviceManager::get_instance()->write(DEVICE, log_message); \
        } \
    } while(0)

#define LiLong_STREAM_TRACE(DEVICE, MESSAGE) LiLong_STREAM_WRITE(DEVICE, LOGLEVEL_TRACE, "trace", MESSAGE)
#define LiLong_STREAM_DEBUG(DEVICE, MESSAGE) LiLong_STREAM_WRITE(DEVICE, LOGLEVEL_DEBUG, "debug", MESSAGE)
#define LiLong_STREAM_NOTICE(DEVICE, MESSAGE) LiLong_STREAM_WRITE(DEVICE, LOGLEVEL_NOTICE, "notice", MESSAGE)
#define LiLong_STREAM_WARN(DEVICE, MESSAGE) LiLong_STREAM_WRITE(DEVICE, LOGLEVEL_WARN, "warn", MESSAGE)
#define LiLong_STREAM_FATAL(DEVICE, MESSAGE) LiLong_STREAM_WRITE(DEVICE, LOGLEVEL_FATAL, "fatal", MESSAGE)

#define LiLong_WRITE(DEVICE, LOGLEVEL, LOGLEVEL_NAME, FORMAT_AND_CONTENT...) \
    do { \
        int32_t __device_log_level = LiLong::LogDeviceManager::get_instance()->get_device_loglevel(DEVICE); \
        if( __device_log_level <= LOGLEVEL) { \
            char __buffer[1024] = {0}; \
            snprintf(__buffer, 1023, FORMAT_AND_CONTENT); \
            struct timeval __tv; \
            GETTIMEOFDAY(&__tv, NULL); \
            struct LiLong::log_message_t log_message = { \
                LOGLEVEL, \
                __buffer, \
                LOGLEVEL_NAME, \
                __FILE__, \
                STR(__LINE__), \
                __FUNCTION__, \
                __tv, \
                LiLong::ThreadUtil::self_id() \
            }; \
            LiLong::LogDeviceManager::get_instance()->write(DEVICE, log_message); \
        } \
    } while(0)

#define LiLong_TRACE(DEVICE, FORMAT...) LiLong_WRITE(DEVICE, LOGLEVEL_TRACE, "trace", ##FORMAT)
#define LiLong_DEBUG(DEVICE, FORMAT...) LiLong_WRITE(DEVICE, LOGLEVEL_DEBUG, "debug", ##FORMAT)
#define LiLong_NOTICE(DEVICE, FORMAT...) LiLong_WRITE(DEVICE, LOGLEVEL_NOTICE, "notice", ##FORMAT)
#define LiLong_WARN(DEVICE, FORMAT...) LiLong_WRITE(DEVICE, LOGLEVEL_WARN, "warn", ##FORMAT)
#define LiLong_FATAL(DEVICE,FORMAT...) LiLong_WRITE(DEVICE, LOGLEVEL_FATAL, "fatal", ##FORMAT)

#endif // LOG_H_INCLUDED
