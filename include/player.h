#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared.h"
#include <allegro5/allegro.h>

#define PLAYER_DIRECTION_NONE  0
#define PLAYER_DIRECTION_UP    1
#define PLAYER_DIRECTION_DOWN  2
#define PLAYER_DIRECTION_LEFT  3
#define PLAYER_DIRECTION_RIGHT 4

#define PLAYER_STATE_NONE    0
#define PLAYER_STATE_IDLE    1
#define PLAYER_STATE_WALKING 2
#define PLAYER_STATE_JUMPING 3
#define PLAYER_STATE_WAIT    4

#define PLAYER_SPEED 4

struct player_t {
    int x;
    int y;
    rect_t hitbox;
    int lives;
    Sint64 score;
    int direction;
    int state;
    int offset_x;
    int offset_y;
    int anim_counter;
    int max_frames;
    int frames;
    uint32_t flags;
};

typedef struct player_t player_t;


void player_init(player_t *pl);
void player_draw(player_t *pl);
void player_update(ALLEGRO_EVENT *ev, player_t *pl);
void player_handle_input(ALLEGRO_EVENT *ev, player_t *pl);


void player_set_pos_screen(player_t *player, int x, int y);

#endif // PLAYER_H
