#include "map.h"
#include "csv_parser.h"
#include "ini_parser.h"

#if defined(__WIN32__) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <io.h>
#elif __linux__
#include <fcntl.h>
#include <unistd.h>
#elif __unix__
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#else
#error "Invalid Platform."
#endif

int map_load_layer(map_t *map, int layer, const char *map_path){
    char buf[4096] = {0};
    FILE *fp = NULL;
    int *data = NULL;

    strncpy(buf, map_path, 4096);
    strncat(buf, "//", 1);
    strncat(buf, map->layers[layer].name, 4096);

    if((fp = fopen(buf,"rb")) == NULL){
        goto map_error;
    }


    csv_parse_file(fp, map->width, map->height, (void**)&data);

    map->layers[layer].layer = calloc(map->width * map->height + 1, sizeof(int));

    memcpy(map->layers[layer].layer, data, (sizeof(int) * map->width * map->height) + 1);
    free(data);
    data = NULL;

    if(!map->layers[layer].layer){
        MAPCONV_ERROR("map data is corrupt");
        return -1;
    }

    return 0;


 map_error:
    MAPCONV_ERROR("map data is corrupt");
    fclose(fp);
    return -1;



}

int map_read_config(map_t *map, const char *filepath){

    FILE *conf;
    const char *map_info = "//map_info.conf";
    char map_path[4096] = {0};


    strncpy(map_path, filepath, strlen(filepath));
    strncat(map_path, map_info, strlen(map_info));

    conf = NULL;



    if((conf = fopen(map_path, "rb")) == NULL){
        MAPCONV_ERROR("filepath not found - %s", strerror(errno));
        return -1;
    }

    ini_parse_file(conf, &ini_handler_proc, map);
    fclose(conf);



    if(map_load_layer(map, LAYER_TILES, filepath) < 0){
        MAPCONV_ERROR("layer tiles not found");
        return -1;
    }

    if(map_load_layer(map, LAYER_BACKGROUND, filepath) < 0){
        MAPCONV_ERROR("background tiles not found");
        return -1;
    }



    map_save_file(map, filepath);


    return 0;


}

map_t *map_init(void){
    map_t *mp = NULL;

    mp = calloc(1, sizeof(map_t));
    mp->layers = alloc_layer_num(LAYERS_NUM);
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

void map_save_file(map_t *map, const char *output_filename)
{

    char name[56] = {0};
    FILE *out = NULL;

    strncpy(name, output_filename,56);
    strcat(name, ".cbmap");

    if((out = fopen(name, "wb")) == NULL){
        fclose(out);
        MAPCONV_ERROR("invalid file creation");
        return;
    }

    fwrite("CBMAP\n", 6,1,out);
    fwrite(map->name, strlen(map->name), 1, out);
    fputc(map->width, out);
    fputc(map->height, out);

    int i;
    for(i = 0; i < LAYERS_NUM; i++){
        fwrite(map->layers[i].layer, map->width * map->height + 1, 1, out);
    }


    fclose(out);

    fprintf(stdout, "map: %s is written to file", name);



}
