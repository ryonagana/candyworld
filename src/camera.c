#include "camera.h"
#include "window.h"


static  SDL_bool camera_overlap(const SDL_Rect orig, const SDL_Rect dest){

    return SDL_HasIntersection(&orig, &dest);
}

void camera_init(camera *c, int x, int y, int width, int height)
{
    c->pos.x = x;
    c->pos.y = y;
    c->pos.w = width;
    c->pos.h  = height;

    c->area.w = 0;
    c->area.h = 0;
}

void camera_set_area(camera *c, int width, int height)
{
    c->area.w = width;
    c->area.h = height;
}

void camera_set_pos(camera *c, int x, int y)
{
    c->pos.x = x;
    c->pos.y = y;
}

void camera_update(camera *c, int offset_x, int offset_y)
{

    if(!camera_overlap(c->area, c->pos)){
        c->pos.x += offset_x;
        c->pos.y += offset_y;
    }
}

