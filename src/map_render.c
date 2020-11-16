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

    const int map_render_order[] = {
        LAYER_BACKGROUND,
        LAYER_TILES
    };

    map_tileset_texture = resources_sprite_get_by_filename(map->tilesets[0].name);

    Uint32 pixelformat = 0;
    SDL_QueryTexture(map_tileset_texture,&pixelformat, NULL, NULL, NULL);
    //SDL_Texture *map_texture = SDL_CreateTexture(window_get()->events.renderer, pixelformat, SDL_TEXTUREACCESS_TARGET, window_get()->info.width, window_get()->info.height);



    //SDL_SetRenderTarget(window_get()->events.renderer, map_texture);
    int layer_count;

    for(layer_count = 0; layer_count < LAYERS_NUM; layer_count++){
        //if(map_render_order[layer_count] == 0) continue;
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

     //SDL_SetRenderTarget(window_get()->events.renderer, NULL);
     //SDL_RenderCopy(window_get()->events.renderer, map_texture, &(SDL_Rect){0,0,window_get()->info.width, window_get()->info.height }, &(SDL_Rect){0,0,window_get()->info.width, window_get()->info.height });
     //SDL_DestroyTexture(map_texture);
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


