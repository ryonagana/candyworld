#include "sprite_animation.h"
#include "log.h"
#include "render.h"
#include <string.h>
#include <assert.h>

static sprite_animation_frame_t* sprite_animation_alloc_frames(int frame_count){
    sprite_animation_frame_t *tmp = NULL;
    tmp = calloc(frame_count, sizeof(sprite_animation_frame_t));
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





void sprite_animation_start(sprite_animation_t *anim, sprite_t *spritesheet)
{
    anim->actual_frame = 0;
    anim->frame_count = 0;
    //anim->frames = NULL;
    anim->play = 0;
    anim->repeat = 0;
    anim->max_frames = spritesheet->cols;
    anim->sprite =  spritesheet;
    anim->x = 0;
    anim->y = 0;
}

int sprite_animation_load(sprite_animation_t *anim, int row, int tile_width, int tile_height,  int max_cols, int delay[]){



    //sprite_animation_frame_t *tmp_frame = sprite_animation_alloc_frames(max_cols);
    int w,h;

    SDL_QueryTexture(anim->sprite->texture,NULL, NULL, &w,&h);

    anim->rows = abs(h / tile_width);
    anim->cols = abs(w / tile_height);
    anim->max_frames = max_cols;

    /*
    for(i = 0; i < max_cols; i++){
         sprite_animation_frame_t *frame = &tmp_frame[i];
          frame->delay = delay[i];
          frame->frame_id = i;
          frame->x = i * tile_width;
          frame->y = row;
          frame->width = tile_width;
          frame->height = tile_height;
    }

    anim->frames = tmp_frame;
    */


    return 1;
}



void sprite_animation_update(sprite_animation_t *anim)
{



    static Uint32 time = 0;
    //sprite_animation_frame_t *frame = &anim->frames[anim->actual_frame];

    int w,h;

    SDL_QueryTexture(anim->sprite->texture,NULL, NULL, &w,&h);

    anim->rows = h / abs(h / 32);
    anim->cols = w / abs(w / 32);

    if(time == 0) time = SDL_GetTicks();


    if(SDL_GetTicks() -  500 > time){
        time = SDL_GetTicks();

            if(anim->actual_frame >= anim->max_frames){
                if(!anim->repeat) anim->actual_frame = anim->max_frames;

                anim->actual_frame = 0;

            }else {
                anim->actual_frame++;
            }



    }

    /*
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

            start = start->next;
            anim->frame_ptr = start;
        }

    }

    */

}



void sprite_animation_draw(sprite_animation_t *anim, int x, int y, int w, int h, int flipmode)
{
    render_texture(anim->sprite->texture,  anim->cols * anim->actual_frame, anim->rows * anim->current_animation, anim->sprite->pos.w, anim->sprite->pos.h, x,y, w,h,0, flipmode);
    return;
}


void sprite_animation_set_anim(sprite_animation_t *anim, int anim_id)
{
    anim->current_animation = anim_id;
}
