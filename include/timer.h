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
    Uint32 start_time;
    Uint32 pause_ticks;
    Uint32 flags;
}game_timer_t;


void timer_init(game_timer_t *tm);
void timer_set_start(game_timer_t *tm);
void timer_set_stop(game_timer_t *tm);
void timer_set_pause(game_timer_t *tm);
int  timer_is_started(game_timer_t *tm);
int  timer_is_paused(game_timer_t *tm);
Uint32 timer_get_ticks(game_timer_t *tm);
Uint32 timer_frame_cap(game_timer_t *tm);

#define TIMER_TICKS_TO_SECS(t) (Uint32)((t) / 1000)
//#define TIMER_TICKS_TO_MSECS(t) (Uint32)((t) / 10)

#endif // TIMER_H
