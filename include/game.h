#ifndef GAME_HEADER
#define GAME_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>


#define GAME_LOGOS_STATE  1
#define GAME_INGAME_STATE 2
#define GAME_MENU_STATE   3


void game_init();
void game_end();
void game_start();

void main_game_loop();


#endif
