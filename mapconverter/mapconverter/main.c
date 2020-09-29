#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <allegro5/allegro.h>



#define MAPCONV_ERROR(x,...) fprintf(stderr, x"\n", ##__VA_ARGS__)


#define LAYERS_NUM 3

typedef struct map_layer {
    int **layer;
    int flags;
}map_layer;


typedef struct map {
    map_layer *layers;
    char name[56];
    int width;
    int height;
    int tile_width;
    int tile_height;
    int rows;
    int cols;
}map;


static map_layer* alloc_mem_layers(int num);
static map_layer ** alloc_map_layer(int rows, int cols);

static void read_config(map *map, const char *filepath){
    ALLEGRO_CONFIG *cfg = NULL;
    ALLEGRO_PATH *path = NULL;

    char map_info[4096] = {0};

    strncpy(map_info, filepath, 4096);
    strncat(map_info, "//map_info.conf", 20);


    path = al_create_path(filepath);

    if(map == NULL){
        MAPCONV_ERROR("error map is not correctly loaded1");
        return;
    }

    cfg = al_load_config_file(map_info);

    if(cfg == NULL){
        MAPCONV_ERROR("cfg cannot be loaded!");
        return;
    }
    //map->name =
    strcpy(map->name, al_get_config_value(cfg, "map", "name"));
    map->width = atoi(al_get_config_value(cfg, "map", "width"));
    map->height = atoi(al_get_config_value(cfg, "map", "height"));

    const char *tiles_layer = al_get_config_value(cfg, "map", "tiles_layer");
    const char *bg_layer    = al_get_config_value(cfg, "map", "bg_layer");

    //todo load layers

    al_destroy_config(cfg);
    al_destroy_path(path);

}

map *map_init(void){
    map *mp = NULL;

    mp = calloc(1, sizeof(map));
    mp->layers = alloc_mem_layers(LAYERS_NUM);

    int i;

    for(i = 0; i < LAYERS_NUM; i++){
        //mp->layers[i] = alloc_map_layer()
    }

    return mp;
}

static map_layer* alloc_mem_layers(int num){
    map_layer *l_tmp = NULL;

    l_tmp = calloc(num, sizeof(map_layer));

    if(!l_tmp){
        MAPCONV_ERROR("Error Trying to Allocate  %d map layers", num);
        return NULL;
    }
    return l_tmp;
}

static map_layer ** alloc_map_layer(int rows, int cols){
        int i;
        map_layer **layer = NULL;

        layer = calloc(cols, sizeof (map_layer*));

        for(i = 0;i < rows; i++){
            layer[i] = calloc(rows, sizeof(map_layer*));
        }

       return layer;
}


int main()
{

    map* root = NULL;

    root = map_init();
    read_config(root, "test");

    return 0;
}
