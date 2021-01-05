#ifndef STD_H
#define STD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stdarg.h>
#include "log.h"

const char *std_basename(const char *path, char separator);


#define BASENAME(p) std_basename(p, '/')


void *mem_alloc(size_t size);
void *mem_calloc(size_t nmemb, size_t size);
void *mem_realloc(void *ptr, size_t size);
void mem_free(void **ptr);

#endif // STD_H

