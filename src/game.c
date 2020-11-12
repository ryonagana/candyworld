#include "game.h"
//#include "keyboard.h"
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


#include "gameplay.h"
static game_data_t gamedata;



game_event_t  g_events[MAX_GAME_EVENTS] = {
    {NULL},
    {NULL},
    {NULL},
    {gameplay_event_loop} // GAMESTATE_IN_GAME
};



void game_init()
{
    //window_get()->gamestate = GAMESTATE_IN_GAME;
    lua_start();
    lua_shared_register(lua_get_state());
    hud_init();
    lua_hud_register(lua_get_state(), hud_get());
    lua_free();


    resources_start(NULL);

    //gamedata.events = g_events[0];

    resources_file_add("resources//sprites//sprite2.png", "sprite2");
    resources_file_add("resources//sprites//debug_tiles.png", "debug_tiles");
    resources_file_add("resources//sfx//test.ogg", "test_music");
    resources_ttf_add("resources//fonts//ModernDOS9x16.ttf", "dos_ttf",26);
    resources_ttf_add("resources//fonts//ModernDOS9x16.ttf", "debug_ttf",11);
    resources_file_add("resources//sprites//hud.png", "sprite_hud");

#if defined (DEBUG)
    debug_start();
#endif


     map_render_init();
     gamedata.map = map_load_file_str("resources//map//test.cbmap");

     //map_show_info(gamedata.map);

     sprite_t *spr_test = NULL;
     sprite_init_str(&spr_test, "sprite2");

     gamedata.gamestate = GAME_INGAME_STATE;
     window_get()->gamestate = GAME_INGAME_STATE;
     gamedata.redraw_frame = 0;
     gamedata.current_event = g_events[gamedata.gamestate];


     return;
}


void game_start()
{
    if(!gamedata.current_event.callback){
        DCRITICAL("Current event pointer is NULL");
        window_end();
    }
    gamedata.current_event.callback(NULL, &gamedata);

}



void game_end()
{
#if defined (DEBUG)
    debug_end();
#endif
    map_render_end();
    resources_free();
    window_end();

}


void game_loop()
{


    /*
    Uint32 ticks = 0;
    game_timer_t game_timer;

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
        player_update(&gamedata.player, ticks);
        player_handle_input(&gamedata.player, ticks);

        SDL_SetRenderDrawColor(window_get()->events.renderer, 255,0,0,255);
        SDL_RenderClear(window_get()->events.renderer);

        debug_player_info(&gamedata.player);
        map_render(gamedata.map);
        player_draw(&gamedata.player);
        //text_draw(debug_text, 0,0, (SDL_Color){255,255,255,255}, "Teste %d", 10);
        //text_draw_shade(debug_text, 0,0, (SDL_Color){0,0,255,255}, (SDL_Color){255,255,255,255}, "Regular Text Test");


        timer_frame_cap(ticks);
        SDL_RenderPresent(window_get()->events.renderer);

    }

    */

}




