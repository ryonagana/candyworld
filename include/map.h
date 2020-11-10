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
#define MAPCONV_LOG(x,...) fprintf(stdout, x"\n", ##__VA_ARGS__)

#define LAYER_TILES 0
#define LAYER_BACKGROUND 1
#define LAYERS_NUM 2


#define MAP_FORMAT ".cbmap"
#define MAP_VERSION 2
#define MAP_MAX_TILES 200
#define MAP_NAME_BUFFER 127
#define MAP_FILENAME_BUFFER 255

typedef struct map_tile_t {
    int32_t id;
    int32_t region_x;
    int32_t region_y;
    int32_t x;
    int32_t y;
    int32_t flags;
}map_tile_t;


typedef struct map_layer {
    char name[127];
    int *layer;
    map_tile_t tiles[MAP_MAX_TILES][MAP_MAX_TILES];
    int flags;
}map_layer;




typedef struct map_tileset {
    char name[MAP_NAME_BUFFER];
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
    char header[6];
    char name[MAP_NAME_BUFFER];
    char filename[MAP_FILENAME_BUFFER];
    int32_t width;
    int32_t height;
    int tileset_count;
    int map_version;
}map_t;



int map_load_str_csv(map_t *map, const char *filepath);
map_t *map_init(void);
void map_free(map_t** map_ptr);
map_layer *map_alloc_layer_num(int num);
map_layer *alloc_map_layer(int rows, int cols);
map_tileset *map_tileset_alloc_mem(int num);
void map_tileset_free(map_tileset **ts);

void map_save_name(map_t *map, const char *output_filename);
void map_save_file(FILE *fp, map_t *map);


int map_load_stream(map_t** map, FILE *in);
map_t* map_load_file_str(const char *filepath);
//void map_load_file(map_t **map, )
int map_getgid(map_t *map, int gid);

void map_convert_1d_to_2d(map_t **map);

void map_show_info(map_t *map);


#endif // MAP_H
