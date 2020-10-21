#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ini.h"
#include <string.h>

#ifdef __GNUC__
#include <errno.h>
#endif


#include "map.h"



char map_folder[4096] = {0};


void usage(){
    printf("usage:\n");
    printf("mapconverter <map path>\n");
    return;

}

void parse_params(int argc, char **argv){

    /*
    int i;

    for(i = 0; i < argc; i++){
        strncpy(map_folder, (char *)argv[1], strlen(argv[1]));
    }*/
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
    map_read_config(root, map_folder);
    map_free(&root);

    return 0;
}
