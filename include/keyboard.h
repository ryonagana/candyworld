#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

void keyboard_init(void);
void keyboard_update(SDL_Event *ev);

Uint8 key_pressed(int key);

#endif // KEYBOARD_H
