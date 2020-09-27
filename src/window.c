#include "window.h"
#include "log.h"
#include "sound.h"

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
    main_window.events.display = NULL;
    main_window.events.main_timer = NULL;
    main_window.events.queue = NULL;
    main_window.events.screen = NULL;
    main_window.gamestate = GAMESTATE_IN_GAME;
}


/** \brief init the allegro library
 *
 * \return -1 error, 0 success
 *
 */
static int window_init_allegro(void){

    window_starts_main_window();

    if(!al_init()){
        REPORT_ERROR("Error allegro cant init!\n");
        goto error;
    }

    if(!al_install_mouse()){
        REPORT_ERROR("Error allegro mouse!\n");
        goto error;
    }

    if(!al_install_keyboard()){
                    REPORT_ERROR("Error allegro keyboard!\n");
        goto error;
    }

    if(!al_install_joystick()){
                    REPORT_ERROR("Error allegro joystick!\n");
        goto error;
    }

    if(!al_init_image_addon()){
        REPORT_ERROR("Error allegro image addon!\n");
        goto error;
    }

    if(!al_init_font_addon()){
        REPORT_ERROR("Error allegro font addon!\n");
        goto error;
    }

    if(!al_init_ttf_addon()){
        REPORT_ERROR("Error allegro ttf addon!\n");
        goto error;
    }


    if(!al_init_primitives_addon()){
        REPORT_ERROR("Error allegro font primitives!\n");
        goto error;
    }

    if(!al_install_audio()){
        REPORT_ERROR("Error allegro audio!\n");
        goto error;
    }

    if(!al_init_acodec_addon()){
         REPORT_ERROR("Error allegro font acodecs!\n");
         goto error;
    }


    return 0;
error: return -1;
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

static void window_create(int width, int height, int fullscreen, int renderer, const char *caption){

    if(window_init_allegro() < 0){
        fprintf(stderr, "fatal error!");
        exit(1);
    }

    if(sound_start(4)){
        DINFO("Sound Started Successfully");
    }

    char title_buf[56] = {0};
    strncpy(title_buf, caption, 56 -1);


    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    if(fullscreen){
        al_set_new_bitmap_flags(ALLEGRO_FULLSCREEN);
    }else {
        al_set_new_bitmap_flags(ALLEGRO_WINDOWED);
    }

#if defined (_WIN32)
     al_set_new_display_flags(ALLEGRO_OPENGL);
#else
    al_set_new_display_flags(ALLEGRO_OPENGL_3_0);
#endif
    al_set_new_bitmap_flags(ALLEGRO_RESIZABLE);
    al_set_new_bitmap_flags(ALLEGRO_GENERATE_EXPOSE_EVENTS);

    main_window.info.width = width;
    main_window.info.height = height;
    main_window.info.renderer = renderer;
    main_window.events.display = al_create_display(width,height);
    main_window.events.queue = al_create_event_queue();
    main_window.events.main_timer = al_create_timer(1.0 / FPS); //60 fps
    main_window.events.timer = al_create_timer(0.1);
    main_window.events.screen = al_create_bitmap(width, height);

    al_start_timer(main_window.events.main_timer);
    al_start_timer(main_window.events.timer);

    al_get_keyboard_state(&main_window.events.kbd_state);

    al_register_event_source(main_window.events.queue, al_get_display_event_source(main_window.events.display));
    al_register_event_source(main_window.events.queue, al_get_keyboard_event_source());
    al_register_event_source(main_window.events.queue, al_get_mouse_event_source());
    al_register_event_source(main_window.events.queue, al_get_timer_event_source(main_window.events.main_timer));
    al_register_event_source(main_window.events.queue, al_get_timer_event_source(main_window.events.timer));


    al_set_window_title(main_window.events.display, title_buf);

    //init logging
    log_init();
}

/** \brief access the window struct
 *
 * \return main_window
 *
 */

game_window*  window_get(){
    return &main_window;
}

void window_init(int w, int h, int fullscreen, const char* caption){
    window_create(w,h,fullscreen, 1, caption);
    DINFO("Window is Created!");
}




int window_end(void){


    FREE_TIMER(main_window.events.main_timer);
    FREE_BMP(main_window.events.screen);
    FREE_QUEUE(main_window.events.queue);
    FREE_DISPLAY(main_window.events.display);
    sound_end();


    al_uninstall_system();
    al_uninstall_mouse();
    al_uninstall_joystick();
    al_uninstall_keyboard();

    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
    al_shutdown_primitives_addon();
    al_shutdown_native_dialog_addon();
    al_shutdown_image_addon();
    al_uninstall_audio();


    if(main_window.events.main_timer == NULL && main_window.events.screen == NULL && main_window.events.queue == NULL && main_window.events.display == NULL){
        return 0;
    }

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
