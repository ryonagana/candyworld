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


int collision_player_detect_hit3(game_rect *object_rect, game_rect *hitbox, map_t *map, game_rect *out)
{
    map_tileset_t *ts =  &map->tilesets[0];
    int tile_x, tile_y;


    game_rect r;
    grect_empty(&r);

    tile_x = object_rect->pos.x / ts->tile_width;
    tile_y = object_rect->pos.y / ts->tile_height;

    map_layer_t *layer = &map->layers[LAYER_COLLISION];





    if(layer->tiles[tile_y][tile_x].id == COLLISION_TILE ||
       layer->tiles[tile_y][object_rect->pos.x + object_rect->pos.w / ts->tile_width].id == COLLISION_TILE ||
       layer->tiles[(object_rect->pos.y + object_rect->pos.h) / ts->tile_height][tile_x].id == COLLISION_TILE ||
       layer->tiles[(object_rect->pos.y + object_rect->pos.h) / ts->tile_width][(object_rect->pos.x + object_rect->pos.w) / ts->tile_height].id == COLLISION_TILE )
    {

        grect_start(&r, (object_rect->pos.x + object_rect->pos.x / ts->tile_width) * ts->tile_width,
                            (object_rect->pos.y + object_rect->pos.h / hitbox->pos.w)  * ts->tile_height,
                            hitbox->pos.w,
                            hitbox->pos.h);

        *out  = r;
        return 1;
    }


    return 0;



}
