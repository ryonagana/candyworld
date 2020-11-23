#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "sprite.h"
#include <stdio.h>

typedef struct sprite_animation_frame_t {
    int frame_id;
    int x;
    int y;
    int width;
    int height;
    int delay;
    struct sprite_animation_frame_t *next;
}sprite_animation_frame_t;

typedef struct sprite_animation_t {
    sprite_t *sprite;
    sprite_animation_frame_t *frames;
    sprite_animation_frame_t *head;
    int frame_count;
    int actual_frame;
    int max_frames;
    int repeat;
    int play;

}sprite_animation_t;


void sprite_animation_start(sprite_animation_t *anim, sprite_t *spritesheet);



sprite_animation_frame_t* sprite_animation_frame_set(int x, int y, int w, int h, int delay);
void sprite_animation_add_frame(sprite_animation_t *anim, sprite_animation_frame_t* frame);

#endif // SPRITE_ANIMATION_H
