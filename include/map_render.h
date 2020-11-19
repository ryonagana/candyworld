#ifndef MAP_RENDER_H
#define MAP_RENDER_H
#include "map.h"
#include "SDL2/SDL.h"


void map_render_init();
void map_render_end();
void map_render(map_t *map, int x, int y);
map_tile_t map_get_tile(map_t *map, int layer, int x, int y);
int map_render_tile(map_t *map, const char *tileset_name);
int map_get_tile_1d(map_t *map, int layer, int width, int x, int y);

#endif // MAP_RENDER_H
