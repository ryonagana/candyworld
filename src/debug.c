#include "debug.h"
#include <SDL2/SDL.h>
#include "window.h"
#include "text.h"

static text_t *debug_text = NULL;

void debug_start()
{
    text_init_font(&debug_text, "debug_ttf", 12,0);
}

void debug_end()
{

}



void debug_render_player_hitbox(player_t *pl)
{

    SDL_SetRenderDrawColor(window_get()->events.renderer, 0,0,255,255);
    SDL_Rect r = { pl->x, pl->y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE  };
    SDL_RenderDrawRect(window_get()->events.renderer, &r);
    return;



}

void debug_player_info(player_t *pl)
{
#ifdef DEBUG
    char *states_pos[6] = {
        "STATE NONE\0",
        "STATE UP\0",
        "STATE DOWN\0",
        "STATE LEFT\0",
        "STATE RIGHT\0",
        NULL
    };
    debug_render_player_hitbox(pl);
    text_draw(debug_text, 10,0, (SDL_Color){0,0,255,255}, "Dir: %s\n",states_pos[pl->direction]);
    text_draw(debug_text, 10,50, (SDL_Color){0,0,255,255}, "X:%d Y: %d\n",pl->x, pl->y);

#endif
    return;
}

