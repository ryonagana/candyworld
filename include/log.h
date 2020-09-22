#pragma once
#define  LOG_HEADER
#include <allegro5/allegro.h>


#define LOG_COMMON 4
#define LOG_INFO 3
#define LOG_WARN 2
#define LOG_CRITICAL 1

#ifdef __cplusplus
extern "C" {
#endif

void log_init();
void log_type(int type);
void log_write(const char *msg, ...);
void log_file(const char *msg);



#ifdef DEBUG

#define DINFO(m,...) { log_type(LOG_INFO); log_write(m,##__VA_ARGS__); }
#define DLOG(m,...) { log_type(LOG_COMMON); log_write(m,##__VA_ARGS__); }
#define DWARN(m,...) { log_type(LOG_WARN); log_write(m,##__VA_ARGS__); }
#define DCRITICAL(m,...) { log_type(LOG_CRITICAL); log_write(m,##__VA_ARGS__); }

#else
#define DINFO(m,...)
#define DLOG(m,...)
#define DWARN(m,...)
#define DCRITICAL(m,...)
#endif

#ifdef __cplusplus
}
#endif

