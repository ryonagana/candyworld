#ifndef HUD_HEADER
#define HUD_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hud_t {
    int lives;
    int candies;
    int sugar_rush;
    int x;
    int y;
    int width;
    int height;

    int lives_x;
    int lives_y;
};
typedef  struct hud_t hud_t;


void hud_init();
void hud_set(const hud_t new_hud);
void hud_draw();
void hud_update();
hud_t *hud_get();

#endif
