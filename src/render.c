#include "render.h"
#include "window.h"

void render_texture(SDL_Texture *tex, int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y, int dst_w, int dst_h, double angle, int flip)
{
    SDL_Rect r_src = { src_x, src_y, src_w, src_h };
    SDL_Rect r_dest = {dst_x, dst_y, dst_w, dst_h};
    SDL_RenderCopyEx(window_get()->events.renderer, tex, &r_src, &r_dest, angle, NULL, flip);


}
