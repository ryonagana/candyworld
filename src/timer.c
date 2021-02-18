#include "timer.h"
#include "window.h"

void timer_init(gametimer_t *tm)
{
    tm->now = SDL_GetPerformanceCounter();
    tm->last = 0;


}

void timer_update(gametimer_t *tm)
{
   tm->last = tm->now;
   tm->now = SDL_GetPerformanceCounter();


}



float timer_do_tick(gametimer_t *tm)
{

  return  ((tm->now - tm->last) * 1000 / (double) SDL_GetPerformanceFrequency());

}


