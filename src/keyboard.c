#include "keyboard.h"
#include "window.h"

static int game_keys[ALLEGRO_KEY_MAX] = {0};
ALLEGRO_EVENT *game_event = NULL;

void keyboard_init()
{
    memset(game_keys, 0, sizeof(int) * ALLEGRO_KEY_MAX);

}

void keyboard_end()
{

}

int key_is_pressed(int key)
{

    if(!game_keys[key]){
            return 0;
    }

    if(game_event->type == ALLEGRO_EVENT_KEY_DOWN && game_keys[game_event->keyboard.keycode]){
        return 1;
    }

    return game_keys[game_event->keyboard.keycode];
}

int key_is_released(int key)
{
    if(!game_keys[key] && !game_event->keyboard.repeat){
        return 0;
    }
    return 1;
}

int key_is_pressed_once(int key)
{
    if(!game_keys[key] && !game_event->keyboard.repeat){
        return 0;
    }

    return game_event->keyboard.repeat ? 0 : 1;
}

int key_is_released_once(int key)
{
    return 0;
}

void keyboard_update(ALLEGRO_EVENT *ev)
{

    game_event = ev;

    if(ev->type == ALLEGRO_EVENT_KEY_DOWN && ev->keyboard.keycode){
        game_keys[ev->keyboard.keycode] = 1;
    }

    if(ev->type == ALLEGRO_EVENT_KEY_UP && ev->keyboard.keycode){
        game_keys[ev->keyboard.keycode] = 0;
    }



    return;

}
