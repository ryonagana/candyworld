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
#define LAYER_COLLISION  2




#define LAYERS_NUM 3


#define MAP_FORMAT ".cbmap"
#define MAP_VERSION 3
#define MAP_MAX_TILES 300
#define MAP_NAME_BUFFER 127
#define MAP_FILENAME_BUFFER 255
#define MAP_SCALE 2.0f



typedef struct map_tile_t {
    int32_t id;
    int32_t region_x;
    int32_t region_y;
    int32_t x;
    int32_t y;
    int32_t width;
    int32_t height;
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
    int64_t map_size;
}map_t;



/*
 * load the MAP in CSV to the memory
 * each CSV is a layer
*/
int map_load_str_csv(map_t *map, const char *filepath);

//init a zero'd map
map_t *map_init(void);

//free map ptr from the memory
void map_free(map_t** map_ptr);

//alloc the number of layers in map
map_layer *map_alloc_layer_num(int num);

/* alloc the size of map for each layer */
map_layer *alloc_map_layer(int rows, int cols);

/* alloc the number of tilesets of map (tiled can allow multiples tilesets for one map)  */
/* PS need to fix the ini reader to find more than 1 tileset */
map_tileset *map_tileset_alloc_mem(int num);

// frees the tileset ptr
void map_tileset_free(map_tileset **ts);

//save the map from the struct to a binary file
void map_save_name(map_t *map, const char *output_filename);

//save file map directly to a file stream
void map_save_file(FILE *fp, map_t *map);

// loads a map from file to mmemory
int map_load_stream(map_t** map, FILE *in);

// loads a map from filename (file must exists) returns a ptr
map_t* map_load_file_str(const char *filepath);
//void map_load_file(map_t **map, )

// get tiled map gid to get the right tile for the loaded map
int map_getgid(map_t *map, int gid);

// convert a 1d map to 2d array
void map_convert_1d_to_2d(map_t **map);

// show map information (for debug only or mapconverter tool)
void map_show_info(map_t *map);

int64_t map_size_bytes(FILE *fp);



// generate tilesed ID
void  map_generate_tilesets(map_t *t, const char *output);



#endif // MAP_H
