#ifndef TIMER_H
#define TIMER_H
#include <SDL2/SDL.h>


#define TIMER_FPS_DESIRED 60
#define TIMER_DELTATIME 1.5f

typedef struct gametimer_t {
    float delta;
    float last_time;
}gametimer_t;

void timer_init(gametimer_t *tm);
void timer_do_tick(gametimer_t *tm);



#endif // TIMER_H
