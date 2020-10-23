#include "ini_parser.h"
#include "map.h"

int ini_handler_proc(void* user, const char* section, const char* name, const char* value){

        map_t *game_map = (void*)user;

        #define INI_MATCH(section_name, val) strcmp(section, section_name) == 0 && strcmp(name, val) == 0



       if(INI_MATCH("map", "name")){
           //game_map->name = strdup(value);
           strncpy(game_map->name, value, 127 - 1);
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
           //game_map->layers[LAYER_TILES].name = strdup(value);
           strncpy(game_map->layers[LAYER_TILES].name, value, 127 - 1);
           return 0;
       }

       if(INI_MATCH("map", "bg_layer")){
           strncpy(game_map->layers[LAYER_BACKGROUND].name, value, 127 - 1);
           return 0;
       }

       if(INI_MATCH("map", "tileset_count")){
           game_map->tileset_count = atoi(value);
           return 0;
       }


       if(INI_MATCH("tileset", "name")){
           strncpy(game_map->tilesets[0].name, value, 127 -1);
           return 0;
       }

       if(INI_MATCH("tileset", "tile_width")){
           game_map->tilesets[0].tile_width = atoi(value);
           return 0;
       }



       if(INI_MATCH("tileset", "tile_height")){
           game_map->tilesets[0].tile_height = atoi(value);
           return 0;
       }

       if(INI_MATCH("tileset", "firstgid")){
           game_map->tilesets[0].first_gid = atoi(value);
           return 0;
       }


       if(INI_MATCH("tileset", "rows")){
           game_map->tilesets[0].rows = atoi(value);
           return 0;
       }

       if(INI_MATCH("tileset", "cols")){
           game_map->tilesets[0].cols = atoi(value);
           return 0;
       }



       if(INI_MATCH("tileset", "width")){
           game_map->tilesets[0].width = atoi(value);
           return 0;
       }

       if(INI_MATCH("tileset", "height")){
           game_map->tilesets[0].height = atoi(value);
           return 0;
       }

        game_map->tilesets[0].loaded = 1;


       return 1;

}
