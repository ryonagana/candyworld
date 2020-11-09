#include "text.h"
#include "resources.h"
#include <stdarg.h>


void text_init_font(text_t **t, const char *font_name, int size, int flags)
{
    TTF_Font *font = NULL;
    text_t *tmp = NULL;

    if(!font_name){
        DWARN("text_init_font(): font name %s invalid ", font_name);
        return;
    }


    font = resources_ttf_get(font_name);

    if(!font){
        DWARN("text_init_font(): resource not found");
        return;
    }


    tmp = calloc(1, sizeof(text_t));
    tmp->font = font;
    tmp->size = size;
    tmp->flags = flags;
    *t = tmp;
    return;
}




void text_destroy(text_t **font)
{
    if(*(font) == NULL) return;
    text_t *tmp = *font;
    free(tmp);
    tmp = NULL;
    *font = tmp;

}



SDL_Surface *text_draw_surface(text_t *t, const SDL_Color color, const char *msg)
{

    return TTF_RenderUTF8_Solid(t->font, msg,  color);

}

void text_draw(text_t *text, int x, int y, const SDL_Color fg, const char *msg, ...)
{

    va_list lst;
    char buf[BUFSIZ] = {0};
    va_start(lst, msg);
    vsnprintf(buf, BUFSIZ, msg, lst);
    va_end(lst);

    SDL_Surface *text_surf = text_draw_surface(text, fg, buf);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(window_get()->events.renderer, text_surf);
    SDL_FreeSurface(text_surf);




    SDL_Rect orig, dest;

    orig.x = 0;
    orig.y = 0;

    TTF_SizeUTF8(text->font, msg, &orig.w, &orig.h);

    dest.x = x;
    dest.y = y;
    dest.w = orig.w;
    dest.h = orig.h;

    SDL_RenderCopyEx(window_get()->events.renderer, texture, &orig, &dest, 0, NULL, SDL_FLIP_NONE);
}
