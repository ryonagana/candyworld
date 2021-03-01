#include "collision.h"
#include "tiles.h"


int collision_bounding_box(int a_x, int a_y, int a_w, int a_h, int b_x, int b_y, int b_w, int b_h){


    game_rect_t a, b;

    game_rect_start(&a, a_x, a_y, a_w, a_h);
    game_rect_start(&b, b_x, b_y, b_w, b_h);
    game_rect_update_rect(&a);
    game_rect_update_rect(&b);

    if(b.left < a.left + a.pos.w ||
       b.left + b.pos.w > b.left  ||
       b.top < a.top + a.pos.h ||
       b.top + b.pos.h > a.top)
    {
        return 1;
    }

    return 0;

}

int collision_SDL_bounding_boxes(SDL_Rect *a, SDL_Rect *b){
    return collision_bounding_box(a->x,a->y,a->w,a->h,b->x,b->y,b->w,b->h);
}

int collision_game_rect_bounding_boxes(game_rect_t *a, game_rect_t *b){
    return collision_bounding_box(a->pos.x,a->pos.y,a->pos.w,a->pos.h,b->pos.x,b->pos.y,b->pos.w,b->pos.h);
}

int collision_player_detect_hit(game_rect_t *object_rect, map_t *map, game_rect_t *out)
{


    map_tileset *tileset =  &map->tilesets[0];
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

        SDL_bool collision =  SDL_HasIntersection(&player_rect, &tile_rect);

        if(collision){
            game_rect_start(&r, tile_rect.x * tile_rect.w, tile_rect.y * tile_rect.h, tile_rect.w, tile_rect.h);
            *out = r;
            return 1;
        }

    }

    return 0;


}
