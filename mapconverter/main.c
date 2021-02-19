#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ini.h"
#include <string.h>
#include <assert.h>
#ifdef __GNUC__
#include <errno.h>
#endif


#include "../include/map.h"



static char map_folder[BUFSIZ] = {0};

static int  map_convert = 0;
static int  show_map_info = 0;

void usage(){
    printf("usage:\n");
    printf("mapconverter <map path> - Convert CSV (Tiled) to binary CBMAP\n");
    printf("mapconverter -i <mymap.cbmap> - Show Map Info\n");
    return;

}

void parse_params(int argc, char **argv){

    char argbuf[255] = {0};

    strncpy(argbuf, argv[1], 255 - strlen(argv[1]));

     if(argc > 1){
        //strncpy(map_folder, (char *)argv[1], strlen(argv[1]));

        if(strncmp(&argbuf[0], "-", 1) == 0){
                char letter = argbuf[1];

                switch(letter){
                    case 'i':
                    show_map_info = 1;
                    break;
                }
                return;
        }else {
             map_convert = 1;
             return;
        }
       }


}

static void opt_map_convert_file(char **argv){

    char converted_map_output[BUFSIZ]= {0};
    map_t *map = NULL;



    strncpy(map_folder, argv[1], BUFSIZ - strlen(argv[1]));
    strncpy(converted_map_output, map_folder, BUFSIZ - strlen(map_folder));
    strncat(converted_map_output,"//",1);
    strncat(converted_map_output, map_folder ,BUFSIZ - strlen(map_folder));



    map = map_init();
    map_load_str_csv(map, map_folder);
    map_save_name(map, converted_map_output);
    map_free(&map);


    FILE *in_map = NULL;


     strncat(converted_map_output, MAP_FORMAT ,BUFSIZ - strlen(MAP_FORMAT));

    in_map = fopen(converted_map_output, "rb+");

    if(!in_map){
        MAPCONV_ERROR("erorr %s not found", map_folder);
        return;
    }
    map = map_load_file_str(converted_map_output);
    //map_load_stream(&map, in_map);
    map_show_info(map);
    map_generate_tilesets(map, "tiles.h");
    fclose(in_map);




    //strncpy(map_folder, argv[1], BUFSIZ - strlen(argv[1]));
    //strncpy(map_output_name, map_folder, BUFSIZ - strlen(map_folder));
    //strncat(map_output_name, MAP_FORMAT, BUFSIZ - strlen(MAP_FORMAT));

    //map = map_init();
    //map_load_str_csv(map, map_folder);
    //map_save_name(map, map_folder);


    /*
    strncat(map_folder, "//", 1);
    strncat(map_folder, map_output_name, strlen(map_output_name) + 1);

    FILE *updated_map = NULL;

    updated_map = fopen(map_folder, "rb+");

    if(!updated_map){
        MAPCONV_ERROR("erorr %s not found", map_folder);
        return;
    }

    map_load_stream(&map, updated_map);
    map_show_info(map);
    map_free(&map);
    */
}


void opt_show_map_info(const char *filename){
    map_t *map = map_load_file_str(filename);

    assert(map);
    MAPCONV_LOG(" ------------- MAP INFORMATION ---------------------");
    map_show_info(map);
    return;
}


int main(int argc , char *argv[])
{


    if(argc <= 1){
        usage();
        return 0;
    }

    parse_params(argc, argv);


    if(map_convert){
        opt_map_convert_file(argv);
        return 0;

    }else if(show_map_info){
        strncpy(map_folder, (char *)argv[2], 4096 - strlen(argv[2]));
        opt_show_map_info(map_folder);
        return 0;
    }




    return 0;
}
