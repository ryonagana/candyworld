#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <stdio.h>
#include <string.h>
//#include <allegro5/allegro.h>

/*
typedef struct game_keys_t {
    int key;
    char name[20];
}game_keys_t[ALLEGRO_KEY_MAX];
*/

void keyboard_init(void);
void keyboard_end(void);


void keyboard_update(ALLEGRO_EVENT *ev);

int key_is_pressed(int key);
int key_is_released(int key);

int key_is_pressed_once(int key);
int key_is_released_once(int key);


#endif // KEYBOARD_H
