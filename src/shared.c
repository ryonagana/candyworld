#include "shared.h"
#include "log.h"



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

void grect_start2(game_rect **r, int x, int y, int w, int h)
{
    game_rect *tmp = *r;

    tmp->pos.x = x;
    tmp->pos.y = y;
    tmp->pos.w = w;
    tmp->pos.h = h;
    grect_refresh(tmp);
}
