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
#include "math.h"



game_event_t  main_game_event;
gametimer_t   gameplay_timer;



void gameplay_start(game_data_t *gamedata)
{
    player_init(&gamedata->player);
    //player_set_pos_screen(&gamedata->player, 10,10);
}

void gameplay_end(game_data_t *gamedata)
{

}




void gameplay_event_loop(game_event_data *e, void* data){

    game_data_t *gamedata = (void*)data;
    timer_init(&gameplay_timer);
    gameplay_start(gamedata);


    while(!window_get()->closed){

        timer_update(&gameplay_timer);



        SDL_Texture *screen_buffer = SDL_CreateTexture(window_get()->events.renderer, SDL_GetWindowPixelFormat(window_get()->events.window) ,SDL_TEXTUREACCESS_TARGET, window_get()->info.width, window_get()->info.height);

        SDL_Event ev;

        if(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT){
                window_get()->closed = 1;
                break;
            }

            if(ev.type == SDL_WINDOWEVENT){
                if(ev.window.event == SDL_WINDOWEVENT_RESIZED){
                    window_resize((int)ev.window.data1, (int)ev.window.data2);
                    SDL_Log("Window Resized to:  %dx%d", window_get()->info.width, window_get()->info.height);
                }
            }


        }





        keyboard_update(&ev);
        player_update(&gamedata->player, timer_do_tick(&gameplay_timer));




        SDL_SetRenderTarget(window_get()->events.renderer, screen_buffer);
        SDL_SetRenderDrawColor(window_get()->events.renderer, 255,0,0,255);
        SDL_RenderClear(window_get()->events.renderer);
        map_render(gamedata->map, 0,0);
        player_draw(&gamedata->player);


        SDL_SetRenderTarget(window_get()->events.renderer, NULL);
        SDL_RenderCopy(window_get()->events.renderer, screen_buffer, &(SDL_Rect){0,0, window_get()->info.width, window_get()->info.height}, &(SDL_Rect){0,0, window_get()->info.width, window_get()->info.height});
        SDL_RenderPresent(window_get()->events.renderer);
        SDL_DestroyTexture(screen_buffer);

    }

     gameplay_end(gamedata);


    /*
    game_data_t *gamedata = (void*)data;
    gameplay_start(gamedata);


    timer_init(&gameplay_timer);

    while(!window_get()->closed){

        timer_do_tick(&gameplay_timer);

        SDL_Event ev;
        SDL_Texture *screen_buffer = SDL_CreateTexture(window_get()->events.renderer, SDL_GetWindowPixelFormat(window_get()->events.window) ,SDL_TEXTUREACCESS_TARGET, window_get()->info.width, window_get()->info.height);


        if(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT){
                window_get()->closed = 1;
                break;
            }

            if(ev.type == SDL_WINDOWEVENT){
                if(ev.window.event == SDL_WINDOWEVENT_RESIZED){
                    window_resize((int)ev.window.data1, (int)ev.window.data2);
                    SDL_Log("Window Resized to:  %dx%d", window_get()->info.width, window_get()->info.height);
                }
            }


        }

        keyboard_update(&ev);
        player_update(&gamedata->player, gameplay_timer.delta);


        SDL_SetRenderTarget(window_get()->events.renderer, screen_buffer);
        SDL_SetRenderDrawColor(window_get()->events.renderer, 255,0,0,255);
        SDL_RenderClear(window_get()->events.renderer);
        map_render(gamedata->map, 0,0);
        player_draw(&gamedata->player);


        SDL_SetRenderTarget(window_get()->events.renderer, NULL);
        SDL_RenderCopy(window_get()->events.renderer, screen_buffer, &(SDL_Rect){0,0, window_get()->info.width, window_get()->info.height}, &(SDL_Rect){0,0, window_get()->info.width, window_get()->info.height});
        SDL_RenderPresent(window_get()->events.renderer);
        SDL_DestroyTexture(screen_buffer);

    }


    gameplay_end(gamedata);
    */


}





