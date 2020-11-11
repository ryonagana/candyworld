#if !defined(MAPCONV_PROJECT)
#include "map.h"
#include <SDL2/SDL.h>
#include "render.h"
#include "resources.h"


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

#define MAP_COUNT_TILESETS(ts) (sizeof((ts)) / sizeof((ts)[0]))

void map_show_info(map_t *map){
    MAPCONV_LOG("[MAP]\n"
                "map name: %s\n"
                "map version: %d\n"
                "map size: %dx%d\n"
                "map tileset count: %d\n\n"
                ,map->name, map->map_version, map->width, map->height, map->tileset_count);

  int i;

  int layer_count;

  for (i = 0; i < LAYERS_NUM; i++){
      MAPCONV_LOG("layer: %s\n"
                  "layer flag :%d\n"
                  "layer size: %d\n\n", map->layers[i].name, map->layers[i].flags, map->width * map->height);

      for(layer_count = 0; layer_count < map->width * map->height; layer_count++){
        //MAPCONV_LOG(" %d ", map->layers[i].layer[y]);
        printf(" %d ", map->layers[i].layer[layer_count]);

      }
  }

  for(i = 0; i < map->tileset_count;i++){
      MAPCONV_LOG("\n\ntileset size:  %dx%d\n"
                  "tileset tile width: %d\n"
                  "tileset tile height %d\n"
                  "tileset gid %d\n", map->tilesets[i].width,map->tilesets[i].height, map->tilesets[i].tile_width, map->tilesets[i].tile_height, map->tilesets[i].first_gid);
  }


}

int map_load_layer(map_t *map, int layer, const char *map_path){
    char buf[BUFSIZ] = {0};
    FILE *fp = NULL;
    int *data = NULL;

    strncpy(buf, map_path, BUFSIZ - 1);
    strncat(buf, "//\0", 3);
    strncat(buf, map->layers[layer].name, MAP_NAME_BUFFER  - strlen(map->layers[layer].name));

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

int map_load_str_csv(map_t *map, const char *filepath){

    FILE *conf;
    conf = NULL;



#if defined (WIN32) || defined(_WIN32) || (__WIN32__)
    const wchar_t info_path[] = L"//map_info.conf";
    wchar_t map_path[4096] = {0};
    mbstowcs(map_path, filepath, 4096 -  strlen(filepath));
    _tcsncat(map_path,info_path, 4096 - strlen(filepath));



    if((conf = _wfopen(map_path, L"rb+")) == NULL){
         MAPCONV_ERROR("filepath not found - %s", strerror(errno));
         return -1;
    }


#elif defined(__linux__) || (__GNUC__)

    const char *map_info = "//map_info.conf\0";
    char map_path[4096] = {0};


    strncpy(map_path, filepath, 4096 -1);
    int map_info_len = strlen(map_info);
    strncat(map_path, map_info, 4096 -  map_info_len);

    if((conf = fopen(map_path, "rb")) == NULL){
        MAPCONV_ERROR("filepath not found - %s", strerror(errno));
        return -1;
    }
#elif __apple__
#error "TODO"
#elif __unix__
#error "TODO"
#else
    //Add new platform here
#error "Map Loader Using Wrong Platform."
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
    mp->layers = map_alloc_layer_num(LAYERS_NUM);
    mp->tilesets = calloc(1, sizeof(map_tileset));
    //mp->name = "";
    mp->width = 0;
    mp->height = 0;
    mp->tileset_count = 1;
    return mp;
}

 map_layer* map_alloc_layer_num(int num){
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

    strncpy(name, output_filename,56 - 1);
    strcat(name, MAP_FORMAT);

    if((out = fopen(name, "wb+")) == NULL){
        fclose(out);
        MAPCONV_ERROR("invalid file creation");
        return;
    }

    strncpy(map->filename, name, 56 - strlen(name));
    map->map_version = MAP_VERSION;
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
    fwrite(&map->width, sizeof (int32_t), 1, fp);
    fwrite(&map->height, sizeof (int32_t), 1, fp);
    //fputc(map->width, fp);
    //fputc(map->height, fp);
    fputc(map->tileset_count, fp);
    fputc(map->map_version, fp);

    int i;

    for(i = 0; i < LAYERS_NUM; i++){

        //layer number
        fputc(i, fp);
        fwrite(map->layers[i].layer, sizeof(int32_t), map->width * map->height , fp);

        /*
        //layer tiles
        for(j = 0; j < map->width * map->height; j++){
            fputc(map->layers[i].layer[j], fp);

        }
        */

    }

    for(i = 0;i < map->tileset_count;i++){

         fwrite(map->tilesets[i].name, 127, 1, fp);
         fwrite(&map->tilesets[i].width, sizeof(int), 1, fp);
         fwrite(&map->tilesets[i].height, sizeof(int), 1, fp);
         fputc(map->tilesets[i].tile_width, fp);
         fputc(map->tilesets[i].tile_height, fp);
         fputc(map->tilesets[i].rows, fp);
         fputc(map->tilesets[i].cols, fp);
         fputc(map->tilesets[i].first_gid, fp);

    }


    fclose(fp);

    MAPCONV_LOG("map: %s is written to file\n\n", map->filename);
    return;


}

static int map_is_valid_header(char header[6]){

    if(header[0] == 'C' && header[1] == 'B' && header[2] == 'M' && header[3] == 'A' && header[4] == 'P' && header[5] == '\n'){
        return 1;
    }

    return 0;
}

int map_load_stream(map_t **map, FILE *in)
{
    map_t *tmp_map = NULL;
    char header[6] = {0};
    int i,j;

    if( (*(map)) == NULL){
         MAPCONV_ERROR("map_load_file(): map need to be inited before loaded");
        return 0;
    }

    if(in == NULL){
        MAPCONV_ERROR("map_load_file(): file stream is NULL");
        return 0;
    }


    tmp_map = *map;

    fread(header, 6, 1, in);

    if(!map_is_valid_header(header)){
        MAPCONV_ERROR("map_load_file(): Invalid map header");
        return 0;
    }
    strncpy(tmp_map->header, header, 6);


    fread(tmp_map->name, MAP_NAME_BUFFER,1,in);
    fread(tmp_map->filename,MAP_FILENAME_BUFFER,1,in);
    fread(&tmp_map->width, sizeof (int32_t), 1, in);
    fread(&tmp_map->height, sizeof (int32_t), 1, in);
    tmp_map->tileset_count = fgetc(in);
    tmp_map->map_version = fgetc(in);


    for(i = 0; i < LAYERS_NUM; i++){
        tmp_map->layers[i].layer = calloc(tmp_map->width * tmp_map->height, sizeof(int32_t));
    }



    for(i = 0; i < LAYERS_NUM; i++){

        int layer_id = fgetc(in); // get the layer num
        fread(tmp_map->layers[layer_id].layer, sizeof (int32_t), tmp_map->width * tmp_map->height, in);

        /*
        for(j = 0; j < tmp_map->width * tmp_map->height; j++){
            tmp_map->layers[layer_id].layer[j] = fgetc(in);
        }
        */
    }


    for(i = 0;i < tmp_map->tileset_count;i++){

         fread(tmp_map->tilesets[i].name, 127,1,in);
         //tmp_map->tilesets[i].width = fgetc(in);
         //tmp_map->tilesets[i].height = fgetc(in);
         fread(&tmp_map->tilesets[i].width, sizeof(int32_t), 1, in);
         fread(&tmp_map->tilesets[i].height, sizeof(int32_t), 1, in);
         tmp_map->tilesets[i].tile_width = fgetc(in);
         tmp_map->tilesets[i].tile_height = fgetc(in);
         tmp_map->tilesets[i].rows = fgetc(in);
         tmp_map->tilesets[i].cols = fgetc(in);
         tmp_map->tilesets[i].first_gid =fgetc(in);

    }


    //convert map loaded 1d array to 2d tile_map_t
    map_convert_1d_to_2d(&tmp_map);

    fclose(in);
    *map = tmp_map;
    return 1;
}

map_t *map_load_file_str(const char *filepath)
{
    FILE *fp = NULL;
    map_t *map = NULL;
    char buf[BUFSIZ] = {0};

    strncpy(buf, filepath, BUFSIZ - strlen(filepath));



    if((fp = fopen(buf, "rb+")) == NULL){
        MAPCONV_ERROR("map_load_file_str(): cannot find file %s", filepath);
        return 0;
    }

    map = map_init();



    if(!map_load_stream(&map, fp)){
        MAPCONV_ERROR("map_load_file_str(): map cannot be loaded! %s", filepath);
        return map;
    }


    return map;


}


int map_getgid(map_t *map, int gid)
{

    int cur_gid = gid;
    int tileset_gid = -1;

    int c;
    for(c = 0; c < map->tileset_count; c++){

        if(tileset_gid <= cur_gid){
            tileset_gid = map->tilesets[c].first_gid;
            break;
        }
    }

    if(tileset_gid == -1 ) return tileset_gid;

    return cur_gid -= tileset_gid;
}




void map_convert_1d_to_2d(map_t **map)
{
    int x,y;
    int layer;
    map_t *tmp = *map;


    for(layer = 0; layer < LAYERS_NUM; layer++){

        for(y = 0; y < tmp->height; y++){
            for(x = 0; x < tmp->width; x++){
               //tmp->layers[layer].tiles[y][x] = tmp->layers[layer].layer[ y * tmp->height + x];

                int id = tmp->layers[layer].layer[ x + tmp->width * y];
                int32_t gid = map_getgid(tmp, id);

                if(gid == -1) continue;

                int rx = (gid % (tmp->tilesets[0].width / tmp->tilesets->tile_width)) * tmp->tilesets[0].tile_width;
                int ry = (gid / (tmp->tilesets[0].height / tmp->tilesets->tile_height)) * tmp->tilesets[0].tile_height;


                map_tile_t t = {
                    id,
                    rx,
                    ry,
                    x *  tmp->tilesets->tile_width * MAP_SCALE,
                    y *  tmp->tilesets->tile_height * MAP_SCALE,
                    0
                };

                tmp->layers[layer].tiles[y][x] = t;



            }
        }
    }

    *map = tmp;


}
