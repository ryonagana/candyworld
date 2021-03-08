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

    text_start();

#if defined (DEBUG)
    debug_start();
#endif


     map_render_init();
     gamedata.map = map_load_file_str("resources//map//test2.cbmap");

     if(!gamedata.map){
         window_end(-1);
     }

     //map_show_info(gamedata.map);

     //sprite_t *spr_test = NULL;
     //sprite_init_str(&spr_test, "sprite2");

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
        window_end(-1);
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
    window_free_events(window_get());
    window_end(0);

}

int game_event_switch(int event)
{
    if(&g_events[event] == NULL){
        DCRITICAL("invalid event. critical error");
        window_end(-1);
    }

    gamedata.current_event = g_events[event];
    return event;
}
