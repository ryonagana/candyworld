#include "text.h"
#include "resources.h"
#include <stdarg.h>


TTF_Font *debug_font;


void text_start()
{
    debug_font = resources_ttf_get("debug_ttf");
}


text_t *text_create(const char *str, SDL_Color color)
{
    text_t *self = malloc(sizeof(text_t));
    text_init(self, str, color);
    return self;
}



int text_init(text_t *text, const char *str, SDL_Color color)
{
    SDL_Surface *text_surf = NULL;
    SDL_Texture *texture_font = NULL;

    text->color = color;
    strncpy(text->text,str, TEXT_MAX_ENTRY - strlen(str));
    text_surf = TTF_RenderText_Solid(debug_font, text->text, text->color);

    if(!text_surf){
        DCRITICAL("text_init(): invalid surface surface");
        return 0;
    }

    texture_font = SDL_CreateTextureFromSurface(window_get()->events.renderer, text_surf);

    if(!texture_font){
        DCRITICAL("text_init(): invalid texture surface");
        return 0;
    }


    text->texture = texture_font;
    return 1;


}



void text_destroy(text_t *text)
{
    SDL_DestroyTexture(text->texture);
    free(text);
    text = 0x0;
}

void text_draw(text_t *text, int x, int y)
{
    SDL_Rect orig, dst;
    int w,h;
    SDL_QueryTexture(text->texture, NULL, NULL, &w, &h);

    orig.x = 0;
    orig.y = 0;
    orig.w = w;
    orig.h = h;

    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;


    SDL_RenderCopy(window_get()->events.renderer, text->texture, &orig, &dst);
}
