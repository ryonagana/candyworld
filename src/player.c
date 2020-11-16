#include "player.h"
#include "resources.h"
#include "keyboard.h"
#include "window.h"
#include "log.h"
#include "render.h"
#include "debug.h"
#include "sprite.h"




static sprite_t *player_spr = NULL;


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




    static SDL_Texture* player_spritesheet = NULL;
    player_spritesheet = resources_sprite_get("sprite2", RESOURCE_EXTENSION_PNG);
    sprite_init(&player_spr, player_spritesheet);
    sprite_set_spritesheet_offset(player_spr, 8, 12);
    sprite_set_delay(player_spr, anim_delay, 8);

    return;

}

static void player_move_up(player_t *pl, Uint32 delta){
    pl->direction = PLAYER_DIRECTION_UP;
    pl->state = PLAYER_STATE_WALKING;
    pl->y -= 1 * PLAYER_SPEED ;
}

static void player_move_dn(player_t *pl, Uint32 delta){
    pl->direction = PLAYER_DIRECTION_DOWN;
    pl->state = PLAYER_STATE_WALKING;
    pl->y += 1 * PLAYER_SPEED ;
}


static void player_move_left(player_t *pl, Uint32 delta){
    pl->direction = PLAYER_DIRECTION_LEFT;
    pl->state = PLAYER_STATE_WALKING;
    pl->x -= 1 * PLAYER_SPEED ;
}


static void player_move_right(player_t *pl, Uint32 delta){
    pl->direction = PLAYER_DIRECTION_RIGHT;
    pl->state = PLAYER_STATE_WALKING;
    pl->x += 1 * PLAYER_SPEED;
}




void player_draw(player_t *pl)
{
#ifdef DEBUG
    debug_render_player_hitbox(pl);
#endif

    sprite_draw(player_spr, pl->x, pl->y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE);

    //render_texture(player_spr->texture, pl->offset_x * pl->frames, pl->offset_y * pl->direction, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, pl->x, pl->y, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE, 0, SDL_FLIP_NONE);

}

void player_update(player_t *pl, Uint32 delta)
{

    int w,h;

    UNUSED(delta);

    SDL_QueryTexture(player_spr->texture, NULL, NULL, &w, &h);
    pl->offset_x = w  /  abs((w / PLAYER_TILE_SIZE));
    pl->offset_y = h  /  abs((h / PLAYER_TILE_SIZE));



    switch(pl->direction){
        case PLAYER_DIRECTION_UP:
            pl->max_frames = (pl->state == PLAYER_STATE_WALKING) ? 6 : 1;
        break;

        case PLAYER_DIRECTION_DOWN:
            pl->max_frames = (pl->state == PLAYER_STATE_WALKING) ? 6 : 1;
        break;

        case PLAYER_DIRECTION_LEFT:
            pl->max_frames = (pl->state == PLAYER_STATE_WALKING) ? 6 : 1;
        break;

        case PLAYER_DIRECTION_RIGHT:
            pl->max_frames = (pl->state == PLAYER_STATE_WALKING) ? 6 : 1;
        break;

        case PLAYER_DIRECTION_NONE:
            pl->max_frames = (pl->state != PLAYER_STATE_WALKING) ? 1 : 1;
            break;
    }



       sprite_update(player_spr);
/*
    if(SDL_GetTicks() > pl->anim_counter + player_spr->delay[pl->frames]){
        pl->frames++;
        pl->anim_counter = SDL_GetTicks();

    }

    if(pl->frames == pl->max_frames){
        pl->frames = 0;
    }
*/




}

void player_handle_input(player_t *pl, Uint32 delta)
{

    if(key_pressed(SDL_SCANCODE_W) > 0){
        player_move_up(pl, delta);
    }else if(key_pressed(SDL_SCANCODE_S) > 0){
        player_move_dn(pl, delta);
    }else if(key_pressed(SDL_SCANCODE_A) > 0){
        player_move_left(pl, delta);
    }else if(key_pressed(SDL_SCANCODE_D) > 0){
        player_move_right(pl, delta);
    }else {
        pl->direction = PLAYER_DIRECTION_NONE;
        pl->state = PLAYER_STATE_IDLE;
    }


    /*
    UNUSED((ev));

    if(key_is_pressed(ALLEGRO_KEY_A)){
        player_move_left(pl);
    }else  if(key_is_pressed(ALLEGRO_KEY_D)){
        player_move_right(pl);
    }else  if(key_is_pressed(ALLEGRO_KEY_W)){
        player_move_up(pl);
    }else  if(key_is_pressed(ALLEGRO_KEY_S)){
        player_move_dn(pl);
    }else {
        pl->direction = PLAYER_DIRECTION_NONE;
    }
    */

/*
    if(key_is_pressed(ALLEGRO_KEY_W)){
        player_move_up(pl);
        DLOG("pressed W");
    }else if(key_is_pressed(ALLEGRO_KEY_S)){
        player_move_dn(pl);
    }else if(key_is_pressed(ALLEGRO_KEY_A)){
        player_move_left(pl);
    }else  if(key_is_pressed(ALLEGRO_KEY_D)){
        player_move_right(pl);
    }else {
        pl->direction = PLAYER_DIRECTION_NONE;
        pl->state = PLAYER_STATE_IDLE;
    }
*/
}

void player_set_pos_screen(player_t *player, int x, int y)
{
        int tx,ty;

        tx = window_get()->info.width / (x * 16);
        ty = window_get()->info.height / (y * 16);

        player->x = tx;
        player->y = ty;
}

int player_screen_bound(player_t *player)
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
