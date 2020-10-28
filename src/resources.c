#include "resources.h"


#include <SDL2/SDL_ttf.h>

static struct resources_t game_resources;



static void resources_release_file(file_t **f){
    free((void *)*f);
    *f = NULL;
}

static void resources_debug_msg_add(file_t *f){
    switch(f->type){
        case RESOURCE_TYPE_SPRITE:
            DLOG("SPRITE: %s added", f->name);
        break;

        case RESOURCE_TYPE_SOUND:
            DLOG("SOUND: %s added", f->name);
        break;

        case RESOURCE_TYPE_FONT:
            DLOG("FONT: %s added", f->name);
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
        strncpy(buf,dir, DIR_BUF_SIZE - 1);
        strncpy(game_resources.dir, dir, DIR_BUF_SIZE - 1);

    }

    DLOG("Resources Folder %s", RESOURCES_FOLDER);
    DLOG("Resources Folder %s", RESOURCES_FOLDER_SPRITE);



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


static void resources_free_sprite(file_t **f){
    SDL_Texture *img = (*f)->block;
    //al_destroy_bitmap(img);
    SDL_DestroyTexture(img);
    img = NULL;

     resources_release_file(f);

    return;
}

static void resources_free_sound(file_t **f){
    sfx_t *sfx = (*f)->block;
    sfx_destroy(sfx);
    resources_release_file(f);
    return;
}

static void resources_free_font(file_t **f){
    TTF_Font *font = (*f)->block;
    TTF_CloseFont(font);
    font = NULL;
    resources_release_file(f);

}

static void resources_list_add(file_t *f){

    if(game_resources.tail == NULL || game_resources.total_loaded <= 0){
        game_resources.tail = f;
        game_resources.head = game_resources.tail;
        game_resources.total_loaded++;
        return;
    }


    game_resources.tail->next = f;
    game_resources.tail = game_resources.tail->next;
    game_resources.total_loaded++;


#if defined(DEBUG)
    resources_debug_msg_add(f);
#endif

}

static int resources_load_image(const char *filepath, const char *name, int extension){



    SDL_Surface *surf  = resources_load_surface(filepath);
    SDL_Texture *tex   = resources_surf_to_tex(surf, 0);

    file_t *tmp = malloc(sizeof (file_t));
    strncpy(tmp->name,"\0", 255);
    strcpy(tmp->name, name);
    tmp->next = NULL;
    tmp->type = RESOURCE_TYPE_SPRITE;
    tmp->block = NULL;
    tmp->block = tex;
    tmp->extension = extension;
    SDL_FreeSurface(surf);
    resources_list_add(tmp);

    return 1;

}

static int resources_load_font(const char *filepath, int size, const char *name, int extension){
    if(resource_file_exists(filepath) < 0){
       DWARN("resource: %s not found!", filepath);
       return -1;
    }


    TTF_Font *fnt = NULL;
    fnt = TTF_OpenFont(filepath, size);



    if(fnt == NULL){
        DWARN("cannot load font %s on memory");
        return -1;
    }

    file_t *tmp = calloc(1, sizeof (file_t));
    strcpy(tmp->name, name);
    tmp->next = NULL;
    tmp->type = RESOURCE_TYPE_FONT;
    tmp->block = NULL;
    tmp->block = fnt;
    tmp->extension = extension;
    resources_list_add(tmp);
    return 0;
}


static int resources_load_sound(const char *filepath, const char *name,  int extension){

    sfx_t* sfx = NULL;

    sfx = sfx_load(filepath);

    if(!sfx){
        DLOG("Error! failed to load sound resource: %s", filepath);
        return 0;
    }


    file_t *tmp = malloc(sizeof (file_t));
    //memcpy(tmp->name, '\0', 255);
    strncpy(tmp->name,"\0", 255);
    strcpy(tmp->name, name);
    tmp->next = NULL;
    tmp->type = RESOURCE_TYPE_SOUND;
    tmp->block = NULL;
    tmp->block = sfx;
    tmp->extension = extension;

    resources_list_add(tmp);

    return 1;

}

static int resources_file_load(const char *filepath, const char *name){
    FILE *fp = NULL;

    if( (fp = fopen(filepath,"rb")) == NULL){
        DWARN("resource: %s not found!", filepath);
        return 0;
    }
    fclose(fp);
    int extension = resource_get_ext(filepath);

    switch(extension){
        case RESOURCE_EXTENSION_PNG:
            resources_load_image(filepath, name, RESOURCE_EXTENSION_PNG);
        break;

        case RESOURCE_EXTENSION_JPG:
            resources_load_image(filepath, name, RESOURCE_EXTENSION_JPG);
        break;

        case RESOURCE_EXTENSION_BMP:
             resources_load_image(filepath, name, RESOURCE_EXTENSION_BMP);
        break;

        case RESOURCE_EXTENSION_OGG:
            resources_load_sound(filepath, name, RESOURCE_EXTENSION_OGG);
        break;

        case RESOURCE_EXTENSION_WAV:
            resources_load_sound(filepath, name, RESOURCE_EXTENSION_WAV);
        break;

        case RESOURCE_EXTENSION_MP3:
            resources_load_sound(filepath, name, RESOURCE_EXTENSION_MP3);
        break;
    }
    return 1;
}

int resources_file_add(const char *file, const char *name)
{
    return resources_file_load(file, name);
}


file_t* resource_get_ptr(const char *name, int type)
{
    file_t *tmp = game_resources.head;

    if(type != RESOURCE_EXTENSION_ANY){
        while(tmp != NULL && strcmp(tmp->name, name) != 0 && tmp->type != type){
            tmp = tmp->next;
        }

        return tmp;
    }


    while(tmp != NULL && strcmp(tmp->name, name) != 0){
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


SDL_Texture *resources_sprite_get(const char* name, int extension)
{
    file_t *tmp = resource_get_ptr(name, extension);

    if(!tmp){
        DLOG("Resource %s not found");
        return NULL;
    }

    return (SDL_Texture *) tmp->block;

}

void resources_free()
{
    file_t *tmp = game_resources.head;
    file_t *old = NULL;


    while(tmp != NULL){
            old = tmp;
            tmp = tmp->next;

            switch(old->type){
                case RESOURCE_TYPE_SPRITE:
                    DWARN("Releasing Sprite Resource: %s", old->name);
                    resources_free_sprite(&old);

                break;

                case RESOURCE_TYPE_SOUND:
                    DWARN("Releasing Sound Resource: %s", old->name);
                    resources_free_sound(&old);
                break;

                case RESOURCE_TYPE_FONT:
                    DWARN("Releasing Font TTF Resource: %s", old->name);
                    resources_free_font(&old);
                break;
            }


            game_resources.total_loaded--;
    };



}

struct resources_t *resources_get()
{
    return &game_resources;
}

SDL_Surface *resources_load_surface(const char *filename)
{
    char path_buf[2048] = {0};
    SDL_Surface *tmp = NULL;
    strncpy(path_buf, filename, 2048 - 1);
    tmp = IMG_Load(path_buf);
    return tmp;
}

SDL_Texture *resources_surf_to_tex(SDL_Surface *surface, int cleanup)
{
    SDL_Texture *texture =  NULL;

    texture = SDL_CreateTextureFromSurface(window_get()->events.renderer, surface);

    if(!texture){
        DWARN("failed to convert surface to texture");
    }

    if(cleanup) SDL_FreeSurface(surface);


    return texture;


}

int resources_ttf_add(const char *file, const char *name, int size)
{
    if(resource_file_exists(file) < 0){
       DWARN("resource: %s not found!", file);
       return -1;
    }


    int file_ext= resource_get_ext(file);

    switch(file_ext){
        default:
        case RESOURCE_EXTENSION_TTF:
            resources_load_font(file,size, name, file_ext);
        break;
    }

    return 0;
}

int resource_file_exists(const char *filepath)
{
    FILE *fp = NULL;

    if( (fp = fopen(filepath,"rb")) == NULL){
        return -1;
    }
    fclose(fp);
    return 0;

}

TTF_Font *resources_ttf_get(const char *name)
{
    file_t *fp = NULL;
    char buf[BUFSIZ] = {0};
    TTF_Font *font = NULL;

    if(!name){
        DCRITICAL("resources_ttf_get(): invalid function parameters");
        return NULL;
    }

    strncpy(buf, name, BUFSIZ - 1);

    fp = resource_get_ptr(buf, RESOURCE_TYPE_FONT);

    if(!fp){
        DCRITICAL("resources_ttf_get(): font %s not found", buf);
        return NULL;
    }

    font = (void*) fp->block;



    if(!font){
        DCRITICAL("resources_ttf_get(): resource ptr is invalid", buf);
        return NULL;
    }

    return font;

}
