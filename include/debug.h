#ifndef DEBUG_H
#define DEBUG_H
#include "player.h"
#include "camera.h"
#include "map.h"

void debug_start(void);
void debug_end(void);


void debug_render_player_hitbox(player_t *pl);
//void debug_player_info(player_t *pl);


void debug_camera_render(camera *c);
#endif // DEBUG_H
