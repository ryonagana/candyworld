#include "keyboard.h"
#include "window.h"
#include "log.h"

Uint8 key_list[285] = {0};


void keyboard_init()
{
    int i;

    for(i = 0; i < 285; i++){
        key_list[i] = 0;
    }
}


void keyboard_update(SDL_Event *ev)
{

    if(ev->key.type == SDL_KEYUP){
        key_list[ev->key.keysym.scancode] = 0;
        DLOG("RELEASED %s\n", SDL_GetKeyName(ev->key.keysym.sym));
    }

    if(ev->key.type == SDL_KEYDOWN){
        key_list[ev->key.keysym.scancode] = 1;
        DLOG("PRESSED %s\n", SDL_GetKeyName(ev->key.keysym.sym));
    }



}

Uint8 key_pressed(int key)
{
    return key_list[key];
}

