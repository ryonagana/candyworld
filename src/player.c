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
    pl->state = PLAYER_STATE_NONE;
    pl->direction = PLAYER_DIRECTION_NONE;
    pl->flags = 0;
    pl->anim_counter = 0;
    pl->max_frames = 0;
    pl->frames = 0;
    pl->speed_x = 0.0f;
    pl->speed_y = 0.0f;
    //rect_init(&pl->hitbox);
    SDL_RectEmpty(&pl->hitbox);

    player_spr = sprite_create(resources_sprite_get("sprite2", RESOURCE_EXTENSION_PNG),0,0,32,32);

    pl->hitbox.h = player_spr->height;
    pl->hitbox.w = player_spr->width;
    pl->hitbox.x = player_spr->x;
    pl->hitbox.y = player_spr->x;

    player_anim_movement_up = sprite_animation_create_empty();
    sprite_animation_load(&player_anim_movement_up, "resources/sprites/player_up.anim");
    camera_init(&pl->player_camera,0,0, pl->hitbox.w, pl->hitbox.h);
    camera_set_area(&pl->player_camera, window_get()->info.width / 2, window_get()->info.height);
    pl->is_falling = 0;
    return;

}

static void player_move_up(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_UP;
    pl->state = PLAYER_STATE_WALKING;
    pl->y -= pl->speed_y * delta * 0.001f;
    game_rect_update_rect(&pl->screen_rect);
}

static void player_move_dn(player_t *pl, float delta){
     pl->direction = PLAYER_DIRECTION_DOWN;
     pl->state = PLAYER_STATE_WALKING;
     pl->y += pl->speed_y * delta * 0.001f;
     game_rect_update_rect(&pl->screen_rect);
}


static void player_move_left(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_LEFT;
    pl->state = PLAYER_STATE_WALKING;
    pl->x += pl->speed_x * delta * 0.001f;
    game_rect_update_rect(&pl->screen_rect);
}


static void player_move_right(player_t *pl, float delta){
    pl->direction = PLAYER_DIRECTION_RIGHT;
    pl->state = PLAYER_STATE_WALKING;
    pl->x += pl->speed_x * delta * 0.001f;
    game_rect_update_rect(&pl->screen_rect);
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


    map_tileset *ts = &map->tilesets[0];

    pl->hitbox.h = PLAYER_TILE_SIZE;
    pl->hitbox.w = PLAYER_TILE_SIZE;
    pl->hitbox.x = (int)pl->x;
    pl->hitbox.y = (int)pl->y;

    //
    pl->screen_rect.pos.x = (int)pl->x;
    pl->screen_rect.pos.y = (int)pl->y;
    pl->screen_rect.pos.w = PLAYER_TILE_SIZE;
    pl->screen_rect.pos.h = PLAYER_TILE_SIZE;
    game_rect_update_rect(&pl->screen_rect);


    //head left
    pl->hitboxes[0].pos.x = pl->screen_rect.pos.x;
    pl->hitboxes[0].pos.y = pl->screen_rect.pos.y;
    pl->hitboxes[0].pos.w = map->tilesets[0].tile_width;
    pl->hitboxes[0].pos.h = map->tilesets[0].tile_height;
    game_rect_update_rect(&pl->hitboxes[0]);

    //head right
    pl->hitboxes[1].pos.x = pl->screen_rect.pos.x / ts->tile_width + ts->tile_width * ts->tile_width;
    pl->hitboxes[1].pos.y = pl->screen_rect.pos.y;
    pl->hitboxes[1].pos.w = map->tilesets[0].tile_width;
    pl->hitboxes[1].pos.h = map->tilesets[0].tile_height;
    game_rect_update_rect(&pl->hitboxes[1]);
    //foot left
    pl->hitboxes[2].pos.x = pl->screen_rect.pos.x;
    pl->hitboxes[2].pos.y = pl->screen_rect.pos.y / ts->tile_height + ts->tile_height * ts->tile_height;
    pl->hitboxes[2].pos.w = map->tilesets[0].tile_width;
    pl->hitboxes[2].pos.h = map->tilesets[0].tile_height;
    game_rect_update_rect(&pl->hitboxes[2]);
    //foot right
    pl->hitboxes[3].pos.x = pl->screen_rect.pos.x / ts->tile_height + ts->tile_width * ts->tile_width;
    pl->hitboxes[3].pos.y = pl->screen_rect.pos.y / ts->tile_height + ts->tile_height * ts->tile_height;
    pl->hitboxes[3].pos.w = map->tilesets[0].tile_width;
    pl->hitboxes[3].pos.h = map->tilesets[0].tile_height;
    game_rect_update_rect(&pl->hitboxes[3]);




    return pl->hitbox;
}


void player_update2(void* data, float delta){
    game_data_t *gamedata = (game_data_t*)data;
    player_t *pl = &gamedata->player;
    map_t *map = gamedata->map;

    camera_update(&pl->player_camera, (int)pl->x, (int)pl->y);
    player_handle_input(pl, delta);
    player_update_hitbox(pl, map);

    if(pl->is_falling == PLAYER_STATE_FALLING){
         player_apply_gravity(pl, delta);
    }

    player_move(pl, map, delta);


}


void player_handle_input(player_t *pl, float delta)
{

    if(key_pressed(KEY_A) > 0){
        pl->speed_x = -130.0f;
        player_move_left(pl, delta);
    }else {
        pl->speed_x = 0.0f;
    }

    if(key_pressed(KEY_D) > 0){
        pl->speed_x = 130.0f;
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
    pl.x = (int)player->x;
    pl.y = (int)player->y;

    return SDL_HasIntersection(&win, &pl);
}

void player_end(player_t *pl)
{
    free(pl);
    pl = NULL;

}

void player_apply_gravity(player_t *pl, float delta)
{
    pl->speed_y = 70.0f;
    pl->y += pl->speed_y * delta * 0.001f;
}



void player_move(player_t *player, map_t *map, float delta)
{




   int i;


   for(i = 0; i < 4; i++){
       game_rect_t is_hit;

       if(collision_player_detect_hit(&player->hitboxes[i], map, &is_hit)){
           if(player->speed_y > 0){
               player->screen_rect.bottom = is_hit.top;
               player->is_falling = PLAYER_STATE_ON_GROUND;
           }else if(player->speed_y < 0){
               player->screen_rect.top = is_hit.bottom;
               player->is_falling = PLAYER_STATE_ON_GROUND;
           }
       }else {
           player->is_falling = PLAYER_STATE_FALLING;
       }
   }




   /*
   game_rect_t hit_rect;

    if(collision_player_detect_hit(player,map, &hit_rect)){

        game_rect_update_rect(&player->screen_rect);
        if(player->speed_y > 0){
           player->screen_rect.bottom = hit_rect.bottom;
            player->is_falling = PLAYER_STATE_ON_GROUND;
        }




         DLOG("scr: %d %d %d %d t: %d b: %d l:%d r%d",
              player->screen_rect.rect.x,
              player->screen_rect.rect.y,
              player->screen_rect.rect.w,
              player->screen_rect.rect.h,

              player->screen_rect.top,
              player->screen_rect.bottom,
              player->screen_rect.left,
              player->screen_rect.right
              );

    }else {
         player->is_falling =  PLAYER_STATE_FALLING;
    }

    */


}
