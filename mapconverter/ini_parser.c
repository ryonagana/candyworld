#include "ini_parser.h"
#include "map.h"

int ini_handler_proc(void* user, const char* section, const char* name, const char* value){

        map_t *game_map = (void*)user;

        #define INI_MATCH(section_name, val) strcmp(section, section_name) == 0 && strcmp(name, val) == 0

       if(INI_MATCH("map", "name")){
           game_map->name = strdup(value);
           return 0;
       }

       if(INI_MATCH("map", "width")){
           game_map->width = atoi(value);
           return 0;
       }


       if(INI_MATCH("map", "height")){
           game_map->height = atoi(value);
           return 0;
       }


       if(INI_MATCH("map", "tiles_layer")){
           game_map->layers[LAYER_TILES].name = strdup(value);
           return 0;
       }

       if(INI_MATCH("map", "bg_layer")){
           game_map->layers[LAYER_BACKGROUND].name = strdup(value);
           return 0;
       }







       return 1;

}
