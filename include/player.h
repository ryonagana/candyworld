#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "shared.h"
#include "camera.h"
#include "map.h"



#define PLAYER_DIRECTION_NONE  0
#define PLAYER_DIRECTION_UP    1
#define PLAYER_DIRECTION_DOWN  2
#define PLAYER_DIRECTION_LEFT  3
#define PLAYER_DIRECTION_RIGHT 4

#define PLAYER_STATE_NONE        0
#define PLAYER_STATE_IDLE        (1 << 1)
#define PLAYER_STATE_WALKING     (1 << 2)
#define PLAYER_STATE_JUMPING     (1 << 3)
#define PLAYER_STATE_WAIT        (1 << 4)
#define PLAYER_STATE_ON_GROUND   (1 << 5)

#define PLAYER_SPEED 350.0f
#define MAX_PLAYER_ANIMATION 32

#define PLAYER_TILE_SIZE 32


#define PLAYER_GRAVITY 90.0f


#define PLAYER_JUMP_LIMIT 245.f;

struct player_t {
    float x;
    float y;
    game_rect rect;
    float speed_x;
    float speed_y;
    game_rect hitbox_area;
    int32_t state;
    camera camera;


};

typedef struct player_t player_t;

void player_init(player_t *player, int x, int y, int32_t state);
void player_update(void *data, float delta);
void player_draw(player_t *player);



#define PLAYER_STATE_IS_SET(mask, bit) ((mask & bit) == bit)
#define PLAYER_STATE_NOT_SET(mask, bit) ((mask & bit) == 0)



#endif // PLAYER_H
