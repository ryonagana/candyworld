#ifndef TIMER_H
#define TIMER_H
#include <SDL2/SDL.h>

enum {
    TIMER_FLAG_NONE  = 0x0,
    TIMER_FLAG_START = 0x2,
    TIMER_PAUSED     = 0x4,
    TIMER_PLAY       = 0x8
};

typedef struct game_timer_t {
    Uint64 now;
    Uint64 last;
    Uint64 pause_ticks;
    Uint32 flags;
}game_timer_t;

#define FPS_VAL   16.666f


void timer_init(game_timer_t *tm);


void timer_start(game_timer_t *tm);
void timer_end(game_timer_t *tm);


void timer_set_stop(game_timer_t *tm);
void timer_set_pause(game_timer_t *tm);
int  timer_is_started(game_timer_t *tm);
int  timer_is_paused(game_timer_t *tm);
double timer_get_ticks(game_timer_t *tm);
void timer_frame_cap(double ticks);

#define TIMER_TICKS_TO_SECS(t) (Uint32)((t) / 1000)
//#define TIMER_TICKS_TO_MSECS(t) (Uint32)((t) / 10)

#endif // TIMER_H
