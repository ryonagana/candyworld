#ifndef TEXTURE_H
#define TEXTURE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

struct _texture_t {
    SDL_Texture *texture;
    int width;
    int height;
    Uint32 format;
    int access;
};

typedef struct _texture_t texture_t;

void  texture_init(texture_t *texture);
texture_t *texture_load_str(const char *name);
texture_t *texture_load_from_SDL(SDL_Texture *tex);
void      texture_destroy(texture_t *self);

#endif // TEXTURE_H
