#ifndef CSV_PARSER_H
#define CSV_PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




void csv_parse_file(FILE *fp, int rows, int cols, void **data);
void csv_debug_print(int *data, int rows, int cols);
void csv_free(void **data);
#endif // CSV_PARSER_H
