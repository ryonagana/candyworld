#include "debug.h"
#include <SDL2/SDL.h>
#include "window.h"
#include "text.h"


void debug_start()
{

}

void debug_end()
{

}



void debug_render_player_hitbox(player_t *pl)
{


    SDL_SetRenderDrawColor(window_get()->events.renderer, 0,0,255,255);
    SDL_Rect r = { (int)pl->x, (int)pl->y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE  };
    SDL_RenderDrawRect(window_get()->events.renderer, &r);



    int i;

    for(i = 0; i < 3; i++){

        r.x = pl->hitboxes[i].pos.x;
        r.y = pl->hitboxes[i].pos.y;
        r.w = pl->hitboxes[i].pos.w;
        r.h = pl->hitboxes[i].pos.h;

        SDL_SetRenderDrawColor(window_get()->events.renderer, 255,255,0,255);
        SDL_RenderDrawRect(window_get()->events.renderer, &r);

    }





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
    text_t* speeds = text_create(dbg_text, (SDL_Color){255,0,0,255});

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
