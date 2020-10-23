#ifndef RESOURCES_H
#define RESOURCES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_image.h>

#define RESOURCES_FOLDER "resources//"

#define RESOURCES_FOLDER_SPRITE RESOURCES_FOLDER"sprites//"


#define RESOURCE_TYPE_SPRITE 1
#define RESOURCE_TYPE_SOUND  2
#define RESOURCE_TYPE_TEXT   3
#define RESOURCE_TYPE_FONT   4

#define RESOURCE_EXTENSION_NONE 0
#define RESOURCE_EXTENSION_PNG  1
#define RESOURCE_EXTENSION_JPG  2
#define RESOURCE_EXTENSION_BMP  3

#define RESOURCE_EXTENSION_OGG  4
#define RESOURCE_EXTENSION_WAV  5
#define RESOURCE_EXTENSION_MP3  6

#define RESOURCE_EXTENSION_TTF  7

#define RESOURCE_EXTENSION_ANY  255

typedef struct file_t {
    char name[255];
    int type;
    int extension;
    void *block;
    struct file_t *next;
}file_t;



struct resources_t
{
    struct file_t* tail;
    struct file_t* head;
    int total_loaded;
    int started;
    char dir[2048];
};

typedef struct resources_t resources_t;

void resources_start(const char *dir);
int  resources_file_add(const char *file, const char *name);
int  resources_ttf_add(const char *file, const char *name, int size);

void resources_free();

int resource_file_exists(const char *filepath);

SDL_Surface *resources_load_surface(const char *filename);
SDL_Texture *resources_surf_to_tex(SDL_Surface *surface, int cleanup);


struct resources_t* resources_get();
SDL_Texture* resources_sprite_get(const char* name, int extension);
struct sfx_t* resources_sound_get(const char *name, int extension);





#endif // RESOURCES_H
