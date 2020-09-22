#include "sound.h"
#include "log.h"

static ALLEGRO_VOICE *game_voice = NULL;
static ALLEGRO_MIXER *game_mixer = NULL;

int sound_start(int samples)
{
    if(!al_install_audio()){
        DLOG("Allegro sound error!");
        return 0;
    }

    game_voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);

    if(!game_voice){
        DCRITICAL("Failed to create a allegro voice!");
        return 0;
    }

    game_mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

    if(!al_attach_mixer_to_voice(game_mixer, game_voice)){
          DINFO("Error attaching mixer to voice");
          return 0;
    }

    if(!al_set_default_mixer(game_mixer)) {
        DINFO("Error setting default mixer.");
        return 0;
    }

    if(!al_reserve_samples(samples)) {
        DINFO("Error reserving samples.");
        return 0;
    }

    return 1;
}

void sound_end()
{
    if(game_voice) al_destroy_voice(game_voice);
    if(game_mixer) al_destroy_mixer(game_mixer);
    game_voice = NULL;
    game_mixer = NULL;
}
