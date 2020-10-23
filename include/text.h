#ifndef TEXT_H
#define TEXT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct text_t {
    TTF_Font *font;
    int size;
    int flags;
}text_t;


void text_init_font(text_t **t, const char *font_name, int size, int flags);

#endif // TEXT_H
