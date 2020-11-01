#ifndef RESOURCES_H
#define RESOURCES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_image.h>


#include "log.h"
#include "sound.h"
#include "window.h"
#include "text.h"

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


#define DIR_BUF_SIZE 2048
#define FILENAME_BUF_SIZE 255

typedef struct file_t {
    char name[FILENAME_BUF_SIZE];
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
    char dir[DIR_BUF_SIZE];
};

typedef struct resources_t resources_t;

void resources_start(const char *dir);

// add any file
int  resources_file_add(const char *file, const char *name);

//add ttf files
int  resources_ttf_add(const char *file, const char *name, int size);

// free all resources (must be called once before SDL_Quit()
void resources_free();

// checks if the file exists
int resource_file_exists(const char *filepath);


//load a optmized surface SDL_Surface
SDL_Surface *resources_load_surface(const char *filename);

//convert a surface to texture
/*
 * resources_surf_to_tex()
 * with cleanup, if cleanup true surface will be freed
 * 1st param: SDL_Surface
 * 2nd param: perform cleanup - 1 = clean 0 = do nothing
 */
SDL_Texture *resources_surf_to_tex(SDL_Surface *surface, int cleanup);

// get resource list
struct resources_t* resources_get();


// get sprite by a name filter by extension
SDL_Texture* resources_sprite_get(const char* name, int extension);

// get get sound resource using name filter by extension
struct sfx_t* resources_sound_get(const char *name, int extension);

// get font ptr by name
TTF_Font* resources_ttf_get(const char *name);




#endif // RESOURCES_H
