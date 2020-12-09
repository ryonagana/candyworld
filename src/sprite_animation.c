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
    self->width = 0;
    self->height = 0;
    self->delay = 0;
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
    self->width = sprite->width;
    self->height = sprite->height;


    return self;

}


void animation_render(sprite_animation_t *self, int x, int y)
{
    sprite_t *sprite = self->sprite;
    int tex_w, tex_h;
    tex_w = tex_h = 0;

    SDL_QueryTexture(sprite->spritesheet->texture, NULL, NULL, &tex_w, &tex_h);

    render_texture(sprite->spritesheet->texture,
                   sprite->x,
                   sprite->y,
                   tex_w,
                   tex_h,
                   x,
                   y,
                   sprite->width,
                   sprite->height,
                   0.0f,
                   self->flipmode);
    return;



}


int animation_add_list(link_list_t *list, sprite_animation_t *spr)
{
    if(spr == NULL){
        return 0;
    }

    if(list->head == NULL){
        list_push_node_head(list, (void *)spr);
        return 1;
    }

    list_push_node(list, (void*) spr);
    return 1;
}

void animation_render_frames(link_list_t *animation_list)
{
    link_node_t *node = animation_list->head;
    static Uint32  timer = 0;

    if(!timer)  timer = SDL_GetTicks();

    while(node != NULL){
        sprite_animation_t* frame = node->data;

        if(SDL_GetTicks() - frame->delay >= timer){
            timer = SDL_GetTicks();

            if(!node && frame->loop == LOOP_INFINITE){
                node = animation_list->head;
                continue;
            }

            if(!node && frame->loop == LOOP_NONE){
                node = animation_list->tail;
                continue;
            }
            node = node->next;
        }
    }
}

void animation_destroy(link_list_t *l)
{
    link_node_t *n = l->head;

    while(n){
        sprite_animation_t *anim = n->data;
        animation_frame_destroy(anim);
        anim = NULL;
        list_remove_node(l, n);
        n = n->next;
    }
}

void animation_frame_destroy(sprite_animation_t *anim)
{
    if(!anim) return;
    sprite_free(anim->sprite);
    free(anim);
}
