#ifndef SHARED_HEADER
#define SHARED_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>




#define UNUSED(v) ((void)v)

typedef int64_t Sint64;
typedef uint64_t Uint64;

typedef uint8_t Byte;
typedef int8_t SByte;

typedef int32_t Sint32;
typedef uint64_t Uint32;



typedef struct Rect {
    int x;
    int y;
    int width;
    int height;
    int top;
    int left;
    int bottom;
    int right;
}Rect;

void rect_init(Rect *r);
void rect_set(Rect *r, int x, int y, int w, int h);



#endif
