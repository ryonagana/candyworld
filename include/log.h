#pragma once
#define  LOG_HEADER
//#include <allegro5/allegro.h>
#include <stdio.h>


#define LOG_COMMON 4
#define LOG_INFO 3
#define LOG_WARN 2
#define LOG_CRITICAL 1

#ifdef __cplusplus
extern "C" {
#endif

/*
void log_init();
void log_type(int type);
void log_write(int type, const char *msg, ...);
void log_file(const char *msg, int type);
*/


#if defined(DEBUG)

#define DINFO(fmt,...)     do { fprintf(stdout,"[INFO]:    %s():%d:%s - "fmt"\n", __func__, __LINE__, __FILE__, ##__VA_ARGS__); }while(0) 
#define DLOG(fmt,...)      do { fprintf(stdout,"[LOG]:     %s():%d:%s - "fmt"\n", __func__, __LINE__, __FILE__, ##__VA_ARGS__); }while(0)
#define DWARN(fmt,...)     do { fprintf(stdout,"[WARN]:    %s():%d:%s - "fmt"\n", __func__, __LINE__, __FILE__, ##__VA_ARGS__); }while(0)
#define DCRITICAL(fmt,...) do { fprintf(stderr,"[CRIT] %s():%d:%s - "fmt"\n", __func__, __LINE__, __FILE__, ##__VA_ARGS__); }while(0)
 
#else
#define DINFO(fmt,...)
#define DLOG(fmt,...)
#define DWARN(fmt,...)
#define DCRITICAL(fmt,...)
#endif

#ifdef __cplusplus
}
#endif

