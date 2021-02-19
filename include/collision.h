#ifndef COLLISION_H
#define COLLISION_H
#include <SDL2/SDL.h>
#include "map.h"
#include "player.h"

int is_overlap(int a_x, int a_y, int a_w, int a_h, int b_x, int b_y, int b_w, int b_h);
int is_colliding(SDL_Rect a, SDL_Rect b);


int collision_test(player_t *player, map_tile_t *tile);

#endif // COLLISION_H
