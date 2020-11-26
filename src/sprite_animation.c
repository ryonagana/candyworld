#include "sprite_animation.h"
#include "log.h"
#include <string.h>

static sprite_animation_frame_t* sprite_animation_alloc_frames(int frame_count){
    sprite_animation_frame_t *tmp = NULL;
    tmp = calloc(frame_count, sizeof(sprite_animation_frame_t));
    tmp->next = NULL;
    return tmp;
}

sprite_animation_frame_t* sprite_animation_frame_set(int id, int x, int y, int w, int h, int delay){
    sprite_animation_frame_t *tmp = NULL;

    tmp = sprite_animation_alloc_frames(1);
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

int sprite_animation_load(sprite_animation_t *anim, int row, int tile_width, int tile_height,  int max_cols, int delay[]){


    int i;

    sprite_animation_frame_t *ret_frame = NULL;
    ret_frame = sprite_animation_alloc_frames(1);

    if(!ret_frame){
        DCRITICAL("failed to load sprite animation");
        return 0;
    }

    for(i = 0; i < max_cols; i++){
         sprite_animation_frame_t *frame = NULL;

          frame =  sprite_animation_alloc_frames(1);
          frame->delay = delay[i];
          frame->frame_id = i;
          frame->x = i * tile_width;
          frame->y = row;
          frame->width = tile_width;
          frame->height = tile_height;
          frame->next = NULL;
          sprite_animation_add_frame(anim, frame);
    }

    return 1;
}



void sprite_animation_update(sprite_animation_t *anim)
{

    sprite_animation_frame_t *start = anim->head;
    static Uint32  time = 0;




    while(start != NULL){

        if(time == 0) time = SDL_GetTicks();


        if(SDL_GetTicks() - start->delay > time){
            time = SDL_GetTicks();

            if(anim->actual_frame >= anim->max_frames){
                if(!anim->repeat) anim->actual_frame = anim->max_frames;

                anim->actual_frame = 0;

            }else {
                anim->actual_frame++;
            }

        }

        start = start->next;
    }

}
