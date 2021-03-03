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

#define PLAYER_STATE_NONE    0
#define PLAYER_STATE_IDLE    1
#define PLAYER_STATE_WALKING 2
#define PLAYER_STATE_JUMPING 3
#define PLAYER_STATE_WAIT    4

#define PLAYER_SPEED 350.0f
#define MAX_PLAYER_ANIMATION 32

#define PLAYER_TILE_SIZE 32


#define PLAYER_STATE_FALLING   0
#define PLAYER_STATE_ON_GROUND 1

struct player_t {
    float x;
    float y;
    float speed_y;
    float speed_x;
    game_rect_t hitbox;
    game_rect_t screen_rect;
    int lives;
    Sint64 score;
    int direction;
    int32_t state;
    Uint32 anim_counter;
    int max_frames;
    game_rect_t hitboxes[4];
    int frames;
    Uint32 flags;
    camera player_camera;
    int is_falling;
};

typedef struct player_t player_t;


void player_init(player_t *pl);
void player_draw(player_t *pl);
void player_handle_input(player_t *pl, float delta);
void player_set_pos_screen(player_t *player, int x, int y);
void player_end(player_t *pl);
SDL_bool player_screen_bound(player_t *player);

void player_apply_gravity(player_t *pl, float delta);
void player_update2(void* data, float delta);
void player_move(player_t *player, map_t *map, float delta);

#endif // PLAYER_H
