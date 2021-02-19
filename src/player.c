#include "player.h"
#include "resources.h"
#include "keyboard.h"
#include "window.h"
#include "log.h"
#include "render.h"
#include "debug.h"
#include "sprite.h"
#include "sprite_animation.h"
#include "list.h"


#define MAX_PLAYER_ANIMATION 32


static sprite_t *player_spr = NULL;

static sprite_animation *player_anim_movement_up;


animation_frame_t frames_animation_up[4] = {
 {{0,32,32,32},100,1},
 {{0,32,32,32},100,1},
 {{0,32,32,32},100,1},
 {{}}
};


/*
static sprite_animation_t  player_animation_up;
static sprite_animation_t  player_animation_down;
static sprite_animation_t  player_animation_left;
static sprite_animation_t  player_animation_right;
*/

link_list_t player_animation[MAX_PLAYER_ANIMATION];



const int movement_order[] = {
        PLAYER_DIRECTION_DOWN,
        PLAYER_DIRECTION_LEFT,
        PLAYER_DIRECTION_RIGHT,
        PLAYER_DIRECTION_UP
};




void player_init(player_t *pl){
    pl->x = 0;
    pl->y = 0;
    pl->lives = 3;
    pl->score = 0;
    pl->state = PLAYER_STATE_NONE;
    pl->direction = PLAYER_DIRECTION_NONE;
    pl->offset_x =  0;
    pl->offset_y  = 0;
    pl->flags = 0;
    pl->anim_counter = 0;
    pl->max_frames = 0;
    pl->frames = 0;
    pl->speed_x = 0.0f;
    pl->speed_y = 0.0f;
    //rect_init(&pl->hitbox);
    SDL_RectEmpty(&pl->hitbox);



    player_spr = sprite_create(resources_sprite_get("sprite2", RESOURCE_EXTENSION_PNG),0,0,32,32);  //sprite_init(resources_sprite_get("sprite2", RESOURCE_EXTENSION_PNG));
    //sprite_init(&player_spr, resources_sprite_get("sprite2", RESOURCE_EXTENSION_PNG));
    //sprite_set_spritesheet_offset(player_spr, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE);
   // sprite_set_delay(player_spr, anim_delay, 8);


    //player_anim_movement_up = sprite_animation_create(6);
   // animation_resize_array(player_anim_movement_up, 3);

   player_anim_movement_up = sprite_animation_create_empty();
   sprite_animation_load(&player_anim_movement_up, "resources/sprites/player_up.anim");
   //animation_add_frame_data(player_anim_movement_up, test, 3);


    camera_init(&pl->player_camera,0,0, pl->hitbox.w, pl->hitbox.h);
    camera_set_area(&pl->player_camera, window_get()->info.width / 2, window_get()->info.height);

    return;

}

static void player_move_up(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_UP;
    pl->state = PLAYER_STATE_WALKING;
    pl->y -= pl->speed_y * delta * 0.001;
}

static void player_move_dn(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_DOWN;
    pl->state = PLAYER_STATE_WALKING;
     pl->y += pl->speed_y * delta * 0.001;
}


static void player_move_left(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_LEFT;
    pl->state = PLAYER_STATE_WALKING;
    pl->x += pl->speed_x * delta * 0.001;
}


static void player_move_right(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_RIGHT;
    pl->state = PLAYER_STATE_WALKING;
    pl->x += pl->speed_x * delta * 0.001;
}




void player_draw(player_t *pl)
{
#ifdef DEBUG
    debug_player_info(pl);
    debug_camera_render(&pl->player_camera);
#endif


    switch(pl->direction){
        case PLAYER_DIRECTION_UP:


        //sprite_draw(player_spr, pl->x, pl->y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE);
        break;

        default:
            sprite_draw(player_spr, pl->x, pl->y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE,45.0f, SDL_FLIP_NONE);
        break;
    }




    //render_texture(player_spr->texture, pl->offset_x * pl->frames, pl->offset_y * pl->direction, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, pl->x, pl->y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, 0, SDL_FLIP_NONE);

}




void player_update(player_t *pl, float delta)
{


    camera_update(&pl->player_camera, pl->x, pl->y);
    player_handle_input(pl, delta);

    player_apply_gravity(pl, delta);


    //pl->y += 80.0 * delta * 0.01;

}

void player_handle_input(player_t *pl, float delta)
{

    if(key_pressed(KEY_A) > 0){
        pl->speed_x = -30.0f;
        player_move_left(pl, delta);
    }else {
        pl->speed_x = 0.0f;
    }

    if(key_pressed(KEY_D) > 0){
        pl->speed_x = 30.0f;
        player_move_right(pl, delta);
    }else {
        pl->speed_x = 0.0f;
    }

    //player_move_up(pl, delta);
    //player_move_dn(pl, delta);





}

void player_set_pos_screen(player_t *player, int x, int y)
{
        int tx,ty;

        tx = window_get()->info.width / (x * 16);
        ty = window_get()->info.height / (y * 16);

        player->x = tx;
        player->y = ty;
}

SDL_bool player_screen_bound(player_t *player)
{
    SDL_Rect win, pl;

    win.w = window_get()->info.width;
    win.h = window_get()->info.height;
    win.x = 0;
    win.y = 0;

    pl.w = player->hitbox.w - 1;
    pl.h = player->hitbox.h - 1;
    pl.x = player->x;
    pl.y = player->y;

    return SDL_HasIntersection(&win, &pl);
}

void player_end(player_t *pl)
{
    free(pl);
    pl = NULL;

}

void player_apply_gravity(player_t *pl, float delta)
{
    pl->speed_y = 30.0f;
    pl->y += pl->speed_y * delta * 0.001;
}
