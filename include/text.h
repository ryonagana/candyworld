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
void text_draw_bg(text_t *font, int x, int y, const SDL_Color fg, const SDL_Color bg, const char *msg,...);
void text_draw(text_t *font, int x, int y,  const SDL_Color fg, const char *msg,...);
void text_draw_shade(text_t *font, int x, int y, const SDL_Color fg, const SDL_Color bg, const char *msg,...);
void text_destroy(text_t **font);

#endif // TEXT_H
