#include "sprite.h"
#include "resources.h"
#include "shared.h"
#include "log.h"

static sprite_t *sprite_alloc_mem(size_t num){

    sprite_t *spr_tmp = NULL;

    if(num <= 0) {
        DCRITICAL("FAIL: %s:%s sprite mem allocation cannot be zero", __FILE__, "sprite_alloc_mem(size_t num)");
        return spr_tmp;
    }


    if((spr_tmp = malloc(sizeof (sprite_t))) == NULL){
        return spr_tmp;
    }

    spr_tmp->pos.x = 0;
    spr_tmp->pos.y = 0;
    spr_tmp->pos.w = 0;
    spr_tmp->pos.h = 0;
    spr_tmp->hotspot.x = 0;
    spr_tmp->hotspot.y = 0;
    spr_tmp->hotspot.w = 0;
    spr_tmp->hotspot.h = 0;
    spr_tmp->offset_x = 0;
    spr_tmp->offset_y = 0;
    spr_tmp->frame_time = 0;
    spr_tmp->is_animated = 0;
    spr_tmp->actual_frame = 0;

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

int sprite_set_spritesheet_offset(sprite_t *spr, int rows, int cols)
{
    int rx,ry;
    int w,h;

    if(spr == NULL || spr->texture == NULL){
        return -1;
    }


    SDL_QueryTexture(spr->texture, NULL, NULL, &w, &h);
    rx = abs((w / cols));
    ry = abs((h / rows));

    spr->offset_x = rx;
    spr->offset_y = ry;
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

    free((void*)spr);
    *spr = NULL;


}
