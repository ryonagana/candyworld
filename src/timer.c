#include "timer.h"
#include "window.h"

static Uint32 timer_flag_check(game_timer_t *tm, Uint32 flags){
     if( (flags & tm->flags) != tm->flags){
         return 0;
     }
     return tm->flags;
}

void timer_init(game_timer_t *tm)
{
    tm->now = 0;
    tm->pause_ticks = 0;
    tm->flags = TIMER_FLAG_START;
}

void timer_start(game_timer_t *tm)
{
    tm->now = SDL_GetPerformanceCounter(); //SDL_GetTicks();
    //tm->flags |= TIMER_FLAG_START;
}

void timer_end(game_timer_t *tm)
{
    tm->last = SDL_GetPerformanceCounter();
}


void timer_set_stop(game_timer_t *tm)
{
    tm->flags |= ~TIMER_FLAG_START;
}

int timer_is_started(game_timer_t *tm)
{
    if(!timer_flag_check(tm, TIMER_FLAG_START)){
        return 0;
    }

    return tm->flags;
}

double timer_get_ticks(game_timer_t *tm)
{

    if(timer_flag_check(tm, TIMER_PAUSED)){
        return tm->now;
    }

    return (double)((tm->now - tm->last)  / (double) SDL_GetPerformanceFrequency()) * 1000;

    /*
    Uint32 actual_time = 0;

    if(timer_flag_check(tm, TIMER_FLAG_START)){
       if(timer_flag_check(tm, TIMER_PAUSED)){
            actual_time = tm->pause_ticks;
       }else {
            //actual_time = SDL_GetTicks() - tm->now;
            tm->last = tm->now;
            tm->now = SDL_GetPerformanceCounter();
            //tm->last = actual_time;
       }
    }
    return  (double)((tm->now - tm->last) * 1000) / (double) SDL_GetPerformanceFrequency();
    */
}

void timer_set_pause(game_timer_t *tm)
{
    tm->flags |= ~TIMER_PAUSED;
}


void timer_frame_cap(double ticks)
{
    SDL_Delay(FPS_VAL - ticks);
}

