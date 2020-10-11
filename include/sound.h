#ifndef SOUND_HEADER
#define SOUND_HEADER
#include <stdio.h>
#include <stdlib.h>


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


#define SOUND_SFX   1
#define SOUND_MUSIC 2

struct  sfx_t {
    Mix_Chunk *sample;
    Mix_Music *music;
    int type;
};



typedef  struct sfx_t sfx_t;


int sound_start(int samples);
void sound_end();

struct sfx_t *sfx_load(const char *filename);
struct sfx_t *music_load(const char *filename);
void sfx_destroy(sfx_t *sfx);

//void sfx_play_sample(sfx_t* sfx, float gain, float pan, float speed, ALLEGRO_PLAYMODE mode);

void sfx_play(sfx_t *sfx);
#endif
