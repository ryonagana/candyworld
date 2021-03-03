#include "collision.h"
#include "tiles.h"


int collision_bounding_box(int a_x, int a_y, int a_w, int a_h, int b_x, int b_y, int b_w, int b_h){


    game_rect_t a, b;

    game_rect_start(&a, a_x, a_y, a_w, a_h);
    game_rect_start(&b, b_x, b_y, b_w, b_h);
    game_rect_update_rect(&a);
    game_rect_update_rect(&b);

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

int collision_game_rect_bounding_boxes(game_rect_t *a, game_rect_t *b){
    return collision_bounding_box(a->pos.x,a->pos.y,a->pos.w,a->pos.h,b->pos.x,b->pos.y,b->pos.w,b->pos.h);
}



int collision_player_detect_hit(game_rect_t *object_rect, map_t *map, game_rect_t *out)
{


    map_tileset_t *tileset =  &map->tilesets[0];
    static game_rect_t r;


    int tile_x =    object_rect->pos.x / tileset->tile_width;
    int tile_y =    object_rect->pos.y / tileset->tile_height;


    if(map->layers[LAYER_COLLISION].tiles[tile_y][tile_x].id == COLLISION_TILE){



        SDL_Rect player_rect = {
                            object_rect->pos.x / tileset->tile_width,
                            object_rect->pos.y / tileset->tile_height,
                            tileset->tile_width,
                            tileset->tile_height
                            };

        SDL_Rect tile_rect = { tile_x,
                               tile_y,
                               tileset->tile_width,
                               tileset->tile_height
                             };

        //SDL_bool collision =  SDL_HasIntersection(&player_rect, &tile_rect);
        int collision = collision_SDL_bounding_boxes(&player_rect, &tile_rect);

        if(collision){
            game_rect_start(&r, tile_x * tileset->tile_width, tile_y * tileset->tile_height, player_rect.w, player_rect.h);
            *out = r;
            return 1;
        }

    }

    return 0;


}

int collision_player_detect_hit2(game_rect_t *object_rect,game_rect_t *hitbox_rect, map_t *map, game_rect_t *out){

    map_tileset_t *tileset =  &map->tilesets[0];



    int tile_x =    object_rect->pos.x / tileset->tile_width;
    int tile_y =    object_rect->pos.y / tileset->tile_height;


    if(map->layers[LAYER_COLLISION].tiles[tile_y][tile_x].id == COLLISION_TILE){

         SDL_Rect player_rect = {
                             object_rect->pos.x / tileset->tile_width,
                             object_rect->pos.y / tileset->tile_height,
                             hitbox_rect->pos.w,
                             hitbox_rect->pos.h
                             };

         SDL_Rect tile_rect = { tile_x,
                                tile_y,
                                hitbox_rect->pos.w,
                                hitbox_rect->pos.h
                              };

     if( collision_SDL_bounding_boxes(&player_rect, &tile_rect) ){
            game_rect_t r;
            game_rect_start(&r, tile_x * tileset->tile_width, tile_y * tileset->tile_height, 32,32);
            *out = r;
            return 1;

     }

    }


    return 0;


}
