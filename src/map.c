#if !defined(MAPCONV_PROJECT)
#include "map.h"
#else
#include "../include/map.h"
#endif

#include "../mapconverter/csv_parser.h"
#include "../mapconverter/ini.h"
#include "../mapconverter/ini_parser.h"

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

#if defined (WIN32) || defined(_WIN32) || (__WIN32__)
#include <windows.h>
#include <tchar.h>
#include <wchar.h>
#include <mbstring.h>
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

int map_load_str(map_t *map, const char *filepath){

    FILE *conf;
    conf = NULL;



#if defined (WIN32) || defined(_WIN32) || (__WIN32__)
    const wchar_t info_path[] = L"//map_info.conf";
    wchar_t map_path[4096] = {0};
    mbstowcs(map_path, filepath, 4096 - 1);
    _tcsncat(map_path,info_path, 4096 - 1);



    if((conf = _wfopen(map_path, L"rb+")) == NULL){
         MAPCONV_ERROR("filepath not found - %s", strerror(errno));
         return -1;
    }


#elif defined(__linux__)

    const char *map_info = "//map_info.conf";
    char map_path[4096] = {0};


    strncpy(map_path, filepath, strlen(filepath) - 1);
    strncat(map_path, map_info, strlen(map_info) - 1);

    if((conf = fopen(map_path, "rb")) == NULL){
        MAPCONV_ERROR("filepath not found - %s", strerror(errno));
        return -1;
    }


#endif


    map->tilesets = map_tileset_alloc_mem(1);
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



    if(map->tilesets == NULL){
        MAPCONV_ERROR("tileset not found");
        return -1;
    }

    return 0;
}

map_t *map_init(void){
    map_t *mp = NULL;

    mp = calloc(1, sizeof(map_t));
    mp->layers = alloc_layer_num(LAYERS_NUM);
    mp->tilesets = calloc(1, sizeof(map_tileset));
    //mp->name = "";
    mp->width = 0;
    mp->height = 0;
    mp->tileset_count = 0;
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

void map_save_name(map_t *map, const char *output_filename)
{

    char name[56] = {0};
    FILE *out = NULL;

    strncpy(name, output_filename,56);
    strcat(name, MAP_FORMAT);

    if((out = fopen(name, "wb+")) == NULL){
        fclose(out);
        MAPCONV_ERROR("invalid file creation");
        return;
    }

    strncpy(map->filename, name, 56 - 1);
    map_save_file(out, map);

}

void map_free(map_t **map_ptr)
{
    int i;

    map_t *map = *map_ptr;

    if(map == NULL) return;

    for(i = 0; i < LAYERS_NUM; i++){

        if(map->layers[i].layer != NULL){
            free(map->layers[i].layer);
            map->layers[i].layer = NULL;
        }

    }

    if(map->layers != NULL){
        free(map->layers);
        map->layers = NULL;
    }

    if(map->tilesets != NULL){
        map_tileset_free(&map->tilesets);
    }


    free(map);
    map = NULL;
    *map_ptr = map;


}

map_tileset *map_tileset_alloc_mem(int num)
{
    map_tileset *tmp = NULL;
    tmp = calloc(num + 1, sizeof (map_tileset));
    return tmp;
}

void map_tileset_free(map_tileset **ts)
{
    map_tileset *tmp = NULL;

    if((*ts) == NULL){
        return;
    }

    tmp = *ts;
    free(tmp);
    tmp = NULL;
    *ts = tmp;
}

void map_save_file(FILE *fp, map_t *map)
{

    if(fp == NULL){
        MAPCONV_ERROR("invalid file creation");
        return;
    }

    fwrite("CBMAP\n", 6,1,fp);
    fwrite(map->name, 127, 1, fp);
    fwrite(map->filename,255,1,fp);
    fputc(map->width, fp);
    fputc(map->height, fp);

    int i,j;

    for(i = 0; i < LAYERS_NUM; i++){

        //layer number
        fputc(i, fp);

        //layer tiles
        for(j = 0; j < map->width * map->height; j++){
            fputc(map->layers[i].layer[j], fp);
        }

    }

    for(i = 0;i < map->tileset_count;i++){
        if(!map->tilesets[i].loaded) continue;

         fwrite(map->tilesets[i].name, 127, 1, fp);
         fputc(map->tilesets[i].width, fp);
         fputc(map->tilesets[i].height, fp);
         fputc(map->tilesets[i].tile_width, fp);
         fputc(map->tilesets[i].tile_height, fp);
         fputc(map->tilesets[i].rows, fp);
         fputc(map->tilesets[i].cols, fp);
         fputc(map->tilesets[i].first_gid, fp);

    }


    fclose(fp);

    fprintf(stdout, "map: %s is written to file\n\n", map->filename);


}
