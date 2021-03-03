#ifndef SHARED_HEADER
#define SHARED_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "list.h"



#define UNUSED(v) ((void)v)
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


void read_sprite_list(FILE *fp, SDL_Texture *texture,  link_list_t **animation);


typedef struct game_rect {
    SDL_Rect pos;
    int top;
    int bottom;
    int left;
    int right;
}game_rect;

void grect_empty(game_rect *r);
void grect_start(game_rect *r, int x, int y, int w, int h);
void grect_start_SDL(game_rect *r, SDL_Rect *rect);
void grect_refresh(game_rect *r);
#endif
