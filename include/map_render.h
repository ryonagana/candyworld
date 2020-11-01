#ifndef MAP_RENDER_H
#define MAP_RENDER_H
#include "map.h"
#include "SDL2/SDL.h"


int map_getgid(map_t *map, int gid);
void map_render(map_t *map, int x, int y);
int map_get_tile(map_t *map, int layer, int x, int y);
int map_render_tile(map_t *map, const char *tileset_name);

#endif // MAP_RENDER_H
