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
    if(argc <= 1){
        usage();
        return 0;
    }

    parse_params(argc, argv);


    map_t* root = NULL;

    root = map_init();
    map_load_str(root, map_folder);

    if(root == NULL){
        usage();
        return 0;
    }

    map_save_name(root, map_folder);

    map_free(&root);

    return 0;
}
