#ifndef TIMER_H
#define TIMER_H
#include <SDL2/SDL.h>

enum {
    TIMER_FLAG_NONE  = 0x0,
    TIMER_FLAG_START = 0x2,
    TIMER_PAUSED     = 0x4,
    TIMER_PLAY       = 0x8
};

typedef struct timer_t {
    Uint32 start_time;
    Uint32 pause_ticks;
    Uint32 flags;
}timer_t;


void timer_init(timer_t *tm);
void timer_set_start(timer_t *tm);
void timer_set_stop(timer_t *tm);
void timer_set_pause(timer_t *tm);
int  timer_is_started(timer_t *tm);
int  timer_is_paused(timer_t *tm);
Uint32 timer_get_ticks(timer_t *tm);

#define TIMER_TICKS_TO_SECS(t) (Uint32)((t) / 1000)
//#define TIMER_TICKS_TO_MSECS(t) (Uint32)((t) / 10)

#endif // TIMER_H
