#include "sprite_animation.h"
#include "log.h"
#include "render.h"
#include <string.h>
#include <assert.h>



void animation_init(sprite_animation_t *self)
{
    self->sprite = NULL;
    self->angle = 0;
    self->frames = 0;
    self->current_frame = 0;
    self->loop = LOOP_NONE;
    self->x = 0;
    self->y = 0;
}



sprite_animation_t *animation_create(sprite_t *sprite, int x, int y, int frames, float angle, loop_type loop)
{
    sprite_animation_t *self = NULL;
    self = malloc(sizeof(sprite_animation_t));

    if(!self) return self;
    animation_init(self);
    self->x = x;
    self->y = y;
    self->frames = frames;
    self->angle = angle;
    self->sprite = sprite;
    self->loop = loop;

    return self;

}


void animation_render(sprite_animation_t *self)
{

}

