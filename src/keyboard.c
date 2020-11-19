#include "keyboard.h"
#include "window.h"
#include "log.h"
#include "shared.h"

//static Uint8 key_list[285] = {0};
static int32_t key_delay = 0;

const Uint8  *key_list;

void keyboard_init()
{
    DLOG("keyboard started");
    key_delay =  SDL_GetTicks();
    return;
}


void keyboard_update(SDL_Event *ev)
{
    UNUSED(ev);
    key_list = SDL_GetKeyboardState(NULL);


    /*
    if(SDL_GetTicks() - 10  > key_delay){

        key_delay = SDL_GetTicks();


        if(ev->key.type == SDL_KEYUP){
            key_list[ev->key.keysym.scancode] = 0;
            //DLOG("RELEASED %s\n", SDL_GetKeyName(ev->key.keysym.sym));
        }

        if(ev->key.type == SDL_KEYDOWN){
            key_list[ev->key.keysym.scancode] = 1;
           //DLOG("PRESSED %s\n", SDL_GetKeyName(ev->key.keysym.sym));
        }
    }
*/


}

Uint8 key_pressed(int key)
{
    return key_list[key];
}

