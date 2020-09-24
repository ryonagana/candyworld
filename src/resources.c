#include "resources.h"
#include "log.h"
#include "sound.h"

static struct resources_t game_resources;

static void resources_debug_msg_add(file_t *f){
    switch(f->type){
        case RESOURCE_TYPE_SPRITE:
        DLOG("SPRITE: %s added", f->name);
        break;

    case RESOURCE_TYPE_SOUND:
        DLOG("SOUND: %s added", f->name);
        break;
    }

}

void resources_start(const char *dir)
{
    game_resources.head = NULL;
    game_resources.tail = NULL;
    game_resources.started = 1;
    game_resources.total_loaded = 0;

    if(!dir){
        strncpy(game_resources.dir, RESOURCES_FOLDER, 2048);
    }else {
        char buf[2048] = {0};
        strncpy(buf,dir, 2048);
        strncpy(game_resources.dir, dir, 2048);

    }



}

static int resource_get_ext(const char *filename)
{
    char *find_dot = strrchr(filename, '.');
    if(!find_dot || find_dot == filename) return RESOURCE_EXTENSION_NONE;

    if(strcmp(find_dot, ".jpg") == 0){
        return RESOURCE_EXTENSION_JPG;
    }

    if(strcmp(find_dot, ".png") == 0){
        return RESOURCE_EXTENSION_PNG;
    }

    if(strcmp(find_dot, ".bmp") == 0){
        return RESOURCE_EXTENSION_BMP;
    }

    if(strcmp(find_dot, ".ogg") == 0){
        return RESOURCE_EXTENSION_OGG;
    }

    if(strcmp(find_dot, ".mp3") == 0){
        return RESOURCE_EXTENSION_MP3;
    }

    if(strcmp(find_dot, ".wav") == 0){
        return RESOURCE_EXTENSION_WAV;
    }


    return RESOURCE_EXTENSION_NONE;
}

static void resources_list_add(file_t *f){


    if(game_resources.total_loaded <= 0 ){
            game_resources.head = f;
            game_resources.tail =  game_resources.head;
            game_resources.tail = game_resources.tail->next;
            game_resources.total_loaded++;
            return;
    }

    game_resources.tail = f;
    game_resources.tail = game_resources.tail->next;


    game_resources.total_loaded++;

#if defined(DEBUG)
    resources_debug_msg_add(f);
#endif

}

static int resources_load_image(const char *filepath, int extension){
    ALLEGRO_BITMAP *img  =  NULL;
    ALLEGRO_PATH   *path =  NULL;

    img = al_load_bitmap(filepath);
    if(!img){
        DCRITICAL("failed to load image %s", filepath);
        return 0;
    }

    path = al_create_path(filepath);
    const char *name = al_get_path_basename(path);

    file_t *tmp = malloc(sizeof (file_t));
    strncpy(tmp->name,"\0", 255);
    strcpy(tmp->name, name);
    tmp->next = NULL;
    tmp->type = RESOURCE_TYPE_SPRITE;
    tmp->block = NULL;
    tmp->block = img;
    tmp->extension = extension;


    al_destroy_path(path);
    path = 0x0;
    resources_list_add(tmp);

    return 1;

}


static int resources_load_sound(const char *filepath, int extension){
    //ALLEGRO_BITMAP *img  =  NULL;
    sfx_t* sfx = NULL;
    ALLEGRO_PATH   *path =  NULL;

    sfx = sfx_load(filepath);
    //img = al_load_bitmap(filepath);
    if(!sfx){
        DCRITICAL("failed to load sound %s", filepath);
        return 0;
    }

    path = al_create_path(filepath);
    const char *name = al_get_path_basename(path);

    file_t *tmp = malloc(sizeof (file_t));
    //memcpy(tmp->name, '\0', 255);
    strncpy(tmp->name,"\0", 255);
    strcpy(tmp->name, name);
    tmp->next = NULL;
    tmp->type = RESOURCE_TYPE_SOUND;
    tmp->block = NULL;
    tmp->block = sfx;
    tmp->extension = extension;


    al_destroy_path(path);
    path = 0x0;
    resources_list_add(tmp);

    return 1;

}

static int resources_file_load(const char *filepath){
    FILE *fp = NULL;

    if( (fp = fopen(filepath,"rb")) == NULL){
        DWARN("resource: %s not found!", filepath);
        return 0;
    }
    fclose(fp);
    int extension = resource_get_ext(filepath);

    switch(extension){
        case RESOURCE_EXTENSION_PNG:
            resources_load_image(filepath, RESOURCE_EXTENSION_PNG);
        break;

        case RESOURCE_EXTENSION_JPG:
            resources_load_image(filepath, RESOURCE_EXTENSION_JPG);
        break;

        case RESOURCE_EXTENSION_BMP:
             resources_load_image(filepath, RESOURCE_EXTENSION_BMP);
        break;

        case RESOURCE_EXTENSION_OGG:
            resources_load_sound(filepath, RESOURCE_EXTENSION_OGG);
        break;

        case RESOURCE_EXTENSION_WAV:
            resources_load_sound(filepath, RESOURCE_EXTENSION_WAV);
        break;

        case RESOURCE_EXTENSION_MP3:
            resources_load_sound(filepath, RESOURCE_EXTENSION_MP3);
        break;
    }
    return 1;
}

int resources_file_add(const char *file)
{
    return resources_file_load(file);
}


file_t* resource_get_ptr(const char *name, int type)
{
    file_t *tmp = game_resources.head;
    while(tmp != NULL && strcmp(tmp->name, name) == 0 && tmp->type == type){
        tmp = tmp->next;
    }

    return tmp;
}


struct sfx_t* resources_sound_get(const char *name, int extension){
    file_t *tmp = resource_get_ptr(name, extension);
    struct sfx_t *data = NULL;

    if(tmp == NULL){
        DLOG("resource %s not found", name);
        return NULL;
    }

    switch(extension){
        case RESOURCE_EXTENSION_OGG:
        case RESOURCE_EXTENSION_WAV:
        case RESOURCE_EXTENSION_MP3:
            data = (struct sfx_t*)tmp->block;
        break;
    }

    return data;
}


ALLEGRO_BITMAP *resources_sprite_get(const char* name, int extension)
{
    file_t *tmp = resource_get_ptr(name, extension);

    if(!tmp){
        DLOG("Resource %s not found");
        return NULL;
    }

    ALLEGRO_BITMAP *data = NULL;
    switch(extension){
        case RESOURCE_EXTENSION_BMP:
        case RESOURCE_EXTENSION_JPG:
        case RESOURCE_EXTENSION_PNG:
            data = (ALLEGRO_BITMAP*)tmp->block;
        break;
    }

    return data;


}

void resources_free()
{
    file_t *tmp = game_resources.head;
    file_t *old = NULL;


    while(tmp != NULL){

          old = tmp;
          tmp = tmp->next;

          free(old->block);
          free(old);

    }



}
