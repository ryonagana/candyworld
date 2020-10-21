#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef __GNUC__
#include <errno.h>
#endif




#define MAPCONV_ERROR(x,...) fprintf(stderr, x"\n", ##__VA_ARGS__)

#define LAYER_TILES 0
#define LAYER_BACKGROUND 1

#define LAYERS_NUM 2

#define MAP_FORMAT ".cbmap"

typedef struct map_layer {
    char name[127];
    int *layer;
    int flags;
}map_layer;


typedef struct map_tileset {
    char name[127];
    int tile_width;
    int tile_height;
    int first_gid;
    int width;
    int height;
}map_tileset;


typedef struct map_t {
    map_layer   *layers;
    map_tileset *tilesets;
    char name[127];
    int width;
    int height;
}map_t;



int map_read_config(map_t *map, const char *filepath);
map_t *map_init(void);
void map_free(map_t** map_ptr);
map_layer *alloc_layer_num(int num);
map_layer *alloc_map_layer(int rows, int cols);


void map_save_file(map_t *map, const char *output_filename);

#endif // MAP_H
