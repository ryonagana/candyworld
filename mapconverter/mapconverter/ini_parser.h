#ifndef INI_PARSE_H
#define INI_PARSE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ini.h"
#include <string.h>

int ini_handler_proc(void* user, const char* section, const char* name, const char* value);

#endif // INI_PARSE_H
