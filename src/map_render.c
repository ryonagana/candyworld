#include "map_render.h"
#include "resources.h"
#include "render.h"
#include "window.h"
/*
 * map_render()
 * renders the map to the screen using double buffer
 *
 * */

static text_t *debug_render_font = NULL;
static SDL_Texture *map_tileset_texture = NULL;

void map_render_init()
{


    text_init_font(&debug_render_font, "debug_ttf", 16, 0);



}

void map_render_end()
{

    text_destroy(&debug_render_font);

}



void map_render(map_t *map)
{


    int x,y;

    int map_render_order[2] = {
        LAYER_BACKGROUND,
        LAYER_TILES,
    };

    map_tileset_texture = resources_sprite_get_by_filename(map->tilesets[0].name);

    Uint32 pixelformat = 0;
    SDL_QueryTexture(map_tileset_texture,&pixelformat, NULL, NULL, NULL);
    SDL_Texture *map_texture = SDL_CreateTexture(window_get()->events.renderer, pixelformat, SDL_TEXTUREACCESS_TARGET, window_get()->info.width, window_get()->info.height);



    SDL_SetRenderTarget(window_get()->events.renderer, map_texture);
    int layer_count;

    for(layer_count = 0; layer_count < LAYERS_NUM; layer_count++){
        for(y = 0;  y < map->height; y++){
            for(x = 0; x < map->width; x++){
                    map_tile_t tile = map_get_tile(map, map_render_order[layer_count] , x,y);
                    int gid = map_getgid(map, tile.id);

                    if(gid == -1) continue;

                    render_texture(map_tileset_texture,
                                   tile.region_x,
                                   tile.region_y,
                                   map->tilesets[0].tile_width,
                                   map->tilesets[0].tile_height,
                                   tile.x,
                                   tile.y,
                                   map->tilesets[0].tile_width * MAP_SCALE,
                                   map->tilesets[0].tile_height * MAP_SCALE,
                                   0,
                                   SDL_FLIP_NONE
                    );




            }
        }
    }

     SDL_SetRenderTarget(window_get()->events.renderer, NULL);
     SDL_RenderCopy(window_get()->events.renderer, map_texture, &(SDL_Rect){0,0,window_get()->info.width, window_get()->info.height }, &(SDL_Rect){0,0,window_get()->info.width, window_get()->info.height });


/*
    int tx,ty, layer;
    SDL_Texture* map_asset =   resources_sprite_get_by_filename(map->tilesets[0].name);

    for(layer = 0; layer < LAYERS_NUM; layer++){
        for(ty = 0; ty < map->height; ty++){
            for(tx = 0; tx < map->width; tx++){
                map_tile_t tile = map_get_tile(map, layer, x,y);


                //text_draw(debug_render_font, tx *  map->tilesets[0].tile_width, ty *  map->tilesets[0].tile_height, (SDL_Color) {255,255,255,255}, " %d ", tile.id);
                render_texture(map_asset,
                             x *  map->tilesets[0].tile_width,
                             y *  map->tilesets[0].tile_height,
                               map->tilesets[0].tile_width,
                               map->tilesets[0].tile_height,
                               tile.region_x,
                               tile.region_y,
                               map->tilesets[0].tile_width,
                               map->tilesets[0].tile_height,
                               0,
                               SDL_FLIP_NONE
                );




            }
        }
    }
    */








/*

    int tx,ty;
    int layer;


    SDL_Texture* map_asset =   resources_sprite_get_by_filename(map->tilesets[0].name);

    for(layer = 0; layer < LAYERS_NUM; layer++){
        if( &(map->layers[layer]) == NULL) continue;

        for(ty = 0; ty < map->height; ty++){
            for(tx = 0; tx < map->width; tx++){
               int tile_id = map_get_tile(map, layer, tx,ty);  // map->layers[layer].layer[ty * map->height + tx];
               int gid = map_getgid(map, tile_id);

               int rx = (gid % (map->tilesets[0].width / map->tilesets->tile_width)) * map->tilesets[0].tile_width;
               int ry = (gid / (map->tilesets[0].height / map->tilesets->tile_height)) * map->tilesets[0].tile_height;
               //int ry;

                render_texture(map_asset,
                              (tx * map->tilesets[0].width)   + x * map->tilesets[0].width,
                              (ty * map->tilesets[0].height)  + y * map->tilesets[0].height,
                               map->tilesets[0].width,
                               map->tilesets[0].height,
                               rx,
                               ry,
                               map->tilesets[0].width,
                               map->tilesets[0].height,
                               0,
                               SDL_FLIP_NONE
                );





            }
        }
    }


    */
}


/*
 *  map_render_tile
 *
 * render a single map through tilesheet
 * using tiled mode
 *
 * */
int map_render_tile(map_t *map, const char *tileset_name)
{
    if(!map->tilesets) return 0;

    int i;
    SDL_Texture *tex = NULL;

    for(i = 0; i < map->tileset_count; i++){
        tex = resources_sprite_get(tileset_name, RESOURCE_EXTENSION_ANY);
    }

    if(!tex){
        return 0;
    }


    return 1;

}

/*
 * this function is needed to normalize tilesetes loaded from map
 * and find right tile before render on screen
 * based on tiled docs
 *
 * return the gid (graphic id) from tileset
 */


/*
 * get tile from the pointer
 * */
map_tile_t map_get_tile(map_t *map, int layer, int x, int y)
{
    return map->layers[layer].tiles[y][x];
}


