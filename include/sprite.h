#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
    SDL_Rect pos;
    SDL_Rect hotspot;
    SDL_Rect offset;
    SDL_Texture *texture;
    int frame_time;
    int frames;
    int actual_frame;
    int is_animated;

}sprite_t;

#endif // SPRITE_H
