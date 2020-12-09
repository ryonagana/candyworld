#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"

typedef struct {
    int width;
    int height;
    texture_t *spritesheet;
    int x;
    int y;
}sprite_t;


void sprite_init(sprite_t *self);
sprite_t *sprite_create(SDL_Texture *texture, int x, int y, int width, int height);
void sprite_free(sprite_t *sprite);
void sprite_draw(sprite_t *self, int x, int y, int width, int height, float angle, SDL_RendererFlip flip);

/*
int sprite_init(sprite_t **spr, SDL_Texture *tex);
int sprite_init_str(sprite_t **spr, const char *name);
int sprite_set_spritesheet_offset(sprite_t *spr, int frame_width, int frame_height);
void sprite_set_animation(sprite_t *spr, int anim);

int sprite_set_delay(sprite_t *spr, int *delay, size_t size);

void sprite_draw(sprite_t *spr, int x, int y, int orig_w, int orig_h, int dst_w, int dst_h);
void sprite_draw_rect(sprite_t *spr, int src_x, int src_y, int dest_x, int dest_y, int w, int h, int flip);
void sprite_update(sprite_t *spr);
void sprite_free(sprite_t **spr);
*/


#endif // SPRITE_H
