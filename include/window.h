#ifndef WINDOW_HEADER
#define WINDOW_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_physfs.h>

#ifdef _WIN32
#include <allegro5/allegro_windows.h>
#include <allegro5/allegro_direct3d.h>
#endif // _WIN32


#define FPS 60.0

#define FREE_HELPER(expr)  { if(expr != NULL) { free(expr); expr = NULL;} }
#define FREE_DISPLAY(dsp)   { if(dsp != NULL) {al_destroy_display(dsp); dsp = NULL;} }
#define FREE_QUEUE(x)   { if(x != NULL) {al_destroy_event_queue(x); x = NULL;} }
#define FREE_TIMER(x)   { if(x != NULL) {al_destroy_timer(x); x = NULL;} }
#define FREE_BMP(x)   { if(x != NULL) {al_destroy_bitmap(x); x = NULL;} }

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

typedef struct window_allegro_events {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_KEYBOARD_STATE kbd_state;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *main_timer;
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP *screen;
}window_allegro_events;

typedef struct game_window {
    window_info info;
    window_allegro_events events;
    int closed;
    int gamestate;
    char title[56];

}game_window;

void window_init(int w, int h, int fullscreen, const char* caption);
int window_end(void);
void window_exit(void);

game_window*  window_get();

#endif // WINDOW_HEADER
