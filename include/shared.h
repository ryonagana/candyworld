#ifndef SHARED_HEADER
#define SHARED_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "list.h"



#define UNUSED(v) ((void)v)


void read_sprite_list(FILE *fp, SDL_Texture *texture,  link_list_t **animation);


#endif
