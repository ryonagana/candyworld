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
    int loaded;
    int rows;
    int cols;
}map_tileset;


typedef struct map_t {
    map_layer   *layers;
    map_tileset *tilesets;
    char name[127];
    char filename[255];
    int width;
    int height;
    int tileset_count;
}map_t;



int map_load_str(map_t *map, const char *filepath);
map_t *map_init(void);
void map_free(map_t** map_ptr);
map_layer *alloc_layer_num(int num);
map_layer *alloc_map_layer(int rows, int cols);
map_tileset *map_tileset_alloc_mem(int num);
void map_tileset_free(map_tileset **ts);

void map_save_name(map_t *map, const char *output_filename);
void map_save_file(FILE *fp, map_t *map);
//void map_load_file(map_t **map, )

#endif // MAP_H
