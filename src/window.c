#include "window.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "log.h"
#include "sound.h"
#include "keyboard.h"
#include "shared.h"
#include "debug.h"

#define REPORT_ERROR(...) { fprintf(stderr,  ##__VA_ARGS__); }

/* Static definition */
static game_window main_window;
/* END STATIC */





/** \brief init main_window with default values
 *
 * \return nothing
 *
 */

static void window_starts_main_window(void)
{
    main_window.closed = 0;
    /*
    main_window.events.display = NULL;
    main_window.events.main_timer = NULL;
    main_window.events.queue = NULL;
    main_window.events.screen = NULL;
    */
    main_window.events.window = NULL;
    main_window.events.renderer = NULL;

    //ain_window.gamestate = GAMESTATE_IN_GAME;
    return;
}


/** \brief init the allegro library
 *
 * \return -1 error, 0 success
 *
 */
static int window_init_libraries(void){

    window_starts_main_window();


    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0){
        DCRITICAL("SDL_CANNOT START!");
        return -1;
    }

    int img_flags =  IMG_INIT_JPG | IMG_INIT_PNG;
    int img_init = IMG_Init(img_flags);
    if( (img_init & img_flags) != img_flags){
        DCRITICAL("IMG_Init() error ! - %s", SDL_GetError());
        return -1;
    }


    int mix_flags = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OGG;

    if( (mix_flags & Mix_Init(mix_flags)) != mix_flags){
         DCRITICAL("MIX_Init() error ! - %s", SDL_GetError());
         return -1;
    }




    if(TTF_Init() < 0){
         DCRITICAL("TTF_Init() error ! - %s", TTF_GetError());
         return -1;
    }



    return 0;

}
/** \brief
 *
 * \param width of the window
 * \param height of the window
 * \param check if starts at fullscreen
 * \param type of the renderer
 * \param caption
 * \return
 *
 */

static void window_create(int width, int height, int fullscreen, int vsync, int renderer, const char *caption){

    UNUSED(renderer);

    if(window_init_libraries() < 0){
        fprintf(stderr, "fatal error!");
        exit(1);
    }




    strncpy(main_window.title, caption, 56 - strlen(caption));


    int window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

    if(fullscreen){
        window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    }

    main_window.events.window = SDL_CreateWindow(main_window.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);

    if(!main_window.events.window){
        DCRITICAL("Main Window Error!");
        goto window_error;
    }


    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED;

    if(vsync > 0){
        renderer_flags |= SDL_RENDERER_PRESENTVSYNC;
    }

    main_window.events.renderer = SDL_CreateRenderer(main_window.events.window, -1, renderer_flags);

    if(!main_window.events.renderer){
        DCRITICAL("window renderer failed to load :(");
        SDL_DestroyWindow(main_window.events.window);
        goto window_error;

    }

    main_window.info.width = width;
    main_window.info.height = height;

    sound_start(4);
    log_init();
    keyboard_init();

    return;

window_error:
        window_end();
        return;


}

/** \brief access the window struct
 *
 * \return main_window
 *
 */

game_window*  window_get(){
    return &main_window;
}

void window_init(int w, int h, int fullscreen, int vsync, const char* caption){

    window_create(w,h,fullscreen, vsync, 1, caption);
    DINFO("Window is Created! -  Width: %d Height: %d, title: %s  fullscreen: %s", w,h, caption, fullscreen ? "True" : "False");
}




int window_end(void){

    window_free_events(&main_window);
    sound_end();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();



    if(main_window.events.window == NULL && main_window.events.renderer == NULL){
        DLOG("Window Closed Successfully!");
        return 0;
    }

    DLOG("Window Closed with Error!");
    return -1;

}

void window_exit(void){
    if(window_end() < 0){
        DINFO("Main Window Closed with error!");
        return;
    }

   DINFO("Main Window closed successfully");
   return;
}

void window_resize(int width, int height)
{
    //SDL_GetWindowSize(window_get()->events.window, )
    SDL_SetWindowSize(window_get()->events.window, width, height);

    int w,h;

    SDL_GetWindowSize(window_get()->events.window, &w,&h);

    window_get()->info.width = w;
    window_get()->info.height = h;
}

void window_free_events(game_window *win)
{
    if(win == NULL){
        return;
    }

    SDL_DestroyRenderer(win->events.renderer);
    SDL_DestroyWindow(win->events.window);
    win->events.window = NULL;
    win->events.renderer = NULL;
}
