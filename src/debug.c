#include "debug.h"
#include <SDL2/SDL.h>
#include "window.h"
#include "text.h"


#if DEBUG
#define RENDER_COLLISION (SDL_Color){255,0,0,0}
#endif


void debug_start()
{

}

void debug_end()
{

}



void debug_render_player_hitbox(player_t *pl)
{


    SDL_SetRenderDrawColor(window_get()->events.renderer, 0,0,255,255);
    SDL_Rect r = {pl->rect.pos.x, pl->rect.pos.y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE  };
    SDL_RenderDrawRect(window_get()->events.renderer, &r);


    r.x = pl->hitbox_area.pos.x;
    r.y = pl->hitbox_area.pos.y;
    r.w = pl->hitbox_area.pos.w;
    r.h = pl->hitbox_area.pos.h;

    SDL_SetRenderDrawColor(window_get()->events.renderer, 255,255,0,255);
    SDL_RenderDrawRect(window_get()->events.renderer, &r);



    return;



}

void debug_player_info(player_t *pl)
{

    char dbg_text[TEXT_MAX_ENTRY] = {0};

    snprintf(dbg_text, TEXT_MAX_ENTRY, "Speed X: %.2f - Speed Y: %.2f", pl->speed_x, pl->speed_y);
    text_t* speeds = text_create(dbg_text, (SDL_Color){255,0,0,255});

    text_draw(speeds, 10, 80);
    //text_destroy(states);


    snprintf(dbg_text, TEXT_MAX_ENTRY, "X:%.2f Y: %.2f\n",pl->x, pl->y);

    //states = text_create(dbg_text, (SDL_Color){0,0,255,255});
    //text_draw(states, 10,40);
    //text_destroy(states);

    return;
}


void debug_camera_render(camera *c)
{
    SDL_SetRenderDrawColor(window_get()->events.renderer, 0,0,255,255);

     text_t* states = text_create("CAMERA AREA:", (SDL_Color){255,0,0,255});


    text_draw(states, 0,50);
    SDL_RenderDrawRect(window_get()->events.renderer, &c->area);
}

