#include "keyboard.h"
#include "window.h"
#include "log.h"

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
   return key == game_event->keyboard.keycode ? game_keys[key] : 0;
}

int key_is_released(int key)
{
    if(!game_keys[key] && key == game_event->keyboard.keycode){
        game_keys[key] = 0;
    }else {
        game_keys[key] = 1;
    }

    return game_keys[key];
}

int key_is_pressed_once(int key)
{
    if(game_keys[key] && key == game_event->keyboard.keycode && !game_event->keyboard.repeat){
        game_keys[key] = 1;
    }else {
        game_keys[key] = 0;
    }

    return game_keys[key];
}

int key_is_released_once(int key)
{
    if(!game_keys[key] && key == game_event->keyboard.keycode && !game_event->keyboard.repeat){
        game_keys[key] = 0;
    }else {
        game_keys[key] = 1;
    }

    return game_keys[key];
}

void keyboard_update(ALLEGRO_EVENT *ev)
{

    game_event = ev;

    if(ev->type == ALLEGRO_EVENT_KEY_DOWN){
        game_keys[ev->keyboard.keycode] = 1;
        DLOG("PRESSED KEY: %d - %s", ev->keyboard.keycode, al_keycode_to_name(ev->keyboard.keycode));
    }

    if(ev->type == ALLEGRO_EVENT_KEY_UP){
        game_keys[ev->keyboard.keycode] = 0;
          DLOG("RELEASED KEY: %d - %s", ev->keyboard.keycode, al_keycode_to_name(ev->keyboard.keycode));
    }



    return;

}
