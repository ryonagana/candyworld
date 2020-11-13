#include <stdio.h>
#include "window.h"
#include "game.h"

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    window_init(800,600, WINDOW_FULLSCREEN_OFF, WINDOW_VSYNC_ON, "Candy!");

    game_init();
    game_start();
    game_end();
    return 0;
}
