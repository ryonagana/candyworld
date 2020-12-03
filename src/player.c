#include "player.h"
#include "resources.h"
#include "keyboard.h"
#include "window.h"
#include "log.h"
#include "render.h"
#include "debug.h"
#include "sprite.h"
#include "sprite_animation.h"






static sprite_t *player_spr = NULL;


static sprite_animation_t  player_animation_up;
static sprite_animation_t  player_animation_down;
static sprite_animation_t  player_animation_left;
static sprite_animation_t  player_animation_right;



const int movement_order[] = {
        PLAYER_DIRECTION_DOWN,
        PLAYER_DIRECTION_LEFT,
        PLAYER_DIRECTION_RIGHT,
        PLAYER_DIRECTION_UP
};



static int anim_delay[8] = {
    100,
    100,
    100,
    100,
    50,
    50,
    50,
    50
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
    //rect_init(&pl->hitbox);
    SDL_RectEmpty(&pl->hitbox);




    sprite_init(&player_spr, resources_sprite_get("sprite2", RESOURCE_EXTENSION_PNG));
    sprite_set_spritesheet_offset(player_spr, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE);
    sprite_set_delay(player_spr, anim_delay, 8);

    camera_init(&pl->player_camera,0,0, pl->hitbox.w, pl->hitbox.h);
    camera_set_area(&pl->player_camera, window_get()->info.width / 2, window_get()->info.height);


    sprite_animation_start(&player_animation_up, player_spr);
    sprite_animation_start(&player_animation_down, player_spr);
    sprite_animation_start(&player_animation_left, player_spr);
    sprite_animation_start(&player_animation_right, player_spr);




    sprite_animation_load(&player_animation_up, 0, 32,32, 5, anim_delay);



    return;

}

static void player_move_up(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_UP;
    pl->state = PLAYER_STATE_WALKING;
    pl->y -= PLAYER_SPEED * delta * 0.01;
}

static void player_move_dn(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_DOWN;
    pl->state = PLAYER_STATE_WALKING;
     pl->y += PLAYER_SPEED * delta * 0.01;
}


static void player_move_left(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_LEFT;
    pl->state = PLAYER_STATE_WALKING;
    pl->x -= PLAYER_SPEED * delta * 0.01;
}


static void player_move_right(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_RIGHT;
    pl->state = PLAYER_STATE_WALKING;
    pl->x += PLAYER_SPEED * delta * 0.01;
}




void player_draw(player_t *pl)
{
#ifdef DEBUG
    debug_player_info(pl);
    debug_camera_render(&pl->player_camera);
#endif


    switch(pl->direction){
        case PLAYER_DIRECTION_UP:
        sprite_animation_draw(&player_animation_up, pl->x, pl->y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, SDL_FLIP_NONE);

        //sprite_draw(player_spr, pl->x, pl->y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE);
        break;

        default:
            sprite_draw(player_spr, pl->x, pl->y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE);
        break;
    }




    //render_texture(player_spr->texture, pl->offset_x * pl->frames, pl->offset_y * pl->direction, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, pl->x, pl->y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, 0, SDL_FLIP_NONE);

}



static void player_direction_none(player_t *pl, sprite_t *spr){
        int dir = pl->direction;
        int old = movement_order[dir];

        spr->end_frame = old * pl->direction;
}

void player_update(player_t *pl, float delta)
{


    camera_update(&pl->player_camera, pl->x, pl->y);
    player_handle_input(pl, delta);

    switch(pl->direction){
        case PLAYER_DIRECTION_UP:
        player_animation_up.max_frames = (pl->state == PLAYER_STATE_WALKING) ? 12 : 1;
        sprite_animation_set_anim(&player_animation_up, PLAYER_DIRECTION_UP);
        sprite_animation_update(&player_animation_up);
        break;
    }

    //pl->y += 80.0 * delta * 0.01;

}

void player_handle_input(player_t *pl, float delta)
{

    if(key_pressed(KEY_W) > 0){
        player_move_up(pl, delta);
    }else if(key_pressed(KEY_S) > 0){
        player_move_dn(pl, delta);
    }else if(key_pressed(KEY_A) > 0){
        player_move_left(pl, delta);
    }else if(key_pressed(KEY_D) > 0){
        player_move_right(pl, delta);
    }else {
         player_direction_none(pl, player_spr);
    }


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
