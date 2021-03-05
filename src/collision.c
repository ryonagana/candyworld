#include "collision.h"
#include "tiles.h"
#include "log.h"

int collision_bounding_box(int a_x, int a_y, int a_w, int a_h, int b_x, int b_y, int b_w, int b_h){


    game_rect a, b;

    grect_start(&a, a_x, a_y, a_w, a_h);
    grect_start(&b, b_x, b_y, b_w, b_h);
    grect_refresh(&a);
    grect_refresh(&b);

    if(a.bottom <= b.top){
        return 0;
    }

    if(a.top >= b.bottom){
        return 0;
    }


    if(a.right <= b.left){
        return 0;
    }


    if(a.left >= b.right){
        return 0;
    }

    return 1;

}

int collision_SDL_bounding_boxes(SDL_Rect *a, SDL_Rect *b){
    return collision_bounding_box(a->x,a->y,a->w,a->h,b->x,b->y,b->w,b->h);
}

int collision_game_rect_bounding_boxes(game_rect *a, game_rect *b){
    return collision_bounding_box(a->pos.x,a->pos.y,a->pos.w,a->pos.h,b->pos.x,b->pos.y,b->pos.w,b->pos.h);
}


int collision_player_detect_hit3(game_rect *hitbox, map_t *map, game_rect *out)
{
    map_tileset_t *ts =  &map->tilesets[0];
    int tile_top, tile_left, tile_right, tile_bottom;


    tile_left   = hitbox->pos.x / ts->tile_width;
    tile_right  = (hitbox->pos.x + hitbox->pos.w) / ts->tile_width;
    tile_top    = hitbox->pos.y / ts->tile_height;
    tile_bottom = (hitbox->pos.y + hitbox->pos.h) / ts->tile_height;


    if(tile_left < 0 ) tile_left  = 0;
    if(tile_right > hitbox->pos.w) tile_right = hitbox->pos.w;
    if(tile_top < 0) tile_right  = 0;
    if(tile_bottom > hitbox->pos.h ) tile_bottom = hitbox->pos.h;

    int collision = 0;
    int i,j;
    game_rect r;

     for(j = tile_left; j <= tile_right; j++){
        for(i = tile_top; i <= tile_bottom; i++){
            map_tile_t tile = map->layers[LAYER_COLLISION].tiles[i][j];

            if(tile.id == COLLISION_TILE ){
                collision = 1;
                grect_start(&r, tile.x, tile.y , ts->tile_width, ts->tile_height);
                break;
            }
        }
    }

     *out = r;
    return collision;



}
