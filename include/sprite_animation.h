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
    int x;
    int y;


}sprite_animation_t;

void animation_init(sprite_animation_t *self);
sprite_animation_t *animation_create(sprite_t *sprite, int x, int y, int frames, float angle, loop_type loop);
void animation_render(sprite_animation_t *self);

#endif // SPRITE_ANIMATION_H
