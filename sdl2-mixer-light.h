#ifndef SDL2_mixer_LIGHT_H
#define SDL2_mixer_LIGHT_H

/**
 * @file sdl2-mixer-light.h
 * @authors Esteban DOUILLET, SCHNEIDER Paul
 * @brief Header du module de SDL2 Mixer (light)
 * @date 2 Décembre 2022
 */

#include <SDL.h>
#include <SDL_mixer.h>

/**
 * @brief Initialisation de SDL Mixer
 */
void init_mixer();

/**
 * @brief Chargement d'un son
 * @param path Le chemin
 * @return Le son
 */
Mix_Chunk *load_sound(const char *path);

/**
 * @brief Libère la mémoire d'un son
 * @param sound Le son
 */
void clean_sound(Mix_Chunk *sound);

/**
 * @brief Libère la mémoire de SDL Mixer
 */
void clean_mixer();

#endif
