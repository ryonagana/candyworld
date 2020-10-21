#include "csv_parser.h"

void csv_parse_file(FILE *fp, int rows, int cols, void** data){

    char linebuf[4096];
    int y = 0;
    int *result = NULL;

    result = calloc( (rows * cols) + 1, sizeof (int));



    while(fgets(linebuf, 4096, fp) &&  y < rows  ){

        char *token = NULL;
        int x = 0;
        const char delimiter[2] = ",";
        token = strtok(linebuf, delimiter);

        while(token != NULL && x < cols){

            const char *val = (char *) token;
            result[x * cols + y] = atoi(val);
            x++;
            token = strtok(NULL, delimiter);
        }

        y++;
    }

    *data = result;

}

void csv_debug_print(int *data, int rows, int cols){
    int y,x;



    for(y = 0; y < rows; y++){
          for(x = 0; x < cols; x++){
              if(data[y * rows + x] != '\0'){
                printf("%d, ", data[x * cols + y]);
              }
          }
    }

}

void csv_free(void **data)
{
    if(*data != NULL){
        free((void **)data);
        *data = NULL;
    }
}
