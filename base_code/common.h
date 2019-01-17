#ifndef  COMMON_H_
#define  COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<stdint.h>

#include "log.h"

//typedef int int32_t;
#define SOCKET int32_t
#define MAX_BUNDLER_RECORDS_NUM_EVERY_TRY  10;
#define CONF_DIR  "./conf";
#define MAIN_CONF_FILE  "main.conf";
#define ROOT_KEY  "SUBSCRIBER";
#define BP_CONF_DIR  "LiLong_file_path";
#define BP_CONF_FILE  "LiLong_file_name";
#define OUT_DIR  "output_dir";
#define PERSISTED_FILE  "persisted_file";
#define LOG_CONF_FILE  "com_log.conf";
#define PIPENAME  "pipename";
#define PIPELET_IDX  "pipelet_idx";
#define SEQ_ID  "seq_id";
#define STARTPOINT  "startpoint";
#define USERNAME  "username";
#define TOKEN  "token";
#define BUNDLER_NUM  "bundler_record_num";
#define BUNDLER_TIMEOUT  "bundler_time_out";
#define BUFFER_SIZE  10240;
#define PEEK_ERROR_RETRY_NUM_COUNT  5;

#define LOGNAME "session"
#define ss_trace(fmt, arg...) do{LiLong_TRACE(LOGNAME, fmt, ##arg);}while(0)
#define ss_debug(fmt, arg...) do{LiLong_DEBUG(LOGNAME, fmt, ##arg);}while(0)
#define ss_notice(fmt, arg...) do{LiLong_NOTICE(LOGNAME, fmt, ##arg);}while(0)
#define ss_warn(fmt, arg...) do{LiLong_WARN(LOGNAME, fmt, ##arg);}while(0)
#define ss_fatal(fmt, arg...) do{LiLong_FATAL(LOGNAME, fmt, ##arg);}while(0)


#endif
