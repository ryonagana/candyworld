#include "game.h"
//#include "keyboard.h"
#include "lua_vm.h"
#include "lua_shared.h"
#include "lua_hud.h"
#include "hud.h"
#include "resources.h"
#include "timer.h"
#include "log.h"

static game_data_t gamedata;



void game_init()
{
    hud_t *hud = hud_get();

    window_get()->gamestate = GAMESTATE_IN_GAME;
    lua_start();
    lua_shared_register(lua_get_state());
    hud_init();
    lua_hud_register(lua_get_state(), hud);
    lua_free();


    resources_start(NULL);

    resources_file_add("resources//sprites//sprite2.png", "sprite2");
    resources_file_add("resources//sprites//debug_tiles.png", "debug_tiles");
    resources_file_add("resources//sfx//test.ogg", "test_music");

    //resources_sprite_get("sprite2", RESOURCE_TYPE_SPRITE);
    //resources_sound_get("test", RESOURCE_EXTENSION_OGG);
}


void game_start()
{
    gamedata.redraw_frame = 0;
    player_init(&gamedata.player);

    player_set_pos_screen(&gamedata.player, 10,10);

    switch(window_get()->gamestate){
        case  GAMESTATE_IN_GAME:
        game_loop();
    break;
    }
}


void game_end()
{

    resources_free();
    window_end();

}


void game_loop()
{

    Uint32 ticks = 0;
    timer_t game_timer;

    timer_init(&game_timer);
    timer_set_start(&game_timer);

    while(!window_get()->closed){
        SDL_Event ev;



        if(SDL_PollEvent(&ev)){
            if(ev.type == SDL_QUIT){
                window_get()->closed = 1;
                break;

            }
        }

        ticks = timer_get_ticks(&game_timer);

        //DLOG("ticks %d", TIMER_TICKS_TO_SECS(ticks));

        SDL_SetRenderDrawColor(window_get()->events.renderer, 255,0,0,255);
        SDL_RenderClear(window_get()->events.renderer);

        player_draw(&gamedata.player);

        SDL_RenderPresent(window_get()->events.renderer);
    }


}


