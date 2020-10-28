#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
    SDL_Rect pos;
    SDL_Rect hotspot;
    SDL_Texture *texture;
    int offset_x;
    int offset_y;
    int frame_time;
    int frames;
    int actual_frame;
    int is_animated;

}sprite_t;


int sprite_init(sprite_t **spr, SDL_Texture *tex);
int sprite_init_str(sprite_t **spr, const char *name);
int sprite_set_spritesheet_offset(sprite_t *spr, int rows, int cols);

void sprite_draw(sprite_t *spr, int x, int y);
void sprite_free(sprite_t **spr);


#endif // SPRITE_H
