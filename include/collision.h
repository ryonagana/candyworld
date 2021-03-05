#ifndef COLLISION_H
#define COLLISION_H
#include <SDL2/SDL.h>
#include "map.h"
#include "player.h"
#include "shared.h"


int collision_bounding_box(int a_x, int a_y, int a_w, int a_h, int b_x, int b_y, int b_w, int b_h);
int collision_SDL_bounding_boxes(SDL_Rect *a, SDL_Rect *b);
int collision_game_rect_bounding_boxes(game_rect *a, game_rect *b);
int collision_player_detect_hit3(game_rect *hitbox, map_t *map, game_rect *out);

#endif // COLLISION_H
