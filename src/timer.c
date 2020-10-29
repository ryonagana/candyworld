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
    tm->start_time = 0;
    tm->pause_ticks = 0;
    tm->flags = TIMER_FLAG_NONE;
}

void timer_set_start(game_timer_t *tm)
{
    tm->start_time = SDL_GetTicks();
    tm->flags |= TIMER_FLAG_START;
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

Uint32 timer_get_ticks(game_timer_t *tm)
{
    Uint32 actual_time = 0;

    if(timer_flag_check(tm, TIMER_FLAG_START)){
       if(timer_flag_check(tm, TIMER_PAUSED)){
            actual_time = tm->pause_ticks;
       }else {
            actual_time = SDL_GetTicks() - tm->start_time;
            tm->last = actual_time;
       }
    }
    return actual_time;
}

void timer_set_pause(game_timer_t *tm)
{
    tm->flags |= ~TIMER_PAUSED;
}


void timer_frame_cap(Uint32 ticks)
{

   if(ticks  < 1000 / FPS){
       SDL_Delay( (1000 - FPS) - ticks);
   }

}
