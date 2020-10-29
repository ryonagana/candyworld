#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>


void render_texture(SDL_Texture *tex, int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y, int dst_w, int dst_h, double angle, int flip);

#endif // RENDER_H
