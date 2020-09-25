#include "player.h"
#include "resources.h"

void player_init(player_t *pl)
{
    pl->x = 0;
    pl->y = 0;
    pl->lives = 3;
    pl->score = 0;
    pl->state = PLAYER_STATE_NONE;
    pl->direction = PLAYER_DIRECTION_NONE;
    rect_init(&pl->hitbox);
    return;

}

void player_draw(player_t *pl)
{
    ALLEGRO_BITMAP *bmp = resources_sprite_get("sprite2", RESOURCE_EXTENSION_PNG);

    al_draw_bitmap(bmp, 0,0,0);
    return;
}

void player_update(player_t *pl)
{

}
