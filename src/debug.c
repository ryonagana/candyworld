#include "debug.h"
#include <SDL2/SDL.h>
#include "window.h"

void debug_render_player_hitbox(player_t *pl)
{
    SDL_SetRenderDrawColor(window_get()->events.renderer, 0,0,255,255);
    SDL_Rect r = { pl->x, pl->y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE  };
    SDL_RenderDrawRect(window_get()->events.renderer, &r);
    return;
}
