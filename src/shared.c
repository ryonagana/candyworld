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

void game_rect_empty(game_rect_t *r)
{
    r->bottom = 0;
    r->left = 0;
    r->rect.h = 0;
    r->rect.w = 0;
    r->rect.x = 0;
    r->rect.y = 0;
    r->right = 0;
    r->top =0;
}

void game_rect_start(game_rect_t *r, int x, int y, int w, int h)
{
    r->rect.x = (int)x;
    r->rect.y = (int)y;
    r->rect.w = (int)w;
    r->rect.h = (int)h;

    game_rect_update_rect(r);
}

void game_rect_update_rect(game_rect_t *r)
{
    r->left   = (int)r->rect.x;
    r->right  = (int)r->rect.x + r->rect.w;
    r->top    = (int)r->rect.y;
    r->bottom = (int)r->rect.y + r->rect.h;
}

void game_rect_start_SDL(game_rect_t *r, SDL_Rect *rect)
{
    game_rect_start(r, rect->x, rect->y, rect->w, rect->h);
    game_rect_update_rect(r);
}
