#ifndef RESOURCES_H
#define RESOURCES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>


#define RESOURCES_FOLDER "resources//"

#define RESOURCES_SPRITE_FOLDER RESOURCE_FOLDER "sprites//"


#define RESOURCE_TYPE_SPRITE 1
#define RESOURCE_TYPE_SOUND  2
#define RESOURCE_TYPE_TEXT   3

#define RESOURCE_EXTENSION_NONE 0
#define RESOURCE_EXTENSION_PNG  1
#define RESOURCE_EXTENSION_JPG  2
#define RESOURCE_EXTENSION_BMP  3

#define RESOURCE_EXTENSION_OGG  4
#define RESOURCE_EXTENSION_WAV  5
#define RESOURCE_EXTENSION_MP3  6

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


void resources_start(const char *dir);
int  resources_file_add(const char *file);

void resources_free();

ALLEGRO_BITMAP* resources_sprite_get(const char* name, int type);
struct sfx_t* resources_sound_get(const char *name, int extension);




#endif // RESOURCES_H
