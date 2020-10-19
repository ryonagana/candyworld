#include "map.h"
#include "csv_parser.h"
#include "ini_parser.h"



void read_config(map_t *map, const char *filepath){

    FILE *conf, *csv;
    const char *map_info = "//map_info.conf";
    char map_path[4096] = {0};


    strncpy(map_path, filepath, strlen(filepath));
    strncat(map_path, map_info, strlen(map_info));

    conf = NULL;
    csv  = NULL;



    if((conf = fopen(map_path, "rb")) == NULL){
        MAPCONV_ERROR("filepath not found - %s", strerror(errno));
        return;
    }

    ini_parse_file(conf, &ini_handler_proc, map);

    fclose(conf);

    memset(map_path, 0, 4096);

    strncpy(map_path, filepath, strlen(filepath));
    strncat(map_path, "\\", 1);
    strncat(map_path, map->layers[0].name, strlen(map->layers[0].name));

    if((csv = fopen(map_path, "rb")) == NULL){
        MAPCONV_ERROR("layer tiles not found!");
        return;
    }

    int *ret =  NULL;

    csv_parse_file(csv, map->width, map->height, (void **)&ret);
    csv_debug_print(ret, map->width, map->height);


}

map_t *map_init(void){
    map_t *mp = NULL;

    mp = calloc(1, sizeof(map_t));
    mp->layers = alloc_layer_num(LAYERS_NUM);

    int i;

    for(i = 0; i < LAYERS_NUM; i++){
        //mp->layers[i] = alloc_map_layer()
    }

    return mp;
}

 map_layer* alloc_layer_num(int num){
    map_layer *l_tmp = NULL;

    l_tmp = calloc(num, sizeof(map_layer));

    if(!l_tmp){
        MAPCONV_ERROR("Error Trying to Allocate  %d map layers", num);
        return l_tmp;
    }
    return l_tmp;
}

map_layer * alloc_map_layer(int rows, int cols){
        map_layer *mp = NULL;
        mp = malloc(sizeof (map_layer));
        mp->flags = 0;
        mp->layer = malloc(sizeof(int) * rows * cols );
        return mp;


}
