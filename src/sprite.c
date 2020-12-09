#include "sprite.h"
#include "resources.h"
#include "shared.h"
#include "log.h"
#include "render.h"


void sprite_init(sprite_t *self)
{
    self->width = 0;
    self->height = 0;
    self->spritesheet = NULL;
    self->x = 0;
    self->y = 0;
}

sprite_t *sprite_create(SDL_Texture *texture, int x, int y, int width, int height)
{
    sprite_t *tmp = NULL;

    if(!(tmp = malloc(sizeof(sprite_t)))){
        DCRITICAL("sprite_create():  failed to alloc memory");
        return tmp;
    }

    sprite_init(tmp);

    tmp->spritesheet = texture_load_from_SDL(texture);
    tmp->x = x;
    tmp->y = y;
    tmp->width = width;
    tmp->height = height;
    return tmp;

}

void sprite_free(sprite_t *sprite)
{
    if(!sprite) return;

    sprite->spritesheet = NULL;
    free(sprite);
}

void sprite_draw(sprite_t *self, int x, int y, int width, int height, float angle, SDL_RendererFlip flip)
{
    if(!self) return;

    render_texture(self->spritesheet->texture, self->x, self->y, self->width, self->height, x,y, width, height, angle, flip );
}
