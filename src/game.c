#include "game.h"
#include "keyboard.h"

static game_data_t gamedata;


static void game_update(ALLEGRO_EVENT *event){
    player_update(event, &gamedata.player);
    gamedata.redraw_frame = 1;
    return;
}

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

    resources_file_add("resources//sprites//sprite2.png");
    resources_file_add("resources//sprites//debug_tiles.png");
    resources_file_add("resources//sfx//test.ogg");

    resources_sprite_get("sprite2", RESOURCE_TYPE_SPRITE);
    resources_sound_get("test", RESOURCE_EXTENSION_OGG);
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



    ALLEGRO_EVENT event;
    sfx_t *sound = resources_sound_get("test", RESOURCE_EXTENSION_OGG);

    //sfx_play(sound);
    sfx_play_sample(sound, 1.0,0.0,0.5,ALLEGRO_PLAYMODE_ONCE);



    while(!window_get()->closed){

            al_wait_for_event(window_get()->events.queue, &event);

            //keys->Update(&event);


            switch (event.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    window_get()->closed = 1;
                break;

                case ALLEGRO_EVENT_TIMER: {
                        if(event.timer.source == window_get()->events.main_timer){
                            game_update(&event);
                        }


                     }
                break;

                case ALLEGRO_EVENT_DISPLAY_RESIZE:
                    al_acknowledge_resize(window_get()->events.display);
                    window_get()->info.width = al_get_display_width(window_get()->events.display);
                    window_get()->info.height = al_get_display_height(window_get()->events.display);
                break;
            }



             keyboard_update(&event);
             player_handle_input(&event, &gamedata.player);




        if(gamedata.redraw_frame && al_is_event_queue_empty(window_get()->events.queue)){
            gamedata.redraw_frame = 0;
            al_set_target_bitmap(window_get()->events.screen);
            al_clear_to_color(al_map_rgba_f(1,0,0,1));


             player_draw(&gamedata.player);


            al_set_target_backbuffer(window_get()->events.display);
            al_draw_bitmap(window_get()->events.screen, 0,0,0);
            al_flip_display();


        }

    }

}


