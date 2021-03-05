#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "sprite.h"
#include "list.h"
#include <stdio.h>

#define ANIMATION_MAX 20

typedef struct animation_frame_t {
    SDL_Rect pos;
    int delay;
    int use;
}animation_frame_t;


typedef struct sprite_animation {
    animation_frame_t *frames;
    int frame_count;
    int index;
    int num_frames_added;
}sprite_animation;


sprite_animation  *sprite_animation_create_empty();
sprite_animation  *sprite_animation_create(int animation_num);
animation_frame_t *animation_create_array(int size);
size_t             animation_count(animation_frame_t frames[ANIMATION_MAX]);
void               sprite_animation_update_size(sprite_animation *spr);
void               animation_free(animation_frame_t *f);
void               sprite_animation_free(sprite_animation *spr);
void               animation_resize_array(sprite_animation *spr, int size);
animation_frame_t *animation_frame_init();


void              animation_add_frame(sprite_animation *spr, int x, int y, int width, int height, int delay);
void              animation_add_frame2(sprite_animation *spr, SDL_Rect pos, int delay);
void              animation_add_frame_data(sprite_animation *spr, animation_frame_t *frames, int size);

#endif // SPRITE_ANIMATION_H
