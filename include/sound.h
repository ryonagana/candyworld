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

int sound_start(int samples);
void sound_end();

#endif
