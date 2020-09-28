#include "player.h"
#include "resources.h"
#include "keyboard.h"
#include "window.h"
#include "log.h"
static ALLEGRO_BITMAP* player_spritesheet = NULL;


static void player_move_up(player_t *pl){
    pl->direction = PLAYER_DIRECTION_UP;
    pl->y -= 1;
}

static void player_move_dn(player_t *pl){
    pl->direction = PLAYER_DIRECTION_DOWN;
    pl->y += 1;
}


static void player_move_left(player_t *pl){
    pl->direction = PLAYER_DIRECTION_LEFT;
    pl->x -= 1;
}


static void player_move_right(player_t *pl){
    pl->direction = PLAYER_DIRECTION_RIGHT;
    pl->x += 1;
}


void player_init(player_t *pl)
{
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
    rect_init(&pl->hitbox);

    player_spritesheet = resources_sprite_get("sprite2", RESOURCE_EXTENSION_PNG);

    return;

}

void player_draw(player_t *pl)
{
    al_draw_bitmap_region(player_spritesheet, pl->offset_x * pl->frames, pl->offset_y * pl->direction, 32,32, pl->x, pl->y, 0);
    return;
}

void player_update(ALLEGRO_EVENT *ev, player_t *pl)
{



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

    if(pl->anim_counter >= 10){
        pl->anim_counter = 0;
        pl->frames++;
    }

    if(pl->frames >= pl->max_frames){
        pl->frames = 0;
    }
}

void player_handle_input(ALLEGRO_EVENT *ev, player_t *pl)
{

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
}

void player_set_pos_screen(player_t *player, int x, int y)
{
        int tx,ty;

        tx = window_get()->info.width / (x * 16);
        ty = window_get()->info.height / (y * 16);

        player->x = tx;
        player->y = ty;
}
