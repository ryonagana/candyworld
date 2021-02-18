#include "texture.h"
#include "resources.h"
#include "list.h"
#include "log.h"

void texture_init(texture_t *texture)
{
    texture->access = 0;
    texture->format = 0;
    texture->height = 0;
    texture->width =  0;
    texture->texture = NULL;
}

texture_t *texture_load_str(const char *name)
{
    SDL_Texture *texture = NULL;
    texture_t *self = NULL;

    texture =  resources_sprite_get(name, RESOURCE_EXTENSION_ANY);

    if(!texture){
        texture = resources_sprite_get_by_filename(name);

        if(!texture){
            DCRITICAL("texture_load_str():  image %s not found", name);
            return NULL;
        }
    }


    self = malloc(sizeof(texture_t));
    texture_init(self);
    self->texture = texture;
    SDL_QueryTexture(texture, &self->format, &self->access, &self->width, &self->height);
    return self;
}

texture_t *texture_load_from_SDL(SDL_Texture *tex)
{
    texture_t *self = NULL;
    self = malloc(sizeof(texture_t));
    texture_init(self);
    self->texture  = tex;
    SDL_QueryTexture(tex, &self->format, &self->access, &self->width, &self->height);
    return self;
}

void texture_destroy(texture_t *self)
{
    if(!self) return;
    free(self);
}

void texture_set_blending(texture_t *self, SDL_BlendMode blend)
{
    SDL_SetTextureBlendMode(self->texture, blend);
}

void texture_set_alpha(texture_t *self, Uint8 alpha)
{
    SDL_SetTextureAlphaMod(self->texture, alpha);
}
