#ifndef CAMERA_H
#define CAMERA_H
#include <SDL2/SDL.h>

typedef struct camera {
    SDL_Rect pos;
    SDL_Rect area;
    int lock;

}camera;



void camera_init(camera *c, int x, int y, int width,int height);
void camera_set_pos(camera *c, int x, int y);
void camera_set_area(camera *c, int width, int height);
void camera_update(camera *c, int offset_x, int offset_y);

/*
int camera_get_x(camera *c);
int camera_get_y(camera *c);
int camera_get_width(camera *c);
int camera_get_height(camera *c);
*/

#endif // CAMERA_H
