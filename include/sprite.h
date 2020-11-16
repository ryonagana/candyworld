#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
    SDL_Rect pos;
    SDL_Rect hotspot;
    SDL_Texture *texture;
    int *delay;
    int rows;
    int cols;
    int current_frame;
    int current_animation;
    int end_frame;
    int time_passed;

}sprite_t;


int sprite_init(sprite_t **spr, SDL_Texture *tex);
int sprite_init_str(sprite_t **spr, const char *name);
int sprite_set_spritesheet_offset(sprite_t *spr, int rows, int cols);

int sprite_set_delay(sprite_t *spr, int *delay, size_t size);

void sprite_draw(sprite_t *spr, int x, int y, int orig_w, int orig_h, int dst_w, int dst_h);
void sprite_update(sprite_t *spr);
void sprite_free(sprite_t **spr);


#endif // SPRITE_H
