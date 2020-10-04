#include "debug.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

void debug_render_player_hitbox(player_t *pl)
{
        al_draw_rectangle(pl->hitbox.x,pl->hitbox.y, (pl->hitbox.x + 16) + 16 , (pl->hitbox.y + 16) + 16 , al_map_rgba(255,255,0,255), 1.0);
        return;
}
