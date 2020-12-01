#include "sprite.h"
#include "resources.h"
#include "shared.h"
#include "log.h"
#include "render.h"

static sprite_t *sprite_alloc_mem(size_t num){

    sprite_t *spr_tmp = NULL;

    if(num <= 0) {
        DCRITICAL("FAIL: %s:%s sprite mem allocation cannot be zero", __FILE__, "sprite_alloc_mem(size_t num)");
        return spr_tmp;
    }


    spr_tmp = calloc(1,sizeof (sprite_t));
    spr_tmp->delay = NULL;

    if(!spr_tmp){
        return spr_tmp;
    }


    return spr_tmp;
}

int sprite_init(sprite_t **spr, SDL_Texture *tex)
{
    sprite_t *tmp = NULL;

    if((tmp = sprite_alloc_mem(1)) == NULL){
        return -1;
    }
    tmp->texture = tex;
    *spr = tmp;
    return 0;


}

int sprite_init_str(sprite_t **spr, const char *name)
{
    SDL_Texture *res_texture = NULL;
    sprite_t *tmp = NULL;

    res_texture =  resources_sprite_get(name, RESOURCE_EXTENSION_ANY);

    if(res_texture == NULL){
        DWARN("sprite %s not found",name);
        return -1;
    }


    if((sprite_init(&tmp, res_texture)) < 0){
        return -1;
    }
    *spr = tmp;
    return 0;



}

int sprite_set_spritesheet_offset(sprite_t *spr, int frame_width, int frame_height)
{
    int rx,ry;
    int w,h;

    if(spr == NULL || spr->texture == NULL){
        return -1;
    }


    SDL_QueryTexture(spr->texture, NULL, NULL, &w, &h);
    rx = w / abs(w / frame_width);
    ry = h / abs(h / frame_height);

    spr->delay = calloc(rx, sizeof(int));

    spr->rows = ry;
    spr->cols = rx;
    return 0;

}

void sprite_free(sprite_t **spr)
{
    if((*spr) == NULL) return;

    sprite_t *spr_tmp = *spr;

    if(spr_tmp->texture){
        SDL_DestroyTexture(spr_tmp->texture);
        spr_tmp->texture = NULL;
    }

    if(spr_tmp->delay) free(spr_tmp->delay);

    free((void*)spr);
    *spr = NULL;


}

void sprite_draw(sprite_t *spr, int x, int y, int orig_w, int orig_h, int dst_w, int dst_h)
{
    render_texture(spr->texture, spr->cols * spr->current_frame, spr->rows * spr->current_animation,
                   orig_w,orig_h, x,y, dst_w,dst_h, 0, SDL_FLIP_NONE);
}

void sprite_update(sprite_t *spr)
{
    if((int64_t)SDL_GetTicks() - spr->delay[spr->current_animation] > spr->time_passed){
        spr->time_passed = SDL_GetTicks();

        if(spr->current_frame >= spr->end_frame){
            spr->current_frame = 0;
        }else {
            ++spr->current_frame;
        }

    }


}

#define DELAY_FREE(x) if(x) free(x); x = NULL

int sprite_set_delay(sprite_t *spr, int *delay, size_t size)
{
    if(spr->delay){
        DELAY_FREE(spr->delay);
        spr->delay = delay;
        return 1;
    }


    spr->delay = calloc(size, sizeof(int));
    memcpy(spr->delay, delay, sizeof(int) * size);
    free(delay);
    delay = NULL;
    return 1;

}

void sprite_set_animation(sprite_t *spr, int anim)
{
     spr->current_animation = anim;
}

void sprite_draw_rect(sprite_t *spr, int src_x, int src_y, int dest_x, int dest_y, int w, int h, int flip)
{
    render_texture(spr->texture, src_x, src_y, w, h, dest_x, dest_y, w, h, 0, flip);
}
