#if !defined(MAPCONV_PROJECT)
#include "map.h"
#include "render.h"
#include "resources.h"


#else
#include "../include/map.h"

#endif

#include "../mapconverter/csv_parser.h"
#include "../mapconverter/ini.h"
#include "../mapconverter/ini_parser.h"

#if defined(MAPCONV_PROJECT)
    #define EXIT_MODE(code) (exit(code))
#else
    #define EXIT_MODE(code) (window_exit(code))
#endif


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

int map_file_exists(const char* filename){
        FILE *fp = NULL;

        if((fp = fopen(filename,"rb")) == NULL){
            return 0;
        }

        fclose(fp);
        return 1;

}

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

    if(!map_file_exists(filepath)){
        MAPCONV_LOG("map %s not found!", filepath);
        return 0;
    }



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

    if(map_load_layer(map, LAYER_COLLISION, filepath) < 0){
        MAPCONV_ERROR("Collision tiles not found");
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
    mp->tilesets = calloc(1, sizeof(map_tileset_t));
    //mp->name = "";
    mp->width = 0;
    mp->height = 0;
    mp->tileset_count = 1;
    mp->map_size = 0;
    return mp;
}

 map_layer_t* map_alloc_layer_num(int num){
    map_layer_t *l_tmp = NULL;

    l_tmp = calloc(num, sizeof(map_layer_t));

    if(!l_tmp){
        MAPCONV_ERROR("Error Trying to Allocate  %d map layers", num);
        return l_tmp;
    }

    return l_tmp;
}

map_layer_t * alloc_map_layer(int rows, int cols){
        map_layer_t *mp = NULL;
        mp = malloc(sizeof (map_layer_t));
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
        if(out){
            fclose(out);
        }
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

map_tileset_t *map_tileset_alloc_mem(int num)
{
    map_tileset_t *tmp = NULL;
    tmp = calloc(num + 1, sizeof (map_tileset_t));
    return tmp;
}

void map_tileset_free(map_tileset_t **ts)
{
    map_tileset_t *tmp = NULL;

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

    fwrite(&map->tileset_count, sizeof (int32_t), 1, fp);
    fwrite(&map->map_version, sizeof (int32_t), 1, fp);
    fwrite(&map->map_size, sizeof(int32_t), 1, fp);
    //fputc(map->tileset_count, fp);
    //fputc(map->map_version, fp);

    int i;

    for(i = 0; i < LAYERS_NUM; i++){

        //layer number
        //fputc(i, fp);
        fwrite(&i,sizeof (int32_t), 1, fp);

        if(!map->layers[i].layer){
            MAPCONV_ERROR("Ignoring layer %d", i);
            continue;
        }

        if(!map->layers[i].layer){
            continue;
        }

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
         fwrite(&map->tilesets[i].width, sizeof(int32_t), 1, fp);
         fwrite(&map->tilesets[i].height, sizeof(int32_t), 1, fp);

         fwrite(&map->tilesets[i].tile_width, sizeof(int32_t), 1, fp);
         fwrite(&map->tilesets[i].tile_height, sizeof(int32_t), 1, fp);
         fwrite(&map->tilesets[i].rows, sizeof(int32_t), 1, fp);
         fwrite(&map->tilesets[i].cols, sizeof(int32_t), 1, fp);
         fwrite(&map->tilesets[i].first_gid, sizeof(int32_t), 1, fp);

         /*
         fputc(map->tilesets[i].tile_width, fp);
         fputc(map->tilesets[i].tile_height, fp);
         fputc(map->tilesets[i].rows, fp);
         fputc(map->tilesets[i].cols, fp);
         fputc(map->tilesets[i].first_gid, fp);
         */

    }

    int64_t map_size = map_size_bytes(fp);
    map->map_size = map_size;

    fseek(fp, 6+127+255+16, SEEK_SET);
    fwrite(&map->map_size, sizeof(int32_t), 1, fp);


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
    int i;

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
    fread(&tmp_map->tileset_count, sizeof (int32_t), 1, in);
    fread(&tmp_map->map_version, sizeof (int32_t), 1, in);

    if(tmp_map->map_version < MAP_VERSION){
        MAPCONV_ERROR("Invalid map version: this map is in VERSION %d, needs VERSION %d", tmp_map->map_version, MAP_VERSION);
        EXIT_MODE(1);
        return 0;
    }


    fread(&tmp_map->map_size, sizeof (int32_t), 1, in);
    //tmp_map->tileset_count = fgetc(in);
    //tmp_map->map_version = fgetc(in);


    for(i = 0; i < LAYERS_NUM; i++){
        tmp_map->layers[i].layer = calloc(tmp_map->width * tmp_map->height, sizeof(int32_t));
    }



    for(i = 0; i < LAYERS_NUM; i++){

        //int layer_id = fgetc(in); // get the layer num
        int layer_id = 0;
        fread(&layer_id, sizeof(int32_t), 1, in);
        fread(tmp_map->layers[layer_id].layer, sizeof (int32_t), tmp_map->width * tmp_map->height, in);


    }


    for(i = 0;i < tmp_map->tileset_count;i++){

         fread(tmp_map->tilesets[i].name, 127,1,in);
         fread(&tmp_map->tilesets[i].width, sizeof(int32_t), 1, in);
         fread(&tmp_map->tilesets[i].height, sizeof(int32_t), 1, in);

         fread(&tmp_map->tilesets[i].tile_width, sizeof(int32_t), 1, in);
         fread(&tmp_map->tilesets[i].tile_height, sizeof(int32_t), 1, in);
         fread(&tmp_map->tilesets[i].rows, sizeof(int32_t), 1, in);
         fread(&tmp_map->tilesets[i].cols, sizeof(int32_t), 1, in);
         fread(&tmp_map->tilesets[i].first_gid, sizeof(int32_t), 1, in);



    }


    //convert map loaded 1d array to 2d tile_map_t
    map_convert_1d_to_2d(&tmp_map);

    //fclose(in);
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
                    x *  tmp->tilesets->tile_width,
                    y *  tmp->tilesets->tile_height,
                    tmp->tilesets->tile_width,
                    tmp->tilesets->tile_height,
                    0
                };

                tmp->layers[layer].tiles[y][x] = t;



            }
        }
    }

    *map = tmp;


}

int64_t map_size_bytes(FILE *fp)
{
    if(fp == NULL){
        return -1;
    }

    rewind(fp);
    fseek(fp,0L, SEEK_END);
    int64_t size = ftell(fp);
    rewind(fp);

    return size;
}


typedef struct {
    int id;
    char name[127];
}tile_name;


static void map_get_id_file(tile_name **names, const char *input_name){
    FILE *in = NULL;
    tile_name *tmp_name = *names;

    in = fopen(input_name, "rb+");

    if(!in){
        MAPCONV_ERROR("error trying to read %s", input_name);
        return;
    }

    char *bufline = NULL;
    size_t line_size = 0;

    int count = 0;

    //strncpy(fmt, "%d\t%s\n", 127);

    while(getline(&bufline, &line_size, in) != -1){
        printf("%s", bufline);
        int id = 0;
        char name[127] = {0};
        sscanf(bufline, "%d\t%s", &id, name);

        tmp_name[id].id = id;
        strncpy(tmp_name[id].name, name, 127);
        count++;
    }

    *names = tmp_name;

}

void  map_generate_tilesets(map_t *t, const char *output)
{
    int x,layer_num;
    FILE *out = NULL;
    char name[127] = {0};

    strncpy(name, output, 127 - 1);

    out = fopen(name, "wb+");

    if(!out){
        MAPCONV_ERROR("file %s cannot be created", name);
        return;
    }

    fprintf(out, "// This file is automatic Generated\n\n");
    fprintf(out, "\n");

    for(layer_num = 0; layer_num < t->tileset_count; layer_num++){

         map_tileset_t *ts = &t->tilesets[layer_num];

         tile_name *tiles = NULL;

         tiles = calloc((((ts->width * ts->height) / ts->tile_width) / ts->tile_width) - 1, sizeof (tile_name));

         if(!tiles){
             MAPCONV_ERROR("cannot allocate tiles");
             continue;
         }


         char fullname[255] = {0};
         strncpy(fullname, ts->name, 127 - strlen(ts->name));
         strncat(fullname, ".txt", 127);
         map_get_id_file(&tiles, fullname);


        fprintf(out, "// tileset %s\n\n", ts[layer_num].name);

        for(x = 0; x < ((ts->width * ts->height) / ts->tile_width) / ts->tile_width;x++){


            if(x == 0 && tiles[x].id == 0){
                fprintf(out,"#define TILESET_%d\t%d\n",x,x);
            }else if(tiles[x].id == x){
                fprintf(out,"#define %s\t\t%d\n",tiles[x].name,tiles[x].id);
            }else{
                fprintf(out,"#define TILESET_%d\t%d\n",x,x);
            }
        }

        free(tiles);
        tiles = NULL;

    }

    fclose(out);




}
