#include "collision.h"

int is_overlap(int a_x, int a_y, int a_w, int a_h, int b_x, int b_y, int b_w, int b_h)
{

    int a_top, a_left, a_right, a_bottom;
    int b_top, b_left, b_right, b_bottom;

    a_top = a_y;
    a_left = a_x;
    a_right = a_x + a_w;
    a_bottom = a_top + a_h;


    b_top = b_y;
    b_left = b_x;
    b_right = b_x + b_w;
    b_bottom = b_top + b_h;


    if(a_bottom <= b_top){
        return 0;
    }

    if(a_top >= b_bottom){
        return 0;
    }

    if(a_right <= b_left){
        return 0;
    }

    if(a_left >= b_right){
        return 0;
    }

    return 1;
}

int is_colliding(SDL_Rect a, SDL_Rect b)
{
    return is_overlap(a.x,a.y,a.w,a.h,b.x,b.y,b.w,b.h);
}

int collision_test(player_t *player, map_tile_t *tile)
{

}
