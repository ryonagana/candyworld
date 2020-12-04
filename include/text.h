#ifndef TEXT_H
#define TEXT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define TEXT_MAX_ENTRY 1024

typedef struct text_t {
    char text[TEXT_MAX_ENTRY];
    SDL_Texture * texture;
    SDL_Color color;
}text_t;

extern TTF_Font *debug_font;

void text_start();
text_t *text_create(const char *str, SDL_Color color);
int text_init(text_t *text, const char *str, SDL_Color color);
text_t *text_edit(text_t *text, const char *str);
void text_destroy(text_t *text);
void text_draw(text_t *text, int x, int y);

#endif // TEXT_H
