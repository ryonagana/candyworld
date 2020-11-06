#include "map_render.h"
#include "resources.h"
#include "render.h"

/*
 * map_render()
 * renders the map to the screen using double buffer
 *
 * */
void map_render(map_t *map, int x, int y)
{
    int tx,ty;
    int layer;

    SDL_Texture* map_asset =   resources_sprite_get_by_filename(map->tilesets[0].name);

    for(layer = 0; layer < LAYERS_NUM; layer++){
        if( &(map->layers[layer]) == NULL) continue;

        for(ty = 0; ty < map->height; ty++){
            for(tx = 0; tx < map->width; tx++){
               int tile_id = map->layers[layer].layer[ty * map->height + tx];
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

int map_getgid(map_t *map, int gid)
{

    int cur_gid = gid;
    int tileset_gid = -1;

    int c;
    for(c = 0; c < map->tileset_count; c++){

        if(tileset_gid <= cur_gid){
            tileset_gid = map->tilesets[c].first_gid;
        }
    }

    if(tileset_gid == -1 ) return tileset_gid;

    return cur_gid -= tileset_gid;
}

/*
 * get tile from the pointer
 * */
int map_get_tile(map_t *map, int layer, int x, int y)
{
    int is_rect = map->width > map->height ? 1 : 0;

    if(is_rect){
        return map->layers[layer].layer[y * map->height+ x];
    }

    return map->layers[layer].layer[x * map->width + y];
}
