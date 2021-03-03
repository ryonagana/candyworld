#ifndef COLLISION_H
#define COLLISION_H
#include <SDL2/SDL.h>
#include "map.h"
#include "player.h"
#include "shared.h"

int collision_player_detect_hit(game_rect_t *object_rect, map_t *map, game_rect_t *out);
int collision_bounding_box(int a_x, int a_y, int a_w, int a_h, int b_x, int b_y, int b_w, int b_h);
int collision_SDL_bounding_boxes(SDL_Rect *a, SDL_Rect *b);
int collision_game_rect_bounding_boxes(game_rect_t *a, game_rect_t *b);
int collision_player_detect_hit2(game_rect_t *object_rect,game_rect_t *hitbox_rect, map_t *map, game_rect_t *out);
#endif // COLLISION_H
