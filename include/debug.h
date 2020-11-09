#ifndef DEBUG_H
#define DEBUG_H
#include "player.h"

void debug_start();
void debug_end();


void debug_render_player_hitbox(player_t *pl);
void debug_player_info(player_t *pl);
#endif // DEBUG_H
