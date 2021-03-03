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

void grect_empty(game_rect *r)
{
    r->bottom = 0;
    r->left = 0;
    r->pos.h = 0;
    r->pos.w = 0;
    r->pos.x = 0;
    r->pos.y = 0;
    r->right = 0;
    r->top =0;
}

void grect_start(game_rect *r, int x, int y, int w, int h)
{
    r->pos.x = (int)x;
    r->pos.y = (int)y;
    r->pos.w = (int)w;
    r->pos.h = (int)h;

    grect_refresh(r);
}

void grect_refresh(game_rect *r)
{
    r->pos.x = r->pos.x;
    r->pos.y = r->pos.y;
    r->left   = (int)r->pos.x;
    r->right  = (int)r->pos.x + r->pos.w;
    r->top    = (int)r->pos.y;
    r->bottom = (int)r->pos.y + r->pos.h;

}

void grect_start_SDL(game_rect *r, SDL_Rect *rect)
{
    grect_start(r, rect->x, rect->y, rect->w, rect->h);
    grect_refresh(r);
}
