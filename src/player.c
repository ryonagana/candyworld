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
#include "game.h"
#include "tiles.h"
#include "collision.h"




static sprite_t *player_spr = NULL;

static sprite_animation *player_anim_movement_up;


animation_frame_t frames_animation_up[4] = {
 {{0,32,32,32},100,1},
 {{0,32,32,32},100,1},
 {{0,32,32,32},100,1},
 {{0,0,0,0},0,0}
};


/*
static sprite_animation_t  player_animation_up;
static sprite_animation_t  player_animation_down;
static sprite_animation_t  player_animation_left;
static sprite_animation_t  player_animation_right;
*/

link_list_t player_animation[MAX_PLAYER_ANIMATION];



/*
const int movement_order[] = {
        PLAYER_DIRECTION_DOWN,
        PLAYER_DIRECTION_LEFT,
        PLAYER_DIRECTION_RIGHT,
        PLAYER_DIRECTION_UP
};
*/




void player_init(player_t *pl){
    pl->x = 0;
    pl->y = 0;
    pl->lives = 3;
    pl->score = 0;
    pl->state |= PLAYER_STATE_ON_GROUND;
    pl->direction = PLAYER_DIRECTION_NONE;
    pl->flags = 0;
    pl->anim_counter = 0;
    pl->max_frames = 0;
    pl->frames = 0;
    pl->speed_x = 0.0f;
    pl->speed_y = 0.0f;
    //rect_init(&pl->hitbox);
    grect_empty(&pl->hitbox);

    player_spr = sprite_create(resources_sprite_get("sprite2", RESOURCE_EXTENSION_PNG),0,0,32,32);

    pl->hitbox.pos.h = player_spr->height;
    pl->hitbox.pos.w = player_spr->width;
    pl->hitbox.pos.x = player_spr->x;
    pl->hitbox.pos.y = player_spr->y;

    pl->screen_rect.pos.x = (int)pl->x;
    pl->screen_rect.pos.y = (int)pl->y;
    pl->screen_rect.pos.w = PLAYER_TILE_SIZE;
    pl->screen_rect.pos.h = PLAYER_TILE_SIZE;

    player_anim_movement_up = sprite_animation_create_empty();
    //sprite_animation_load(&player_anim_movement_up, "resources/sprites/player_up.anim");
    camera_init(&pl->player_camera,0,0, pl->hitbox.pos.w, pl->hitbox.pos.h);
    camera_set_area(&pl->player_camera, window_get()->info.width / 2, window_get()->info.height);

    return;

}

static void player_move_up(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_UP;
    pl->y += pl->speed_y * delta * 0.001;
    grect_refresh(&pl->screen_rect);
}



static void player_move_left(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_LEFT;
    pl->x += pl->speed_x * delta;
    grect_refresh(&pl->screen_rect);
}


static void player_move_right(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_RIGHT;
    pl->x += pl->speed_x * delta;
    grect_refresh(&pl->screen_rect);
}




void player_draw(player_t *pl)
{
#ifdef DEBUG
    debug_player_info(pl);
    debug_camera_render(&pl->player_camera);
#endif


            sprite_draw(player_spr, pl->screen_rect.pos.x, pl->screen_rect.pos.y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE,0.0, SDL_FLIP_NONE);



    //render_texture(player_spr->texture, pl->offset_x * pl->frames, pl->offset_y * pl->direction, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, pl->x, pl->y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, 0, SDL_FLIP_NONE);

}



static  SDL_Rect player_update_hitbox(player_t *pl, map_t *map){


    map_tileset_t *ts = &map->tilesets[0];
    UNUSED(ts);

    //
    pl->screen_rect.pos.x = (int)pl->x;
    pl->screen_rect.pos.y = (int)pl->y;
    pl->screen_rect.pos.w = PLAYER_TILE_SIZE;
    pl->screen_rect.pos.h = PLAYER_TILE_SIZE;
    grect_refresh(&pl->screen_rect);

    pl->hitbox.pos.h = PLAYER_TILE_SIZE;
    pl->hitbox.pos.w = PLAYER_TILE_SIZE >> 1;
    pl->hitbox.pos.x = pl->screen_rect.pos.x +  pl->hitbox.pos.w - (pl->hitbox.pos.w  >> 1);
    pl->hitbox.pos.y = pl->screen_rect.pos.y;
    grect_refresh(&pl->hitbox);



    return pl->hitbox.pos;
}


void player_update2(void* data, float delta){
    game_data_t *gamedata = (game_data_t*)data;
    player_t *pl = &gamedata->player;
    map_t *map = gamedata->map;

    camera_update(&pl->player_camera, (int)pl->x, (int)pl->y);
    player_handle_input(pl, delta);
    player_update_hitbox(pl, map);
    player_move(pl, map, delta);


}


void player_handle_input(player_t *pl, float delta)
{
    if(key_pressed(KEY_A) > 0){
        pl->state |= PLAYER_STATE_WALKING;
        pl->speed_x = -80.0f;
        player_move_left(pl, delta);
    }else {
        pl->state &= ~PLAYER_STATE_WALKING;
        pl->speed_x = 0.0f;
    }

    if(key_pressed(KEY_D) > 0){
        pl->speed_x = 80.0f;
        pl->state |= PLAYER_STATE_WALKING;
        player_move_right(pl, delta);
    }else {
        pl->speed_x = 0.0f;
        pl->state &= ~PLAYER_STATE_WALKING;
    }


    if(key_pressed(KEY_SPACE) && BITMASK(pl->state, PLAYER_STATE_ON_GROUND)){
        pl->speed_y = -10.0f;
        pl->y -= pl->speed_y * delta;
        pl->state |= PLAYER_STATE_JUMPING;
        pl->state &= ~PLAYER_STATE_ON_GROUND;
    }else {
          pl->state |= PLAYER_STATE_ON_GROUND;
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

    pl.w = player->hitbox.pos.w - 1;
    pl.h = player->hitbox.pos.h - 1;
    pl.x = (int)player->x;
    pl.y = (int)player->y;

    return SDL_HasIntersection(&win, &pl);
}

void player_end(player_t *pl)
{
    free(pl);
    pl = NULL;

}

void player_apply_gravity(player_t *pl, float delta, float force)
{
    if(BITMASK(pl->state, PLAYER_STATE_ON_GROUND)){
        pl->speed_y = force;
        pl->y += pl->speed_y * delta;
        grect_refresh(&pl->screen_rect);
        return;
    }


    pl->speed_y = 0.0;
}



void player_move(player_t *player, map_t *map, float delta)
{

    player_apply_gravity(player, delta, 400);


    game_rect old_player= player->screen_rect;
    game_rect tile_rect;

    int collision = collision_player_detect_hit3(&player->hitbox, map, &tile_rect);

    if(collision && !BITMASK(player->state, PLAYER_STATE_ON_GROUND)){

        player->screen_rect.bottom = tile_rect.top + 10;
        grect_refresh(&player->screen_rect);
        player->state &= ~PLAYER_STATE_ON_GROUND;
    }else {
        player->state |= PLAYER_STATE_ON_GROUND;
    }


#if DEBUG
    if(player->screen_rect.pos.y > 1000){
        player->y = 0;
        grect_refresh(&player->screen_rect);
    }
#endif


}
