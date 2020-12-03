#include "timer.h"
#include "window.h"

void timer_do_tick(gametimer_t *tm)
{
    tm->delta = (SDL_GetTicks() - tm->last_time) * (TIMER_FPS_DESIRED / 1000.0f);

    if(tm->delta >= TIMER_DELTATIME){
        tm->delta = TIMER_DELTATIME;
    }

    tm->last_time = SDL_GetTicks();
}

void timer_init(gametimer_t *tm)
{
    tm->delta = 0.0f;
    tm->last_time  = 0.0f;
}
