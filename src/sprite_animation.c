#include "sprite_animation.h"
#include <string.h>

static sprite_animation_frame_t* sprite_animation_alloc_frames(){
    sprite_animation_frame_t *tmp = NULL;
    tmp = calloc(1, sizeof(sprite_animation_frame_t));
    tmp->next = NULL;
    return tmp;
}

sprite_animation_frame_t* sprite_animation_frame_set(int id, int x, int y, int w, int h, int delay){
    sprite_animation_frame_t *tmp = NULL;

    tmp = sprite_animation_alloc_frames();
    tmp->x = x;
    tmp->y = y;
    tmp->width = w;
    tmp->height = h;
    tmp->delay = delay;
    tmp->frame_id = id;

    return tmp;

}




void sprite_animation_add_frame(sprite_animation_t *anim, sprite_animation_frame_t* frame){
        if(anim->frames == NULL){
            anim->frames = frame;
            anim->head = anim->frames;
            anim->frame_count++;
            return;
        }


         anim->frames->next = frame;
         anim->frames = anim->frames->next;
         anim->frame_count++;
}

void sprite_animation_start(sprite_animation_t *anim, sprite_t *spritesheet)
{
    anim->actual_frame = 0;
    anim->frame_count = 0;
    anim->frames = NULL;
    anim->play = 0;
    anim->repeat = 0;
    anim->max_frames = spritesheet->cols;
    anim->sprite =  spritesheet;
}

