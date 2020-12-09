#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "sprite.h"
#include "list.h"
#include <stdio.h>

typedef enum {
    LOOP_NONE,
    LOOP_INFINITE
}loop_type;

typedef struct _sprite_animation {
    sprite_t *sprite;
    int current_frame;
    int frames;
    float angle;
    loop_type loop;
    SDL_RendererFlip flipmode;
    int x;
    int y;
    int width;
    int height;
    int delay;


}sprite_animation_t;

void animation_init(sprite_animation_t *self);
sprite_animation_t *animation_create(sprite_t *sprite, int x, int y, int frames, float angle, loop_type loop);
void animation_render(sprite_animation_t *self, int x, int y);
void animation_render_frames(link_list_t *animation_list);
int animation_add_list(link_list_t *list, sprite_animation_t *spr);
void animation_frame_destroy(sprite_animation_t *anim);
void animation_destroy(link_list_t *l);

#endif // SPRITE_ANIMATION_H
