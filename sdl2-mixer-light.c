/**
 * @file sdl2-mixer-light.c
 * @authors Esteban DOUILLET, SCHNEIDER Paul
 * @brief Header du module de SDL2 Mixer (light)
 * @date 2 Décembre 2022
 */

#include "sdl2-mixer-light.h"
#include <stdio.h>

void init_mixer() {
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        printf("SDL2_mixer could not be initialized!\n"
               "SDL_Error: %s\n", SDL_GetError());
    }
}

Mix_Chunk *load_sound(const char *path) {
    Mix_Chunk *sound = Mix_LoadWAV(path);
    if (!sound) printf("Mix_LoadWAV(\"Chunk.wav\"): %s\n", Mix_GetError());
    return sound;
}

void clean_sound(Mix_Chunk *sound) {
    Mix_FreeChunk(sound);
}


void clean_mixer() {
    Mix_CloseAudio();
}
