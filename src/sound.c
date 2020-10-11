#include "sound.h"
#include "log.h"



int sound_start(int samples)
{

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, samples, 1024)== -1) {
        DCRITICAL("Mix_OpenAudio: %s\n", Mix_GetError());
        return 0;
    }

    return 1;
}

void sound_end()
{
   Mix_Quit();
}

struct sfx_t *sfx_load(const char *filename)
{
    sfx_t *tmp = NULL;

    tmp = malloc(sizeof(sfx_t));
    tmp->sample = Mix_LoadWAV(filename);
    tmp->type = SOUND_SFX;
    tmp->music = NULL;

    if(tmp == NULL || tmp->sample == NULL){
        DLOG("Sample %s Failed to load", filename);
        goto exit_error;
    }

    return tmp;


exit_error:
    free(tmp);
    tmp = NULL;
    return NULL;


}

void sfx_destroy(sfx_t *sfx)
{
    if(sfx->sample){
        Mix_FreeChunk(sfx->sample);
        sfx->sample = NULL;
    }

    free(sfx);
    sfx = NULL;
    return;
}


void sfx_play(sfx_t *sfx)
{
    if(Mix_PlayChannel(-1, sfx->sample, 0)  < 0){
        DLOG("sfx_play(): failed to play sound");
        return;
    }
}

sfx_t *music_load(const char *filename)
{
    sfx_t *tmp = NULL;

    tmp = malloc(sizeof(sfx_t));
    tmp->sample = NULL;
    tmp->music = Mix_LoadMUS(filename);
    tmp->type = SOUND_MUSIC;

    if(tmp == NULL || tmp->sample == NULL){
        DLOG("Sample %s Failed to load", filename);
        goto exit_error;
    }

    return tmp;


exit_error:
    free(tmp);
    tmp = NULL;
    return NULL;
}
