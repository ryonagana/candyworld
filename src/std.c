#include "std.h"
#include <string.h>

const char *std_basename(const char *path, char separator)
{
    if((strrchr(path, separator)) == NULL){
        return  strdup(path);
    }

    return strdup(strrchr(path + 1, separator) + 1);
}

static void mem_error_message(const char *msg, ...){

    va_list lst;
    va_start(lst, msg);
    char buf[BUFSIZ] = {0};
    vsnprintf(buf, BUFSIZ, msg,  lst);
    va_end(lst);
    DCRITICAL(buf);
    return;
}

void *mem_alloc(size_t size)
{
    void *block = NULL;
    block = malloc(size);

    if(!block){
        mem_error_message("mem_alloc(): invalid block");
        return block;
    }

    return block;
}

void *mem_calloc(size_t nmemb, size_t size)
{
    void *block = NULL;

    block = calloc(nmemb, size);

    if(!block){
        mem_error_message("mem_alloc(): invalid calloc ");
        return block;
    }

    return block;


}

void mem_free(void **ptr)
{
    if( *ptr == NULL){
        return;
    }

    free((void **)ptr);
    *ptr = 0x0;
}

void *mem_realloc(void *ptr, size_t size)
{
    void *blk = NULL;
    blk = realloc(ptr, size);

    if(!blk){
        mem_error_message("mem_realloc(): invalid calloc ");
        return blk;
    }

    return blk;
}
