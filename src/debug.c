#include "debug.h"
#include <SDL2/SDL.h>
#include "window.h"
#include "text.h"

static text_t *debug_text = NULL;

void debug_start()
{
    //text_create()
   // text_init_font(&debug_text, "debug_ttf", 12,0);
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

    char *states_pos[6] = {
        "STATE NONE",
        "STATE UP",
        "STATE DOWN",
        "STATE LEFT",
        "STATE RIGHT",
        NULL
    };
    debug_render_player_hitbox(pl);

    char dbg_text[TEXT_MAX_ENTRY] = {0};
    snprintf(dbg_text, TEXT_MAX_ENTRY,  "Dir: %s\n",states_pos[pl->direction]);

    text_t* states = text_create(dbg_text, (SDL_Color){0,0,255,255});



    text_draw(states, 10,0);

    snprintf(dbg_text, TEXT_MAX_ENTRY, "Speed X: %.2f - Speed Y: %.2f", pl->speed_x, pl->speed_y);
    text_t* speeds = text_create(dbg_text, (SDL_Color){255,0,0});

    text_draw(speeds, 10, 80);
    text_destroy(states);


    snprintf(dbg_text, TEXT_MAX_ENTRY, "X:%.2f Y: %.2f\n",pl->x, pl->y);

    states = text_create(dbg_text, (SDL_Color){0,0,255,255});
    text_draw(states, 10,40);
    text_destroy(states);

    return;
}


void debug_camera_render(camera *c)
{
    SDL_SetRenderDrawColor(window_get()->events.renderer, 0,0,255,255);

     text_t* states = text_create("CAMERA AREA:", (SDL_Color){255,0,0,255});


    text_draw(states, 0,50);
    SDL_RenderDrawRect(window_get()->events.renderer, &c->area);
}
