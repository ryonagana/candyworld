#include <stdio.h>
#include "window.h"
#include "game.h"

int main(int argc, char *argv[])
{
    window_init(800,600, 0, "Candy!");

    game_init();
    game_start();
    game_end();
    return 0;
}
