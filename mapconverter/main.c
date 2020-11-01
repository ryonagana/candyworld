#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ini.h"
#include <string.h>

#ifdef __GNUC__
#include <errno.h>
#endif


#include "../include/map.h"



char map_folder[4096] = {0};


void usage(){
    printf("usage:\n");
    printf("mapconverter <map path>\n");
    return;

}

void parse_params(int argc, char **argv){


     if(argc > 1){
        strncpy(map_folder, (char *)argv[1], strlen(argv[1]));
     }

}


int main(int argc , char *argv[])
{
    char name[BUFSIZ] = {0};
    map_t *map = NULL;

    if(argc <= 1){
        usage();
        return 0;
    }

    parse_params(argc, argv);


    strncpy(name, map_folder, BUFSIZ - strlen(map_folder));
    strncat(name, MAP_FORMAT, BUFSIZ - strlen(MAP_FORMAT));

    map = map_init();
    map_load_str_csv(map, map_folder);
    map_save_name(map, map_folder);
    map_show_info(map);
    map_free(&map);




    return 0;
}
