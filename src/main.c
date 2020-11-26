#include "main.h"

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    window_init(800,600, WINDOW_FULLSCREEN_OFF, WINDOW_VSYNC_ON, "Application");

    game_init();
    game_start();
    game_end();
    SDL_Quit();
    return 0;
}
