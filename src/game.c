#include "game.h"
#include "window.h"
#include "hud.h"
#include "lua_shared.h"
#include "lua_hud.h"
#include "lua_vm.h"
#include "resources.h"
#include "player.h"

static int64_t timer_count = 0;

static player_t player;

void game_init()
{
    window_get()->gamestate = GAMESTATE_IN_GAME;
    lua_start();
    lua_shared_register(lua_get_state());
    hud_init();
    lua_hud_register(lua_get_state(), hud_get());
    lua_free();


    resources_start(NULL);
    resources_file_add("resources//sprites//sprite2.png");
    resources_file_add("resources//sprites//debug_tiles.png");
    resources_file_add("resources//sfx//test.ogg");


    resources_sprite_get("sprite2", RESOURCE_TYPE_SPRITE);
    resources_sound_get("test", RESOURCE_EXTENSION_OGG);
}


void game_start()
{

    player_init(&player);

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



    ALLEGRO_EVENT event;
    int redraw = 0;



    while(!window_get()->closed){

            al_wait_for_event(window_get()->events.queue, &event);

            //keys->Update(&event);


            switch (event.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    window_get()->closed = 1;
                break;

                case ALLEGRO_EVENT_TIMER:
                    timer_count++;
                break;

                case ALLEGRO_EVENT_DISPLAY_RESIZE:
                    al_acknowledge_resize(window_get()->events.display);
                    window_get()->info.width = al_get_display_width(window_get()->events.display);
                    window_get()->info.height = al_get_display_height(window_get()->events.display);
                break;
            }


            while(timer_count > 0){
                timer_count--;

                //GameState::getStateInstance()->getState()->Update();
                redraw = 1;
            }


            //KeyboardEvent::getKeyboardInstance()->handleInput(&event,0);
            //GameState::getStateInstance()->getState()->Input();


        if(redraw && al_is_event_queue_empty(window_get()->events.queue)){
            al_set_target_bitmap(window_get()->events.screen);
            al_clear_to_color(al_map_rgba_f(1,0,0,1));


               player_draw(&player);

             //GameState::getStateInstance()->getState()->Draw();


            al_set_target_backbuffer(window_get()->events.display);
            al_draw_bitmap(window_get()->events.screen, 0,0,0);
            al_flip_display();
            redraw = 0;

        }

    }

}


