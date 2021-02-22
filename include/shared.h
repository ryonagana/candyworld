#ifndef SHARED_HEADER
#define SHARED_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "list.h"



#define UNUSED(v) ((void)v)


void read_sprite_list(FILE *fp, SDL_Texture *texture,  link_list_t **animation);


typedef struct game_rect_t {
    SDL_Rect rect;
    int top;
    int bottom;
    int left;
    int right;
}game_rect_t;

void game_rect_empty(game_rect_t *r);
void game_rect_start(game_rect_t *r, int x, int y, int w, int h);
void game_rect_start_SDL(game_rect_t *r, SDL_Rect *rect);
void game_rect_update_rect(game_rect_t *r);
#endif
