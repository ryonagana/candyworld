#include "csv_parser.h"

void csv_parse_file(FILE *fp, int rows, int cols, void** data){

    char linebuf[4096];
    int line_count = 0;
    int *result = NULL;

    result = calloc( (rows * cols) + 1, sizeof (int));



    while(fgets(linebuf, 4096, fp) &&  line_count < rows  ){

        char *token = NULL;
        int col_count = 0;
        const char delimiter[2] = ",";
        token = strtok(linebuf, delimiter);

        while(token != NULL && col_count < cols){

            const char *val = (char *) token;
            result[line_count * rows + col_count] = atoi(val);
            col_count++;
            token = strtok(NULL, delimiter);
        }

        line_count++;
    }
    // send end of the map
    result[ rows * cols + 1] = '\0';

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
