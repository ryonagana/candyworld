#include "hud.h"
#include "lua_vm.h"
#include "lua_hud.h"

static hud_t game_hud;

void hud_init()
{
    game_hud.x = 0;
    game_hud.y = 0;
    game_hud.lives = 0;
    game_hud.width = 0;
    game_hud.height = 0;
    game_hud.candies = 0;
    game_hud.sugar_rush = 0;
    game_hud.lives_x = 0;
    game_hud.lives_y = 0;
}

void hud_draw()
{


}

void hud_update()
{

}

hud_t *hud_get()
{
    return &game_hud;
}

void hud_set(const hud_t new_hud)
{
    hud_init();
    memcpy(&game_hud, &new_hud, sizeof (hud_t));
}
