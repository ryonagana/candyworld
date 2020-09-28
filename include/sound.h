#ifndef SOUND_HEADER
#define SOUND_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

struct  sfx_t {
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *instance;

};

typedef  struct sfx_t sfx_t;

int sound_start(int samples);
void sound_end();

struct sfx_t *sfx_load(const char *filename);
void sfx_destroy(sfx_t *sfx);

void sfx_play_sample(sfx_t* sfx, float gain, float pan, float speed, ALLEGRO_PLAYMODE mode);

void sfx_play(sfx_t *sfx);

#endif
