#include "shared.h"
#include "log.h"

void read_sprite_list(FILE *fp, SDL_Texture *texture,  link_list_t **animation)
{
    if(fp == NULL){
        DCRITICAL("sprite_list is NULL");
        return;
    }

    static int frame_counter = 0;
    link_list_t *anim_tmp = *animation;

    char buf[1024] = {0};
    int x, y;
    int width, height;
    int flip;

    x = y = width = height = flip = 0;

    while(fscanf(fp, "%s %d %d %d %d %d", buf, &x, &y, &width, &height, &flip) == 6){

    }
}
