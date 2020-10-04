#ifndef GAME_HEADER
#define GAME_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "window.h"
#include "hud.h"
#include "lua_shared.h"
#include "lua_hud.h"
#include "lua_vm.h"
#include "resources.h"
#include "player.h"
#include "thread.h"
#include "sound.h"


#define GAME_LOGOS_STATE  1
#define GAME_INGAME_STATE 2
#define GAME_MENU_STATE   3


typedef struct game_data_t {
    int64_t timer_count;
    player_t player;
    int  transition_state;
    int redraw_frame;
}game_data_t;


void game_init();
void game_end();
void game_start();

void game_loop();


#endif
