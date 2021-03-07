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



double timer_do_tick(gametimer_t *tm)
{
  double delta =  (double)((tm->now - tm->last) * 1000 / SDL_GetPerformanceFrequency());
  delta /= 1000;

  return delta > 1.0 ? 1.0 : delta;

}


