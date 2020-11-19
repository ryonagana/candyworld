#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared.h"
#include "camera.h"
#include <SDL2/SDL.h>

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


#define PLAYER_TILE_SIZE 32

struct player_t {
    int x;
    int y;
    SDL_Rect hitbox;
    int lives;
    Sint64 score;
    int direction;
    int state;
    int offset_x;
    int offset_y;
    Uint32 anim_counter;
    int max_frames;
    int frames;
    Uint32 flags;
    camera player_camera;
};

typedef struct player_t player_t;


void player_init(player_t *pl);
void player_draw(player_t *pl);
void player_update(player_t *pl, Uint32 delta);
void player_handle_input(player_t *pl, Uint32 delta);
void player_set_pos_screen(player_t *player, int x, int y);

SDL_bool player_screen_bound(player_t *player);

#endif // PLAYER_H
