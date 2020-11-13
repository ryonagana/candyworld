#ifndef GAME_HEADER
#define GAME_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "window.h"
#include "player.h"
#include "map.h"
#include "map_render.h"


/*
#include "hud.h"
#include "lua_shared.h"
#include "lua_hud.h"
#include "lua_vm.h"
#include "resources.h"
#include "thread.h"
#include "sound.h"
*/

#define GAME_LOGOS_STATE      0
#define GAME_MENU_STATE       1
#define GAME_OPTIONS          2
#define GAME_INGAME_STATE     3
#define GAME_GAMEOVER_STATE   4


#define MAX_GAME_EVENTS 32

typedef struct game_event_data {
        void *data1;
        void *data2;
}game_event_data;

typedef void (*game_event_callback)(game_event_data *e, void *data);


typedef struct game_event_t {
    game_event_callback callback;
}game_event_t;


typedef struct game_data_t {
    int64_t timer_count;
    player_t player;
    int  transition_state;
    int redraw_frame;
    map_t *map;
    game_event_t  current_event;
    int gamestate;
}game_data_t;


void game_init();
void game_end();
void game_start();






#endif
