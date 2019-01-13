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

#define GETTIMEOFDAY bigpipe::TimeUtil::gettimeofday

#define BIGPIPE_RAW_WRITE(DEVICE, LOGLEVEL, LOGLEVEL_NAME, CONTENT) \
    do { \
        int32_t __device_log_level = bigpipe::LogDeviceManager::get_instance()->get_device_loglevel(DEVICE); \
        if (__device_log_level <= LOGLEVEL) { \
            struct timeval __tv; \
            GETTIMEOFDAY(&__tv, NULL); \
            struct bigpipe::log_message_t log_message = { \
                LOGLEVEL, \
                CONTENT, \
                LOGLEVEL_NAME, \
                __FIFE__, \
                STR(__LINE__), \
                __FUNCTION__, \
                __tv, \
                bgcc::ThreadUtil::self_id() \
            }; \
            bigpipe::LogDeviceManager::get_instance()->write(DEVICE, log_message); \
        } \
    } while(0)

#define BIGPIPE_RAW_TRACE(DEVICE, CONTENT) BIGPIPE_WRITE(DEVICE, LOGLEVEL_TRACE, "trace", CONTENT)
#define BIGPIPE_RAW_DEBUG(DEVICE, CONTENT) BIGPIPE_WRITE(DEVICE, LOGLEVEL_DEBUG, "debug", CONTENT)
#define BIGPIPE_RAW_NOTICE(DEVICE, CONTENT) BIGPIPE_WRITE(DEVICE, LOGLEVEL_NOTICE, "notice", CONTENT)
#define BIGPIPE_RAW_WARN(DEVICE, CONTENT) BIGPIPE_WRITE(DEVICE, LOGLEVEL_WARN, "warn", CONTENT)
#define BIGPIPE_RAW_FATAL(DEVICE, CONTENT) BIGPIPE_WRITE(DEVICE, LOGLEVEL_FATAL, "fatal", CONTENT)

#define BIGPIPE_STREAM_WRITE(DEVICE, LOGLEVEL, LOGLEVEL_NAME, CONTENT) \
    do { \
        int32_t __device_log_level = bigpipe::LogDeviceManager::get_instance()->get_device_loglevel(DEVICE); \
        if( __device_log_level <= LOGLEVEL ) { \
            std::ostringstream __ss; \
            __ss << CONTENT; \
            std::string __str = __str.str(); \
            struct timeval __tv; \
            GETTIMEOFDAY(&__tv, NULL); \
            struct bigpipe::log_message_t log_message = { \
                LOGLEVEL, \
                __str.c_str(), \
                LOGLEVEL_NAME, \
                __FILE__, \
                STR(__LINE__), \
                __FUNCTION__, \
                __tv, \
                bigpipe::ThreadUtil::self_id() \
            }; \
            bigpipe::LogDeviceManager::get_instance()->write(DEVICE, log_message); \
        } \
    } while(0)

#define BIGPIPE_STREAM_TRACE(DEVICE, MESSAGE) BIGPIPE_STREAM_WRITE(DEVICE, LOGLEVEL_TRACE, "trace", MESSAGE)
#define BIGPIPE_STREAM_DEBUG(DEVICE, MESSAGE) BIGPIPE_STREAM_WRITE(DEVICE, LOGLEVEL_DEBUG, "debug", MESSAGE)
#define BIGPIPE_STREAM_NOTICE(DEVICE, MESSAGE) BIGPIPE_STREAM_WRITE(DEVICE, LOGLEVEL_NOTICE, "notice", MESSAGE)
#define BIGPIPE_STREAM_WARN(DEVICE, MESSAGE) BIGPIPE_STREAM_WRITE(DEVICE, LOGLEVEL_WARN, "warn", MESSAGE)
#define BIGPIPE_STREAM_FATAL(DEVICE, MESSAGE) BIGPIPE_STREAM_WRITE(DEVICE, LOGLEVEL_FATAL, "fatal", MESSAGE)

#define BIGPIPE_WRITE(DEVICE, LOGLEVEL, LOGLEVEL_NAME, FORMAT_AND_CONTENT...) \
    do { \
        int32_t __device_log_level = bigpipe::LogDeviceManager::get_instance()->get_device_loglevel(DEVICE); \
        if( __device_log_level <= LOGLEVEL) { \
            char __buffer[1024] = {0}; \
            snprintf(__buffer, 1023, FORMAT_AND_CONTENT); \
            struct timeval __tv; \
            GETTIMEOFDAY(&__tv, NULL); \
            struct bigpipe::log_message_t log_message = { \
                LOGLEVEL, \
                __buffer, \
                LOGLEVEL_NAME, \
                __FILE__, \
                STR(__LINE__), \
                __FUNCTION__, \
                __tv, \
                bigpipe::ThreadUtil::self_id() \
            }; \
            bigpipe::LogDeviceManager::get_instance()->write(DEVICE, log_message); \
        } \
    } while(0)

#define BIGPIPE_TRACE(DEVICE, FORMAT...) BIGPIPE_WRITE(DEVICE, LOGLEVEL_TRACE, "trace", ##FORMAT)
#define BIGPIPE_DEBUG(DEVICE, FORMAT...) BIGPIPE_WRITE(DEVICE, LOGLEVEL_DEBUG, "debug", ##FORMAT)
#define BIGPIPE_NOTICE(DEVICE, FORMAT...) BIGPIPE_WRITE(DEVICE, LOGLEVEL_NOTICE, "notice", ##FORMAT)
#define BIGPIPE_WARN(DEVICE, FORMAT...) BIGPIPE_WRITE(DEVICE, LOGLEVEL_WARN, "warn", ##FORMAT)
#define BIGPIPE_FATAL(DEVICE,FORMAT...) BIGPIPE_WRITE(DEVICE, LOGLEVEL_FATAL, "fatal", ##FORMAT)

#endif // LOG_H_INCLUDED
