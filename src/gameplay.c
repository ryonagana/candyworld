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

    double delta_time = 0;
    Uint64 fps_time =  SDL_GetTicks();
    int64_t frame_time = 0;
    int64_t fps = 0;
    int64_t fps_total  = 0;
    //game_timer_t game_timer;

    gameplay_start(gamedata);




    while(!window_get()->closed){
        frame_time = SDL_GetTicks();
        SDL_Event ev;



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


        //DLOG("ticks %d", TIMER_TICKS_TO_SECS(ticks));
        keyboard_update(&ev);
        player_update(&gamedata->player, delta_time);
        player_handle_input(&gamedata->player, delta_time);

        SDL_SetRenderDrawColor(window_get()->events.renderer, 255,0,0,255);
        SDL_RenderClear(window_get()->events.renderer);

        map_render(gamedata->map);
        debug_player_info(&gamedata->player);
        player_draw(&gamedata->player);
        //text_draw(debug_text, 0,0, (SDL_Color){255,255,255,255}, "Teste %d", 10);
        //text_draw_shade(debug_text, 0,0, (SDL_Color){0,0,255,255}, (SDL_Color){255,255,255,255}, "Regular Text Test");


        SDL_RenderPresent(window_get()->events.renderer);


        if(SDL_GetTicks() - 1000 >= fps_time){
            fps_time = SDL_GetTicks();
            fps_total = fps;
            char fps_str[60] = {0};
            snprintf(fps_str, 60, "%s  - FPS: %lld", window_get()->title, fps);
            SDL_SetWindowTitle(window_get()->events.window, fps_str);
            fps = 0;

        }

        ++fps;


        if(!window_get()->vsync && SDL_GetTicks() - frame_time < FPS_MIN){
            SDL_Delay(FPS_MIN - (SDL_GetTicks() - frame_time));
        }





    }


    gameplay_end(gamedata);


}





