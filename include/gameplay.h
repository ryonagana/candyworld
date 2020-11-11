#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "game.h"



extern game_event_t  main_game_event;

void gameplay_start(game_data_t *gamedata);
void gameplay_end(game_data_t *gamedata);

void gameplay_event_loop(game_event_data *e, void* data);


#endif // GAMEPLAY_H
