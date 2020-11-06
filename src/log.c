#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <SDL2/SDL.h>
//static variables init;
#include "shared.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ALLEGRO_LOG
#include <allegro5/allegro_native_dialog.h>
static ALLEGRO_TEXTLOG *allegro_log = NULL;
#endif

static char prefix[30] = {0};

void log_init()
{
#ifdef ALLEGRO_LOG
    allegro_log = al_open_native_text_log("Debug Log:", ALLEGRO_TEXTLOG_MONOSPACE | ALLEGRO_TEXTLOG_NO_CLOSE);
    UNUSED(common_log);
#endif

}



void log_type(int type)
{


    switch(type){

        default:
        case LOG_COMMON:
            strncpy(prefix, "[LOG] ", 30);
        break;

        case LOG_INFO:
            strncpy(prefix, "[INFO] ", 30);
        break;

        case LOG_WARN:
            strncpy(prefix, "[WARN] ", 30);
        break;
        case LOG_CRITICAL:
            strncpy(prefix, "[CRITICAL] ", 30);
        break;



    }


}


void log_write(int type, const char *msg, ...)
{

    char logbuf[1024] = {0};


    va_list lst;
    va_start(lst, msg);
    vsnprintf(logbuf, sizeof(logbuf), msg, lst);
    va_end(lst);
    log_file(logbuf, type);
}



void log_file(const char *msg, int type)
{
#ifdef ALLEGRO_LOG
     al_append_native_text_log(allegro_log, "\n%s: %s - Line: %d, Src: %s\n", prefix, msg, __LINE__, __FILE__);

#else

    switch(type){

        case LOG_COMMON:
            SDL_LogError(SDL_LOG_PRIORITY_INFO, "%s: %s - line: %d - File: %s", prefix, msg, __LINE__, __FILE__);
        break;
        case LOG_WARN:
            SDL_LogError(SDL_LOG_PRIORITY_WARN, "%s: %s - line: %d - File: %s", prefix, msg, __LINE__, __FILE__);
        break;
        case LOG_INFO:
            SDL_LogError(SDL_LOG_PRIORITY_INFO, "%s: %s - line: %d - File: %s", prefix, msg, __LINE__, __FILE__);
        break;

        case LOG_CRITICAL:
            SDL_LogError(SDL_LOG_CATEGORY_ERROR,"%s: %s - line: %d - File: %s", prefix, msg, __LINE__, __FILE__);
        break;


    }

    SDL_Log("%s: %s - line: %d - File: %s", prefix, msg, __LINE__, __FILE__);

#endif
}


#ifdef __cplusplus
}
#endif

