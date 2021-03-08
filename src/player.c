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



void player_init(player_t *player, int x, int y, int32_t state)
{
    player->rect.pos.x = x;
    player->rect.pos.y = y;
    player->rect.pos.w = PLAYER_TILE_SIZE;
    player->rect.pos.h = PLAYER_TILE_SIZE;

    player->state = state;
    player->hitbox_area.pos.x = x;
    player->hitbox_area.pos.y = y;
    player->hitbox_area.pos.w = player->rect.pos.w;
    player->hitbox_area.pos.h = player->rect.pos.h;
    player->speed_y = PLAYER_GRAVITY;
    player->speed_x = 0.0f;

    grect_refresh(&player->rect);
    grect_refresh(&player->hitbox_area);

    player_spr = sprite_create(resources_sprite_get("sprite2", RESOURCE_EXTENSION_PNG),0,0,32,32);
}


static void player_apply_force(float *coord, float speed, float delta){
    *coord += speed * delta;
}

static void player_handle_keyboard(player_t *player, float delta){
    game_control_t *control = keyboard_get_player_control();


    if(key_is_right(control)){
        player->speed_x = -130;
    }

    if(key_is_left(control)){
        player->speed_x = 130;
    }



}


static void player_update_coords(player_t *player, float delta){

    player->x +=  player->speed_x * delta;
    player->y +=  player->speed_y * delta;
    player->rect.pos.x = (int) player->x;
    player->rect.pos.y = (int) player->y;
    player->rect.pos.w = PLAYER_TILE_SIZE;
    player->rect.pos.h = PLAYER_TILE_SIZE;


    int center = player->rect.pos.x + (player->rect.pos.w >> 1) / 2;

    player->hitbox_area.pos.x = center;
    player->hitbox_area.pos.y = player->rect.pos.y;
    player->hitbox_area.pos.w = (player->rect.pos.w  >> 1);
    player->hitbox_area.pos.h = player->rect.pos.h;

    grect_refresh(&player->hitbox_area);
    grect_refresh(&player->rect);

}



void player_update(void *data, float delta)
{
    game_data_t *gamedata = (game_data_t*)data;
    player_t *player= &gamedata->player;

    player_update_coords(&gamedata->player, delta);
    player_handle_keyboard(&gamedata->player, delta);

    //player_apply_force(&gamedata->player.y, gamedata->player.speed_y, delta);
   // player_apply_force(&gamedata->player.x, gamedata->player.speed_x, delta);



    game_rect r;

   int collision = collision_player_detect_hit3(&gamedata->player.hitbox_area, gamedata->map, &r);

   if(collision){



       if(player->speed_y > 0 && (player->state & PLAYER_STATE_ON_GROUND) == 0 ){
           //
           gamedata->player.rect.bottom =  r.top;



           player->state |= PLAYER_STATE_ON_GROUND;
           gamedata->player.speed_y = 0;

           if((player->state & PLAYER_STATE_ON_GROUND) &&  (player->state & PLAYER_STATE_JUMPING) == PLAYER_STATE_JUMPING){
               player->state &= ~PLAYER_STATE_JUMPING;

           }

       }

   }else {
       gamedata->player.speed_y = PLAYER_GRAVITY;
       player->state &= ~PLAYER_STATE_ON_GROUND;
   }



}


void player_draw(player_t *player)
{
    sprite_draw(player_spr, player->rect.pos.x, player->rect.pos.y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE,0.0, SDL_FLIP_NONE);

}



