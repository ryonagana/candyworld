#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared.h"


#define PLAYER_DIRECTION_NONE  0
#define PLAYER_DIRECTION_UP    1
#define PLAYER_DIRECTION_DOWN  2
#define PLAYER_DIRECTION_LEFT  3
#define PLAYER_DIRECTION_RIGHT 4

#define PLAYER_STATE_NONE    0
#define PLAYER_STATE_WALKING 1
#define PLAYER_STATE_JUMPING 2
#define PLAYER_STATE_WAIT    3



struct player_t {
    int x;
    int y;
    rect_t hitbox;
    int lives;
    Sint64 score;
    int direction;
    int state;
};

typedef struct player_t player_t;


void player_init(player_t *pl);
void player_draw(player_t *pl);
void player_update(player_t *pl);

#endif // PLAYER_H
