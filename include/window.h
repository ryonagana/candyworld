#ifndef WINDOW_HEADER
#define WINDOW_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_physfs.h>
*/
#include <SDL2/SDL.h>

/*
#ifdef _WIN32
#include <allegro5/allegro_windows.h>
#include <allegro5/allegro_direct3d.h>
#endif // _WIN32
*/

#define FPS 60
#define MAX_TICKS 1000/FPS


enum {
    GAMESTATE_LOGOS,
    GAMESTATE_MENU_SCREEN,
    GAMESTATE_IN_GAME,
    GAMESTATE_GAME_OVER
};


typedef struct window_info {
    int width;
    int height;
    int renderer;
}window_info;

typedef struct window_events {

    SDL_Window *window;
    SDL_Renderer *renderer;

}window_events;

typedef struct game_window {
    window_info info;
    window_events events;
    int closed;
    int gamestate;
    char title[56];

}game_window;

void window_init(int w, int h, int fullscreen, const char* caption);

void window_free_events(game_window *win);
int window_end(void);
void window_exit(void);

void window_resize(int width, int height);

game_window*  window_get();

#endif // WINDOW_HEADER
