#include "gameplay.h"
#include "lua_vm.h"
#include "lua_shared.h"
#include "lua_hud.h"
#include "hud.h"
#include "resources.h"
#include "timer.h"
#include "log.h"
#include "keyboard.h"
#include "sprite.h"
#include "debug.h"


game_event_t  main_game_event;


void gameplay_start(game_data_t *gamedata)
{
    player_init(&gamedata->player);
    player_set_pos_screen(&gamedata->player, 10,10);
}

void gameplay_end(game_data_t *gamedata)
{

}



void gameplay_event_loop(game_event_data *e, void* data){


    game_data_t *gamedata = (void*)data;

    Uint32 ticks = 0;
    game_timer_t game_timer;

    gameplay_start(gamedata);

    timer_init(&game_timer);
    timer_set_start(&game_timer);

    while(!window_get()->closed){
        SDL_Event ev;
        ticks = timer_get_ticks(&game_timer);



        if(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT){
                window_get()->closed = 1;
                break;
            }

            if(ev.type == SDL_WINDOWEVENT){
                if(ev.window.event == SDL_WINDOWEVENT_RESIZED){
                    window_resize(ev.window.data1, ev.window.data2);
                    SDL_Log("Window Resized to:  %dx%d", window_get()->info.width, window_get()->info.height);
                }
            }


        }



        ticks = timer_get_ticks(&game_timer);



        //DLOG("ticks %d", TIMER_TICKS_TO_SECS(ticks));
        keyboard_update(&ev);
        player_update(&gamedata->player, ticks);
        player_handle_input(&gamedata->player, ticks);

        SDL_SetRenderDrawColor(window_get()->events.renderer, 255,0,0,255);
        SDL_RenderClear(window_get()->events.renderer);

        debug_player_info(&gamedata->player);
        map_render(gamedata->map);
        player_draw(&gamedata->player);
        //text_draw(debug_text, 0,0, (SDL_Color){255,255,255,255}, "Teste %d", 10);
        //text_draw_shade(debug_text, 0,0, (SDL_Color){0,0,255,255}, (SDL_Color){255,255,255,255}, "Regular Text Test");


        SDL_RenderPresent(window_get()->events.renderer);
        timer_frame_cap(ticks);

    }


    gameplay_end(gamedata);


}





