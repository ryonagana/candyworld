#include "sprite_animation.h"
#include "log.h"
#include "render.h"
#include "std.h"
#include <string.h>
#include <assert.h>

static sprite_animation* sprite_animation_alloc(){
    sprite_animation *anim = NULL;
    anim = mem_alloc(sizeof(sprite_animation)); //malloc(sizeof (sprite_animation));

    if(!anim){
        DCRITICAL("sprite_animation_create(): Critical Error: cannot allocate sprite animation");
        return NULL;
    }

    anim->frame_count = 0;
    anim->frames = NULL;
    anim->index = 0;

    return anim;
}


sprite_animation *sprite_animation_create(int animation_num)
{

    sprite_animation* self = NULL;
    self = sprite_animation_alloc();


    self->frames = animation_create_array(animation_num);
    self->frame_count = animation_num;
    self->index = 0;


    return self;

}

sprite_animation *sprite_animation_create_empty()
{
    sprite_animation* self = NULL;
    self = sprite_animation_alloc();


    self->frames = animation_create_array(ANIMATION_MAX);
    self->frame_count = 0;
    self->index = 0;


    return self;
}


animation_frame_t *animation_frame_init()
{
    animation_frame_t *frame = NULL;

    frame = mem_alloc(sizeof(animation_frame_t));
    frame->delay = 0;
    frame->pos = (SDL_Rect){0,0,0,0};
    frame->use = 0;
    return frame;
}

animation_frame_t *animation_create_array(int size)
{
    animation_frame_t *frame = NULL;
    frame = mem_calloc(size, sizeof (animation_frame_t));

    if(!frame){
        DCRITICAL("animation_create_array(): failed to create animation");
        return NULL;
    }

    return frame;

}

void animation_free(animation_frame_t *f)
{
    mem_free((void*)f);
}

void sprite_animation_free(sprite_animation *spr)
{
    if(!spr) return;

    if(spr->frames){
        animation_free(spr->frames);
    }

    mem_free((void*)spr);
}

void animation_resize_array(sprite_animation *spr, int size)
{
    if(size < spr->frame_count){
        DLOG("animation_resize_array resizing failed");
        return;
    }

    void *blk = NULL;
    blk = mem_realloc(spr->frames, sizeof(animation_frame_t) * size);
    spr->frames = blk;
    spr->frame_count = size;

    return;
}

void animation_add_frame(sprite_animation *spr, int x, int y, int width, int height, int delay)
{
    animation_frame_t *frame  = NULL;
    frame = animation_frame_init();

    if(!frame){
        return;
    }

    frame->pos = (SDL_Rect){x,y,width,height};
    frame->delay = delay;
    frame-> use = 1;

    if(!spr->frames){
        DCRITICAL("animation_add_frame():  frame array is NULL");
        return;
    }

    spr->frames[spr->num_frames_added] = *frame;
    spr->num_frames_added++;
}

void animation_add_frame2(sprite_animation *spr, SDL_Rect pos, int delay)
{
    animation_add_frame(spr, pos.x, pos.y, pos.w, pos.h, delay);
    return;
}

size_t animation_count(animation_frame_t frames[ANIMATION_MAX]){
    int counter = 0;
    int i;

    for(i = 0; i < ANIMATION_MAX; i++){
        if(!frames[i].use) continue;
        counter++;
    }

    return counter;
}

void animation_add_frame_data(sprite_animation *spr, animation_frame_t *frames, int size)
{

    memcpy(spr->frames, frames, sizeof(animation_frame_t) * size);
    spr->frame_count = size;
    return;

}


void sprite_animation_update_size(sprite_animation *spr)
{
    int c = animation_count(spr->frames);
    spr->frame_count = c;
}

