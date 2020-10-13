#include "player.h"
#include "resources.h"
#include "keyboard.h"
#include "window.h"
#include "log.h"
//#include "debug.h"


static SDL_Texture* player_spritesheet = NULL;


static void player_move_up(player_t *pl){
    pl->direction = PLAYER_DIRECTION_UP;
    pl->y -= 1 * PLAYER_SPEED;
}

static void player_move_dn(player_t *pl){
    pl->direction = PLAYER_DIRECTION_DOWN;
    pl->y += 1 * PLAYER_SPEED;
}


static void player_move_left(player_t *pl){
    pl->direction = PLAYER_DIRECTION_LEFT;
    pl->x -= 1 * PLAYER_SPEED;
}


static void player_move_right(player_t *pl){
    pl->direction = PLAYER_DIRECTION_RIGHT;
    pl->x += 1 * PLAYER_SPEED;
}


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

    player_spritesheet = resources_sprite_get("sprite2", RESOURCE_EXTENSION_PNG);

    return;

}

void player_draw(player_t *pl)
{
#ifdef DEBUG
   // debug_render_player_hitbox(pl);
#endif
    int tex_width, tex_height;

    SDL_QueryTexture(player_spritesheet, NULL, NULL, &tex_width, &tex_height);

    SDL_Rect orig, dest;

    orig.x = pl->frames;
    orig.y = pl->direction;
    orig.w = 32;
    orig.h = 32;

    dest.x = pl->x;
    dest.y = pl->y;
    dest.w = 32;
    dest.h = 32;

    //SDL_RenderCopyEx(window_get()->events.renderer, player_spritesheet,&orig, &dest, 0, NULL, 0);
    SDL_RenderCopy(window_get()->events.renderer, player_spritesheet, &orig, &dest);
    //al_draw_bitmap_region(player_spritesheet, pl->offset_x * pl->frames, pl->offset_y * pl->frames, 32,32, pl->x, pl->y, 0);
    return;
}

void player_update(player_t *pl, Uint32 delta)
{

    SDL_QueryTexture(player_spritesheet, NULL, NULL, &pl->offset_x, &pl->offset_y);
    //pl->offset_x = al_get_bitmap_width(player_spritesheet) / 12;
    //pl->offset_y = al_get_bitmap_height(player_spritesheet) / 8;

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
    }

    Uint32 animTime = SDL_GetTicks();

    if(animTime > pl->anim_counter + 100){
        pl->frames++;
        pl->anim_counter = animTime;
    }

    if(pl->frames >= pl->max_frames){
        pl->frames = 0;
    }


    /*

    rect_set(&pl->hitbox, pl->x, pl->y, 32,32);

    pl->offset_x = al_get_bitmap_width(player_spritesheet) / 12;
    pl->offset_y = al_get_bitmap_height(player_spritesheet) / 8;

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
    }

    if(pl->anim_counter++ >= 10){
        pl->anim_counter = 0;
        pl->frames++;
    }

    if(pl->frames >= pl->max_frames){
        pl->frames = 0;
    }

    */

}

void player_handle_input(player_t *pl)
{

    if(key_pressed(SDL_SCANCODE_W)){
        player_move_up(pl);
    }

    if(key_pressed(SDL_SCANCODE_S)){
        player_move_dn(pl);
    }

    if(key_pressed(SDL_SCANCODE_A)){
        player_move_left(pl);
    }


    if(key_pressed(SDL_SCANCODE_D)){
        player_move_right(pl);
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
