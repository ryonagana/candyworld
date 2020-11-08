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


void text_draw(text_t *font, int x, int y,  const SDL_Color fg, const char *msg,...)
{
    char buf[BUFSIZ] = {0};
    va_list lst;
    SDL_Surface *text_surf = NULL;
    SDL_Texture *texture = NULL;
    va_start(lst, msg);
    vsnprintf(buf, BUFSIZ, msg, lst);
    va_end(lst);



    text_surf = TTF_RenderUTF8_Solid(font->font, buf, fg);
    texture = SDL_CreateTextureFromSurface(window_get()->events.renderer, text_surf);
    SDL_FreeSurface(text_surf);

    SDL_Rect orig, dest;

    orig.x = 0;
    orig.y = 0;

    TTF_SizeUTF8(font->font, msg, &orig.w, &orig.h);

    dest.x = x;
    dest.y = y;
    dest.w = x * 16;
    dest.h = y * 16;

    SDL_RenderCopyEx(window_get()->events.renderer, texture, &orig, &dest, 0, NULL, SDL_FLIP_NONE);
}



void text_draw_bg(text_t *font, int x, int y,  const SDL_Color fg, const SDL_Color bg, const char *msg,...)
{
    char buf[BUFSIZ] = {0};
    va_list lst;
    SDL_Surface *text_surf = NULL;
    SDL_Texture *texture = NULL;
    va_start(lst, msg);
    vsnprintf(buf, BUFSIZ, msg, lst);
    va_end(lst);



    text_surf = TTF_RenderUTF8_Shaded(font->font, buf, fg,bg);
    texture = SDL_CreateTextureFromSurface(window_get()->events.renderer, text_surf);
    SDL_FreeSurface(text_surf);

    SDL_Rect orig, dest;

    orig.x = 0;
    orig.y = 0;

    TTF_SizeUTF8(font->font, msg, &orig.w, &orig.h);

    dest.x = x;
    dest.y = y;
    dest.w = orig.w;
    dest.h = orig.h;

    SDL_RenderCopyEx(window_get()->events.renderer, texture, &orig, &dest, 0, NULL, SDL_FLIP_NONE);
}

void text_draw_shade(text_t *font, int x, int y, const SDL_Color fg, const SDL_Color bg, const char *msg,...)
{
    va_list lst;
    char buf[BUFSIZ] = {0};
    va_start(lst, msg);
    vsnprintf(buf, BUFSIZ, msg, lst);
    va_end(lst);

    text_draw(font,x,y+1, bg, msg);
    text_draw(font,x,y,   fg, msg);


}

void text_destroy(text_t **font)
{
    if(*(font) == NULL) return;

    text_t *tmp = *font;

    if(tmp->font != NULL) TTF_CloseFont(tmp->font);
    tmp->font = NULL;

    free(tmp);
    tmp = NULL;
    *font = tmp;

}
